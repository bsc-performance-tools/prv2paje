#include "pajewriter.h"


prv2paje::PajeWriter::PajeWriter(string pajePath):pajePath(pajePath)
{

}

prv2paje::PajeWriter::~PajeWriter()
{

}

void prv2paje::PajeWriter::pushEvents(int cpu, int app, int task, int thread, double timestamp, map<int, string> *events, long lineNumber)
{
    checkContainerChain(timestamp, cpu, app, task, thread);
    string container = to_string(cpu)+string(".")+to_string(app)+string(".")+to_string(task)+string(".")+to_string(thread);
    pajePending.pushPendingEvents(timestamp);
    for (auto &it: *events){
        int type = it.first;
        string typeString = to_string(type);
        string value = it.second;
        if (pcfParser->getPcfEvents()->count(type)==0){
            PcfEvents* unknownEvent=new PcfEvents(0,type);
            unknownEvent->setEventType(Variable);
            unknownEvent->setLabel(to_string(type));
            pcfParser->getPcfEvents()->operator [](type)=unknownEvent;
            Message::Warning("line " + to_string(lineNumber)+ ". Undefined event type. Type: "+to_string(type)+" Value: "+value+
                            ". Unable to determine its semantic. Will be defined as a variable. We recommend to add this event type in the trace pcf file.");
            string color= to_string((float) rand()/RAND_MAX)+string(" ")+
                          to_string((float) rand()/RAND_MAX)+string(" ")+
                          to_string((float) rand()/RAND_MAX);
            poti_DefineVariableType(typeString.c_str(), PAJE_CONTAINER_DEF_NAME_THREAD, typeString.c_str(), color.c_str());
        }
        if (pcfParser->getPcfEvents()->operator [](type)->getEventType()==State){
            if (value.compare(PCF_EVENT_STATE_VALUE_END_STRING)){

                poti_PopState (timestamp, container.c_str(), typeString.c_str());
            }else{
                poti_PushState (timestamp, container.c_str(), typeString.c_str(), value.c_str());
            }
        }else if (pcfParser->getPcfEvents()->operator [](type)->getEventType()==Variable){
            try{
                long long valueLong=stoll(value.c_str());
                poti_SetVariable (timestamp, container.c_str(), typeString.c_str(), valueLong);
            }catch (const std::out_of_range& err) {
                Message::Warning("line "+ to_string(lineNumber)+". Value out of range value. Type: "+to_string(type)+" Value: "+value+". Event will be dropped...");
            }
        }
    }
}

void prv2paje::PajeWriter::pushState(int cpu, int app, int task, int thread, double startTimestamp, double endTimestamp, string value, long lineNumber)
{
    checkContainerChain(startTimestamp, cpu, app, task, thread);
    string container = to_string(cpu)+string(".")+to_string(app)+string(".")+to_string(task)+string(".")+to_string(thread);
    PajePendingEndState* pajePendingEndState=new PajePendingEndState(endTimestamp);
    pajePendingEndState->setContainer(container);
    pajePendingEndState->setType(PAJE_PRVSTATE_ALIAS);
    pajePending.pushPendingEvents(startTimestamp);
    poti_PushState (startTimestamp, container.c_str(), PAJE_PRVSTATE_ALIAS, value.c_str());
    pajePending.addPajePendingEvent(pajePendingEndState);
}

void prv2paje::PajeWriter::generatePajeHeader()
{
    FILE *file = fopen(pajePath.c_str(), "w");
    if (!file){
      Message::Error("cannot generate file "+pajePath);
    }
    int err=poti_init(file);
    poti_header(0, 0);
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
        string name="\""+it.second->getLabel()+"\"";
        if (it.second->getEventType()==State){
            poti_DefineStateType(alias.c_str(), PAJE_CONTAINER_DEF_NAME_THREAD, name.c_str());
            for (auto const &it2 : *(it.second->getValues())){
                string alias2=to_string(it2.first);
                string name2=it2.second->getLabel();
                string color= to_string((float) rand()/RAND_MAX)+string(" ")+
                              to_string((float) rand()/RAND_MAX)+string(" ")+
                              to_string((float) rand()/RAND_MAX);
                poti_DefineEntityValue(alias2.c_str(), alias.c_str(), name2.c_str(), color.c_str());
            }
        }else if (it.second->getEventType()==Variable){
            string color= to_string((float) rand()/RAND_MAX)+string(" ")+
                          to_string((float) rand()/RAND_MAX)+string(" ")+
                          to_string((float) rand()/RAND_MAX);
            poti_DefineVariableType(alias.c_str(), PAJE_CONTAINER_DEF_NAME_THREAD, name.c_str(), color.c_str());
        }
    }
}

void prv2paje::PajeWriter::finalize()
{
    pajePending.pushPendingEvents(prvMetaData->getStandardDuration());
    int i=0;
    for (auto const cpu: containerChain){
        int cpu_index=i++ +1;
        for (auto &app: cpu){
            for (auto &task: app.second){
                for (auto &thread: task.second){
                    string alias=to_string(cpu_index)+string(".")+to_string(app.first)+string(".")+to_string(task.first)+string(".")+to_string(thread.first);
                    poti_DestroyContainer(prvMetaData->getStandardDuration(), PAJE_CONTAINER_DEF_ALIAS_THREAD, alias.c_str());
                }
                string alias=to_string(cpu_index)+string(".")+to_string(app.first)+string(".")+to_string(task.first);
                poti_DestroyContainer(prvMetaData->getStandardDuration(), PAJE_CONTAINER_DEF_ALIAS_TASK, alias.c_str());
            }
            string alias=to_string(cpu_index)+string(".")+to_string(app.first);
            poti_DestroyContainer(prvMetaData->getStandardDuration(), PAJE_CONTAINER_DEF_ALIAS_APP, alias.c_str());
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
            poti_DestroyContainer (prvMetaData->getStandardDuration(), PAJE_CONTAINER_DEF_ALIAS_CPU, alias2.c_str());
        }
        poti_DestroyContainer (prvMetaData->getStandardDuration(), PAJE_CONTAINER_DEF_ALIAS_NODE, alias.c_str());
    }
    poti_DestroyContainer(prvMetaData->getStandardDuration(), PAJE_CONTAINER_DEF_ALIAS_ROOT, PAJE_CONTAINER_ALIAS_ROOT);
    poti_close();
}

prv2paje::PcfParser *prv2paje::PajeWriter::getPcfParser() const
{
    return pcfParser;
}

void prv2paje::PajeWriter::setPcfParser(PcfParser *value)
{
    pcfParser = value;
}

void prv2paje::PajeWriter::checkContainerChain(long int timestamp, int cpu, int app, int task, int thread)
{
    if (containerChain.operator [](cpu-1).count(app)==0){
        containerChain[cpu-1][app]= map<int, map<int, bool > >();
        string name=string(PAJE_CONTAINER_NAME_APP_PREFIX)+to_string(app);
        string alias=to_string(cpu)+string(".")+to_string(app);
        string parent=string(PAJE_CONTAINER_ALIAS_CPU_PREFIX)+to_string(cpu);
        poti_CreateContainer(timestamp, alias.c_str(), PAJE_CONTAINER_DEF_ALIAS_APP, parent.c_str(), name.c_str());
    }
    if (containerChain.operator [](cpu-1).operator [](app).count(task)==0){
        containerChain[cpu-1][app][task]= map<int, bool >();
        string name=string(PAJE_CONTAINER_NAME_TASK_PREFIX)+to_string(task);
        string alias=to_string(cpu)+string(".")+to_string(app);
        string parent=alias;
        alias=alias+string(".")+to_string(task);
        poti_CreateContainer(timestamp, alias.c_str(), PAJE_CONTAINER_DEF_ALIAS_TASK, parent.c_str(), name.c_str());
    }
    if (containerChain.operator [](cpu-1).operator [](app).operator [](task).count(thread)==0){
        containerChain[cpu-1][app][task][thread]=true;
        string name=PAJE_CONTAINER_NAME_THREAD_PREFIX+to_string(thread);
        string alias=to_string(cpu)+string(".")+to_string(app)+string(".")+to_string(task);
        string parent=alias;
        alias=alias+string(".")+to_string(thread);
        poti_CreateContainer(timestamp, alias.c_str(), PAJE_CONTAINER_DEF_ALIAS_THREAD, parent.c_str(), name.c_str());
    }
}



prv2paje::PrvMetaData *prv2paje::PajeWriter::getPrvMetaData() const
{
    return prvMetaData;
}

void prv2paje::PajeWriter::setPrvMetaData(PrvMetaData *value)
{
    prvMetaData = value;
}
