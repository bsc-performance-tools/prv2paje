#include "pajewriter.h"


prv2paje::PajeWriter::PajeWriter(PrvParser* prvParser, string pajePath):pajePath(pajePath), basicHeader(false), oldHeader(false), prvParser(prvParser)
{
    pcfParser=prvParser->getPcfParser();
    prvMetaData=prvParser->getPrvMetaData();
    fast=prvParser->getFast();
}

prv2paje::PajeWriter::PajeWriter(PrvParser* prvParser, string pajePath, bool basicHeader, bool oldHeader):pajePath(pajePath), basicHeader(basicHeader), oldHeader(oldHeader), prvParser(prvParser)
{
    pcfParser=prvParser->getPcfParser();
    prvMetaData=prvParser->getPrvMetaData();
    fast=prvParser->getFast();
}

prv2paje::PajeWriter::~PajeWriter()
{

}

void prv2paje::PajeWriter::push(PrvEvents *prvEvent)
{
    double timestamp=(double)prvEvent->getTimestamp()/timeDivider;
    int cpu=prvEvent->getCpu();
    int app=prvEvent->getApp();
    int task=prvEvent->getTask();
    int thread=prvEvent->getThread();
    long lineNumber=prvEvent->getLineNumber();
    checkContainerChain(timestamp, cpu, app, task, thread);
    string container = to_string(cpu)+string(".")+to_string(app)+string(".")+to_string(task)+string(".")+to_string(thread);
    pajePending.pushPendingEvents(timestamp);
    for (auto &it: *(prvEvent->getEvents())){
        int type = it.first;
        string typeString = to_string(type);
        string value = it.second;
        if (pcfParser->getPcfEvents()->count(type)==0){
            PcfEvents* unknownEvent=new PcfEvents(0,type);
            unknownEvent->setEventType(pcfeventtype::Variable);
            unknownEvent->setLabel(to_string(type));
            pcfParser->getPcfEvents()->operator [](type)=unknownEvent;
            Message::Warning("line " + to_string(lineNumber)+ ". Undefined event type. Type: "+to_string(type)+" Value: "+value+
                            ". Unable to determine its semantics. Will be defined as a variable.");
            string color= to_string((float) rand()/RAND_MAX)+string(" ")+
                          to_string((float) rand()/RAND_MAX)+string(" ")+
                          to_string((float) rand()/RAND_MAX);
            poti_DefineVariableType(typeString.c_str(), PAJE_CONTAINER_DEF_NAME_THREAD, typeString.c_str(), color.c_str());
        }
        if (pcfParser->getPcfEvents()->operator [](type)->getEventType()==pcfeventtype::State){
            if (value.compare(PCF_EVENT_STATE_VALUE_END_STRING)==0){
                PajePendingEndState* pajePendingEndState=new PajePendingEndState(timestamp);
                pajePendingEndState->setContainer(container);
                pajePendingEndState->setType(typeString);
                if (pajePending.addPajePendingEvent(pajePendingEndState, true, fast)==-1){
                    Message::Warning("line " + to_string(lineNumber)+ ". Illegal pop. Type: "+to_string(type)+" Value: "+value+
                                    ". Event will be dropped...");
                }
            }else{
                PajePendingStartState* pajePendingStartState=new PajePendingStartState(timestamp);
                pajePendingStartState->setContainer(container);
                pajePendingStartState->setType(typeString);
                pajePendingStartState->setValue(value);
                pajePending.addPajePendingEvent(pajePendingStartState, true, fast);
            }
        }else if (pcfParser->getPcfEvents()->operator [](type)->getEventType()==pcfeventtype::Variable){
            try{
                long long valueLong=stoll(value.c_str());
                poti_SetVariable (timestamp, container.c_str(), typeString.c_str(), valueLong);
            }catch (const std::out_of_range& err) {
                Message::Warning("line "+ to_string(lineNumber)+". Value out of range. Type: "+to_string(type)+" Value: "+value+". Event will be dropped...");
            }
        }
    }
}

void prv2paje::PajeWriter::push(PrvState *prvEvent)
{
    double startTimestamp=(double)prvEvent->getTimestamp()/timeDivider;
    double endTimestamp=(double)prvEvent->getEndTimestamp()/timeDivider;
    pajePending.pushPendingEvents(startTimestamp);
    int cpu=prvEvent->getCpu();
    int app=prvEvent->getApp();
    int task=prvEvent->getTask();
    int thread=prvEvent->getThread();
    long lineNumber=prvEvent->getLineNumber();
    string value=prvEvent->getValue();
    if (startTimestamp>endTimestamp){
        Message::Warning("line "+ to_string(lineNumber)+". State duration is negative. Start: "+to_string(startTimestamp)+" End: "+to_string(endTimestamp)+". Event will be dropped...");
    }else{
        checkContainerChain(startTimestamp, cpu, app, task, thread);
        string container = to_string(cpu)+string(".")+to_string(app)+string(".")+to_string(task)+string(".")+to_string(thread);
        PajePendingStartState* pajePendingStartState=new PajePendingStartState(startTimestamp);
        pajePendingStartState->setContainer(container);
        pajePendingStartState->setType(PAJE_PRVSTATE_ALIAS);
        pajePendingStartState->setValue(value);
        PajePendingEndState* pajePendingEndState=new PajePendingEndState(endTimestamp);
        pajePendingEndState->setContainer(container);
        pajePendingEndState->setType(PAJE_PRVSTATE_ALIAS);      
        pajePending.addPajePendingEvent(pajePendingStartState, false, fast);
        pajePending.addPajePendingEvent(pajePendingEndState, false, fast);
    }
}

void prv2paje::PajeWriter::push(PrvCommunications *prvEvent)
{
    int cpu1=prvEvent->getCpu();
    int app1=prvEvent->getApp();
    int task1=prvEvent->getTask();
    int thread1=prvEvent->getThread();
    int cpu2=prvEvent->getCpu2();
    int app2=prvEvent->getApp2();
    int task2=prvEvent->getTask2();
    int thread2=prvEvent->getThread2();
    long lineNumber=prvEvent->getLineNumber();
    double startTimestampSW=(double)prvEvent->getTimestamp()/timeDivider;
    double endTimestampSW=(double)prvEvent->getTimestampEnd()/timeDivider;
    double startTimestampHW=(double)prvEvent->getTimestampHW()/timeDivider;
    double endTimestampHW=(double)prvEvent->getTimestampHWEnd()/timeDivider;
    pajePending.pushPendingEvents(startTimestampHW);
    string value=prvEvent->getValue();
    if (startTimestampHW>endTimestampHW){
        Message::Debug("line "+ to_string(lineNumber)+". Backward communication. Event will be dropped...");
    }else{
        checkContainerChain(startTimestampSW, cpu1, app1, task1, thread1);
        checkContainerChain(startTimestampSW, cpu2, app2, task2, thread2);
        string startContainer = to_string(cpu1)+string(".")+to_string(app1)+string(".")+to_string(task1)+string(".")+to_string(thread1);
        string endContainer = to_string(cpu2)+string(".")+to_string(app2)+string(".")+to_string(task2)+string(".")+to_string(thread2);
        string container = PAJE_CONTAINER_ALIAS_ROOT;
        string typeHW=PAJE_PRVCOMMUNICATION_HW_ROOT_ALIAS;
        string typeSW=PAJE_PRVCOMMUNICATION_SW_ROOT_ALIAS;
        if (cpu1==cpu2){
            typeHW=PAJE_PRVCOMMUNICATION_HW_CPU_ALIAS;
            typeSW=PAJE_PRVCOMMUNICATION_SW_CPU_ALIAS;
            container = string(PAJE_CONTAINER_ALIAS_CPU_PREFIX)+to_string(cpu1);
            if (app1==app2){
                typeHW=PAJE_PRVCOMMUNICATION_HW_APP_ALIAS;
                typeSW=PAJE_PRVCOMMUNICATION_SW_APP_ALIAS;
                container = to_string(cpu1)+string(".")+to_string(app1);
                if (task1==task2){
                    typeHW=PAJE_PRVCOMMUNICATION_HW_TASK_ALIAS;
                    typeSW=PAJE_PRVCOMMUNICATION_SW_TASK_ALIAS;
                    container = container+string(".")+to_string(task1);
                    if (thread1==thread2){
                        typeHW=PAJE_PRVCOMMUNICATION_HW_THREAD_ALIAS;
                        typeSW=PAJE_PRVCOMMUNICATION_SW_THREAD_ALIAS;
                        container = container+string(".")+to_string(thread1);
                    }
                }
            }
        }
        PajePendingStartCommunication* pajePendingStartCommunicationHW=new PajePendingStartCommunication(startTimestampHW);
        PajePendingEndCommunication* pajePendingEndCommunicationHW=new PajePendingEndCommunication(endTimestampHW);
        PajePendingStartCommunication* pajePendingStartCommunicationSW=new PajePendingStartCommunication(startTimestampSW);
        PajePendingEndCommunication* pajePendingEndCommunicationSW=new PajePendingEndCommunication(endTimestampSW);
        pajePendingStartCommunicationHW->setContainer(container);
        pajePendingEndCommunicationHW->setContainer(container);
        pajePendingStartCommunicationSW->setContainer(container);
        pajePendingEndCommunicationSW->setContainer(container);
        pajePendingStartCommunicationHW->setType(typeHW);
        pajePendingEndCommunicationHW->setType(typeHW);
        pajePendingStartCommunicationSW->setType(typeSW);
        pajePendingEndCommunicationSW->setType(typeSW);
        pajePendingStartCommunicationHW->setSubContainer(startContainer);
        pajePendingEndCommunicationHW->setSubContainer(endContainer);
        pajePendingStartCommunicationSW->setSubContainer(startContainer);
        pajePendingEndCommunicationSW->setSubContainer(endContainer);
        pajePendingStartCommunicationHW->setValue(value);
        pajePendingEndCommunicationHW->setValue(value);
        pajePendingStartCommunicationSW->setValue(value);
        pajePendingEndCommunicationSW->setValue(value);
        pajePendingStartCommunicationHW->setKey(PajePendingCommunication::GetNextKey());
        pajePendingEndCommunicationHW->setKey(pajePendingStartCommunicationHW->getKey());
        pajePendingStartCommunicationSW->setKey(PajePendingCommunication::GetNextKey());
        pajePendingEndCommunicationSW->setKey(pajePendingStartCommunicationSW->getKey());
        //TODO manage SW communications
        //poti_StartLink(startTimestampSW, container.c_str(), typeSW.c_str(), startContainer.c_str(), value.c_str(), pajePendingEndCommunicationSW->getKey().c_str());
        //pajePending.addPajePendingEvent(pajePendingStartCommunicationSW);
        //pajePending.addPajePendingEvent(pajePendingEndCommunicationSW);
        pajePending.addPajePendingEvent(pajePendingStartCommunicationHW);
        pajePending.addPajePendingEvent(pajePendingEndCommunicationHW);
        //pajePending.addPajePendingEvent(pajePendingEndCommunicationSW);
    }
}

void prv2paje::PajeWriter::generatePajeHeader()
{
    FILE *file = fopen(pajePath.c_str(), "w");
    if (!file){
      Message::Error("cannot generate file "+pajePath);
    }
    poti_init(file);
    poti_header(basicHeader?1:0, oldHeader?1:0);
    //TODO manage old paje format, see https://github.com/schnorr/poti/tree/master/examples
}

void prv2paje::PajeWriter::defineAndCreatePajeContainers()
{
    poti_DefineContainerType(PAJE_CONTAINER_DEF_ALIAS_ROOT, "0", PAJE_CONTAINER_DEF_NAME_ROOT);
    poti_DefineContainerType(PAJE_CONTAINER_DEF_ALIAS_NODE, PAJE_CONTAINER_DEF_NAME_ROOT, PAJE_CONTAINER_DEF_NAME_NODE);
    poti_DefineContainerType(PAJE_CONTAINER_DEF_ALIAS_CPU, PAJE_CONTAINER_DEF_NAME_NODE, PAJE_CONTAINER_DEF_NAME_CPU);
    poti_DefineContainerType(PAJE_CONTAINER_DEF_ALIAS_APP, PAJE_CONTAINER_DEF_NAME_CPU, PAJE_CONTAINER_DEF_NAME_APP);
    poti_DefineContainerType(PAJE_CONTAINER_DEF_ALIAS_TASK, PAJE_CONTAINER_DEF_NAME_APP, PAJE_CONTAINER_DEF_ALIAS_TASK);
    poti_DefineContainerType(PAJE_CONTAINER_DEF_ALIAS_THREAD, PAJE_CONTAINER_DEF_NAME_TASK, PAJE_CONTAINER_DEF_NAME_THREAD);
    poti_CreateContainer(0, PAJE_CONTAINER_ALIAS_ROOT, PAJE_CONTAINER_DEF_ALIAS_ROOT, "0", PAJE_CONTAINER_NAME_ROOT);
    int it=0;
    for (int i=0; i<prvMetaData->getNodes(); i++){
        string name(PAJE_CONTAINER_NAME_NODE_PREFIX);
        name+=to_string(i+1);
        string alias(PAJE_CONTAINER_ALIAS_NODE_PREFIX);
        alias+=to_string(i+1);
        poti_CreateContainer (0, alias.c_str(), PAJE_CONTAINER_DEF_ALIAS_NODE, PAJE_CONTAINER_ALIAS_ROOT, name.c_str());
        for (int j=0; j<prvMetaData->getCpus()->operator [](i); j++){
            it++;
            string name2(PAJE_CONTAINER_NAME_CPU_PREFIX);
            name2+=to_string(it);
            string alias2(PAJE_CONTAINER_ALIAS_CPU_PREFIX);
            alias2+=to_string(it);
            poti_CreateContainer (0, alias2.c_str(), PAJE_CONTAINER_DEF_ALIAS_CPU, alias.c_str(), name2.c_str());
            containerChain.push_back(map<int, map<int, map<int, bool > > >());
        }
    }
}

void prv2paje::PajeWriter::definePajeEvents()
{
    srand(time(0));
    poti_DefineLinkType(PAJE_PRVCOMMUNICATION_HW_THREAD_ALIAS, PAJE_CONTAINER_DEF_NAME_THREAD, PAJE_CONTAINER_DEF_NAME_THREAD, PAJE_CONTAINER_DEF_NAME_THREAD, PAJE_PRVCOMMUNICATION_HW_THREAD_NAME);
    poti_DefineLinkType(PAJE_PRVCOMMUNICATION_HW_TASK_ALIAS, PAJE_CONTAINER_DEF_NAME_TASK, PAJE_CONTAINER_DEF_NAME_THREAD, PAJE_CONTAINER_DEF_NAME_THREAD, PAJE_PRVCOMMUNICATION_HW_TASK_NAME);
    poti_DefineLinkType(PAJE_PRVCOMMUNICATION_HW_APP_ALIAS, PAJE_CONTAINER_DEF_NAME_APP, PAJE_CONTAINER_DEF_NAME_THREAD, PAJE_CONTAINER_DEF_NAME_THREAD, PAJE_PRVCOMMUNICATION_HW_APP_NAME);
    poti_DefineLinkType(PAJE_PRVCOMMUNICATION_HW_CPU_ALIAS, PAJE_CONTAINER_DEF_NAME_CPU, PAJE_CONTAINER_DEF_NAME_THREAD, PAJE_CONTAINER_DEF_NAME_THREAD, PAJE_PRVCOMMUNICATION_HW_CPU_NAME);
    poti_DefineLinkType(PAJE_PRVCOMMUNICATION_HW_ROOT_ALIAS, PAJE_CONTAINER_DEF_NAME_ROOT, PAJE_CONTAINER_DEF_NAME_THREAD, PAJE_CONTAINER_DEF_NAME_THREAD, PAJE_PRVCOMMUNICATION_HW_ROOT_NAME);
    poti_DefineLinkType(PAJE_PRVCOMMUNICATION_SW_THREAD_ALIAS, PAJE_CONTAINER_DEF_NAME_THREAD, PAJE_CONTAINER_DEF_NAME_THREAD, PAJE_CONTAINER_DEF_NAME_THREAD, PAJE_PRVCOMMUNICATION_SW_THREAD_NAME);
    poti_DefineLinkType(PAJE_PRVCOMMUNICATION_SW_TASK_ALIAS, PAJE_CONTAINER_DEF_NAME_TASK, PAJE_CONTAINER_DEF_NAME_THREAD, PAJE_CONTAINER_DEF_NAME_THREAD, PAJE_PRVCOMMUNICATION_SW_TASK_NAME);
    poti_DefineLinkType(PAJE_PRVCOMMUNICATION_SW_APP_ALIAS, PAJE_CONTAINER_DEF_NAME_APP, PAJE_CONTAINER_DEF_NAME_THREAD, PAJE_CONTAINER_DEF_NAME_THREAD, PAJE_PRVCOMMUNICATION_SW_APP_NAME);
    poti_DefineLinkType(PAJE_PRVCOMMUNICATION_SW_CPU_ALIAS, PAJE_CONTAINER_DEF_NAME_CPU, PAJE_CONTAINER_DEF_NAME_THREAD, PAJE_CONTAINER_DEF_NAME_THREAD, PAJE_PRVCOMMUNICATION_SW_CPU_NAME);
    poti_DefineLinkType(PAJE_PRVCOMMUNICATION_SW_ROOT_ALIAS, PAJE_CONTAINER_DEF_NAME_ROOT, PAJE_CONTAINER_DEF_NAME_THREAD, PAJE_CONTAINER_DEF_NAME_THREAD, PAJE_PRVCOMMUNICATION_SW_ROOT_NAME);
    poti_DefineStateType(PAJE_PRVSTATE_ALIAS, PAJE_CONTAINER_DEF_NAME_THREAD, PAJE_PRVSTATE_NAME);
    for (auto const &it : *(pcfParser->getPcfStates()->getValues())){
        string alias=to_string(it.first);
        string name=string("\"")+it.second+string("\"");
        string color= to_string((float) pcfParser->getPcfStates()->getColors()->operator [](it.first).getR()/255)+string(" ")+
                      to_string((float) pcfParser->getPcfStates()->getColors()->operator [](it.first).getG()/255)+string(" ")+
                      to_string((float) pcfParser->getPcfStates()->getColors()->operator [](it.first).getB()/255);
        poti_DefineEntityValue(alias.c_str(), PAJE_PRVSTATE_NAME, name.c_str(), color.c_str());
    }
    for (auto const &it : *(pcfParser->getPcfEvents())){
        string alias=to_string(it.first);
        string name=it.second->getLabel();
        if (it.second->getEventType()==pcfeventtype::State){
            poti_DefineStateType(alias.c_str(), PAJE_CONTAINER_DEF_NAME_THREAD, name.c_str());
            for (auto const &it2 : *(it.second->getValues())){
                string alias2=to_string(it2.first);
                string name2="\""+it2.second->getLabel()+"\"";
                string color= to_string((float) rand()/RAND_MAX)+string(" ")+
                              to_string((float) rand()/RAND_MAX)+string(" ")+
                              to_string((float) rand()/RAND_MAX);
                poti_DefineEntityValue(alias2.c_str(), alias.c_str(), name2.c_str(), color.c_str());
            }
        }else if (it.second->getEventType()==pcfeventtype::Variable){
            string color= to_string((float) rand()/RAND_MAX)+string(" ")+
                          to_string((float) rand()/RAND_MAX)+string(" ")+
                          to_string((float) rand()/RAND_MAX);
            poti_DefineVariableType(alias.c_str(), PAJE_CONTAINER_DEF_NAME_THREAD, name.c_str(), color.c_str());
        }
    }
}

PcfParser *prv2paje::PajeWriter::getPcfParser() const
{
    return pcfParser;
}

PrvMetaData *prv2paje::PajeWriter::getPrvMetaData() const
{
    return prvMetaData;
}

PrvParser *prv2paje::PajeWriter::getPrvParser() const
{
    return prvParser;
}

void prv2paje::PajeWriter::finalize()
{
    double timestamp=(double) prvMetaData->getDuration()/timeDivider;
    if (PajePendingEvent::LastTimestamp>timestamp){
        timestamp=PajePendingEvent::LastTimestamp;
    }
    pajePending.pushPendingEvents(timestamp);
    int i=0;
    for (auto const cpu: containerChain){
        int cpu_index=i++ +1;
        for (auto &app: cpu){
            for (auto &task: app.second){
                for (auto &thread: task.second){
                    string alias=to_string(cpu_index)+string(".")+to_string(app.first)+string(".")+to_string(task.first)+string(".")+to_string(thread.first);
                    poti_DestroyContainer(timestamp, PAJE_CONTAINER_DEF_ALIAS_THREAD, alias.c_str());
                }
                string alias=to_string(cpu_index)+string(".")+to_string(app.first)+string(".")+to_string(task.first);
                poti_DestroyContainer(timestamp, PAJE_CONTAINER_DEF_ALIAS_TASK, alias.c_str());
            }
            string alias=to_string(cpu_index)+string(".")+to_string(app.first);
            poti_DestroyContainer(timestamp, PAJE_CONTAINER_DEF_ALIAS_APP, alias.c_str());
        }
    }
    int it=0;
    for (i=0; i<prvMetaData->getNodes(); i++){
        string alias(PAJE_CONTAINER_ALIAS_NODE_PREFIX);
        alias+=to_string(i+1);
        for (int j=0; j<prvMetaData->getCpus()->operator [](i); j++){
            it++;
            string alias2(PAJE_CONTAINER_ALIAS_CPU_PREFIX);
            alias2+=to_string(it);
            poti_DestroyContainer (timestamp, PAJE_CONTAINER_DEF_ALIAS_CPU, alias2.c_str());
        }
        poti_DestroyContainer (timestamp, PAJE_CONTAINER_DEF_ALIAS_NODE, alias.c_str());
    }
    poti_DestroyContainer(timestamp, PAJE_CONTAINER_DEF_ALIAS_ROOT, PAJE_CONTAINER_ALIAS_ROOT);
    poti_close();
}

void prv2paje::PajeWriter::initialize()
{
    setTimeDivider();
    PajePendingCommunication::InitializeId();
    Message::Info("Generating header", 3);
    generatePajeHeader();
    Message::Info("Define and create Paje containers", 3);
    defineAndCreatePajeContainers();
    Message::Info("Define and create Paje event types", 3);
    definePajeEvents();
}

double prv2paje::PajeWriter::getTimeDivider()
{
    return timeDivider;
}

void prv2paje::PajeWriter::setTimeDivider()
{
    if (prvMetaData->getTimeUnit().compare(PRV_TIME_UNIT_SECONDS)==0){
        timeDivider=TIME_DIVIDER_SECONDS;
    }else if (prvMetaData->getTimeUnit().compare(PRV_TIME_UNIT_MILISECONDS)==0){
        timeDivider=TIME_DIVIDER_MILISECONDS;
    }else if (prvMetaData->getTimeUnit().compare(PRV_TIME_UNIT_MICROSECONDS)==0){
        timeDivider=TIME_DIVIDER_MICROSECONDS;
    }else if (prvMetaData->getTimeUnit().compare(PRV_TIME_UNIT_NANOSECONDS)==0){
        timeDivider=TIME_DIVIDER_NANOSECONDS;
    }
}

void prv2paje::PajeWriter::generate()
{
    prveventtype::PrvEventType type=prveventtype::Header;
    do{
        PrvEvent *prvEvent=prvParser->parseLine();
        type=prvEvent->getType();
        if (type==prveventtype::Events){
            PrvEvents* cast=static_cast<PrvEvents*> (prvEvent);
            push(cast);
        }
        else if (type==prveventtype::State){
            PrvState* cast=static_cast<PrvState*> (prvEvent);
            push(cast);
        }
        else if (type==prveventtype::Communications){
            PrvCommunications* cast=static_cast<PrvCommunications*> (prvEvent);
            push(cast);
        }
        else if (type==prveventtype::End){
            if (prvEvent->getLineNumber()>1){
                finalize();
            }
        }
        else if (type==prveventtype::Header){
            Message::Info("Parsing header", 2);
            initialize();
            Message::Info("Parsing body", 2);
        }
        else if (type==prveventtype::Critical){
            delete prvEvent;
            return;
        }
        delete prvEvent;
    }
    while(type!=prveventtype::End);
}

void prv2paje::PajeWriter::checkContainerChain(long int timestamp, int cpu, int app, int task, int thread)
{
    if (containerChain.operator [](cpu-1).count(app)==0){
        containerChain[cpu-1][app]= map<int, map<int, bool > >();
        string alias=to_string(cpu)+string(".")+to_string(app);
        string name=string(PAJE_CONTAINER_NAME_APP_PREFIX)+to_string(app);
        string parent=string(PAJE_CONTAINER_ALIAS_CPU_PREFIX)+to_string(cpu);
        poti_CreateContainer(timestamp, alias.c_str(), PAJE_CONTAINER_DEF_ALIAS_APP, parent.c_str(), alias.c_str());
    }
    if (containerChain.operator [](cpu-1).operator [](app).count(task)==0){
        containerChain[cpu-1][app][task]= map<int, bool >();
        string alias=to_string(cpu)+string(".")+to_string(app);
        string name=string(PAJE_CONTAINER_NAME_TASK_PREFIX)+to_string(task);
        string parent=alias;
        alias=alias+string(".")+to_string(task);
        poti_CreateContainer(timestamp, alias.c_str(), PAJE_CONTAINER_DEF_ALIAS_TASK, parent.c_str(), alias.c_str());
    }
    if (containerChain.operator [](cpu-1).operator [](app).operator [](task).count(thread)==0){
        containerChain[cpu-1][app][task][thread]=true;
        string alias=to_string(cpu)+string(".")+to_string(app)+string(".")+to_string(task);
        string name=PAJE_CONTAINER_NAME_THREAD_PREFIX+to_string(thread);
        string parent=alias;
        alias=alias+string(".")+to_string(thread);
        poti_CreateContainer(timestamp, alias.c_str(), PAJE_CONTAINER_DEF_ALIAS_THREAD, parent.c_str(), alias.c_str());
    }
}

