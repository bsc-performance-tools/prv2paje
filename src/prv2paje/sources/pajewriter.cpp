#include "pajewriter.h"


prv2paje::PajeWriter::PajeWriter(string pajePath):pajePath(pajePath)
{

}

prv2paje::PajeWriter::~PajeWriter()
{

}

void prv2paje::PajeWriter::pushEvents(int cpu, int app, int task, int thread, long timestamp, map<int, int> *events)
{
    checkContainerChain(startTimestamp, cpu, app, task, thread);
    string container = cpu+"."+app+"."+task+"."+thread;
    string valueString=value;
    pajePending.pushAllPendingEvents(startTimestamp);
    for (auto &it: *events){
        int type = it.first;
        int value= it.second;
        string typeString = type;
        string valueString = value;
        if (pcfParser->getPcfEvents()->operator [](type)->getEventType()==State){
            if (value==PCF_EVENT_STATE_VALUE_END){
                poti_PopState (timestamp, container, typeString);
            }else{
                poti_PushState (timestamp, container, typeString, valueString);
            }
            //TODO continuar aqui!!!!!!!
        }

    }
    poti_PushState (startTimestamp, container, PAJE_PRVSTATE_ALIAS, valueString);
    pajePending.addPajePendingEvent(pajePendingEndState);
}

void prv2paje::PajeWriter::pushState(int cpu, int app, int task, int thread, long startTimestamp, long endTimestamp, int value)
{
    checkContainerChain(startTimestamp, cpu, app, task, thread);
    string container = cpu+"."+app+"."+task+"."+thread;
    string valueString=value;
    PajePendingEndState* pajePendingEndState=new PajePendingEndState(endTimestamp);
    pajePendingEndState->setContainer(container);
    pajePendingEndState->setType(PAJE_PRVSTATE_ALIAS);
    pajePending.pushAllPendingEvents(startTimestamp);
    poti_PushState (startTimestamp, container, PAJE_PRVSTATE_ALIAS, valueString);
    pajePending.addPajePendingEvent(pajePendingEndState);
}

void prv2paje::PajeWriter::generatePajeHeader()
{
    poti_open(pajePath.c_str());
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
        name+=(i+1);
        string alias(PAJE_CONTAINER_ALIAS_NODE_PREFIX);
        alias+=(i+1);
        poti_CreateContainer (0, alias.c_str(), PAJE_CONTAINER_DEF_ALIAS_NODE, PAJE_CONTAINER_ALIAS_ROOT, name.c_str());
        for (int j=0; j<prvMetaData->getCpus()->operator [](i); j++){
            it++;
            string name2(PAJE_CONTAINER_NAME_CPU_PREFIX);
            name2+=it;
            string alias2(PAJE_CONTAINER_ALIAS_CPU_PREFIX);
            alias2+=it;
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
        char* alias;
        sprintf(alias, "%d", it.first);
        const char* name=it.second.c_str();
        char* color;
        sprintf(color, "%f %f %f", (float) pcfParser->getPcfStates()->getColors()->operator [](it.first).getR()/255,
                (float) pcfParser->getPcfStates()->getColors()->operator [](it.first).getG()/255,
                (float) pcfParser->getPcfStates()->getColors()->operator [](it.first).getB()/255);
        poti_DefineEntityValue(alias, PAJE_PRVSTATE_NAME, name, color);
    }
    for (auto const &it : *(pcfParser->getPcfEvents())){
        char* alias;
        sprintf(alias, "%d", it.first);
        const char* name=it.second.c_str();
        if (it.second.getEventType()==State){
            poti_DefineStateType(alias, PAJE_CONTAINER_DEF_NAME_THREAD, name);
            for (auto const &it2 : *(it.second.getValues())){
                char* alias2;
                sprintf(alias2, "%d", it2.first);
                const char* name2=it2.second.c_str();
                char* color;
                sprintf(color, "%f %f %f", (float) rand()/RAND_MAX, (float) rand()/RAND_MAX, (float) rand()/RAND_MAX);
                poti_DefineEntityValue(alias2, alias, name2, color);
            }
        }else{
            poti_DefineVariableType(alias, PAJE_CONTAINER_DEF_NAME_THREAD, name);
        }
    }
}

void prv2paje::PajeWriter::removeAllContainers()
{
    for (auto cpu: containerChain){
        int cpu_index=distance(containerChain.begin(), cpu)+1;
        for (auto &app: cpu){
            for (auto &task: app.second){
                for (auto &thread: task.second){
                    string alias=cpu_index+"."+app.first+"."+task.first+"."+thread.first;
                    poti_DestroyContainer(prvMetaData->getDuration(), PAJE_CONTAINER_DEF_ALIAS_THREAD, alias.c_str());
                }
                string alias=cpu_index+"."+app.first+"."+task.first;
                poti_DestroyContainer(prvMetaData->getDuration(), PAJE_CONTAINER_DEF_ALIAS_TASK, alias.c_str());
            }
            string alias=cpu_index+"."+app.first;
            poti_DestroyContainer(prvMetaData->getDuration(), PAJE_CONTAINER_DEF_ALIAS_APP, alias.c_str());
        }
    }
    for (int i=0; i<prvMetaData->getNodes(); i++){
        string alias(PAJE_CONTAINER_ALIAS_NODE_PREFIX);
        alias+=(i+1);
        for (int j=0; j<prvMetaData->getCpus()->operator [](i); j++){
            it++;
            string alias2(PAJE_CONTAINER_ALIAS_CPU_PREFIX);
            alias2+=it;
            poti_DestroyContainer (prvMetaData->getDuration(), PAJE_CONTAINER_DEF_ALIAS_CPU, alias2.c_str());
        }
        poti_DestroyContainer (prvMetaData->getDuration(), PAJE_CONTAINER_DEF_ALIAS_NODE, alias.c_str());
    }
    poti_DestroyContainer(prvMetaData->getDuration(), PAJE_CONTAINER_DEF_ALIAS_ROOT, PAJE_CONTAINER_ALIAS_ROOT);
}

prv2paje::PcfParser *prv2paje::PajeWriter::getPcfParser() const
{
    return pcfParser;
}

void prv2paje::PajeWriter::setPcfParser(PcfParser *value)
{
    pcfParser = value;
}

prv2paje::PajeWriter::checkContainerChain(long int timestamp, int cpu, int app, int task, int thread)
{
    if (containerChain.operator [](cpu-1).count(app)==0){
        containerChain[cpu-1][app]= map<int, map<int, bool > >();
        string name=PAJE_CONTAINER_NAME_APP_PREFIX+app;
        string alias=cpu+"."+app;
        string parent=PAJE_CONTAINER_ALIAS_CPU_PREFIX+cpu;
        poti_CreateContainer(timestamp, alias.c_str(), PAJE_CONTAINER_DEF_ALIAS_APP, parent.c_str(), name.c_str());
    }
    if (containerChain.operator [](cpu-1).operator [](app).count(task)==0){
        containerChain[cpu-1][app][task]= map<int, bool >();
        string name=PAJE_CONTAINER_NAME_TASK_PREFIX+task;
        string alias=cpu+"."+app;
        string parent=alias;
        alias=alias+"."+task;
        poti_CreateContainer(timestamp, alias.c_str(), PAJE_CONTAINER_DEF_ALIAS_TASK, parent.c_str(), name.c_str());
    }
    if (containerChain.operator [](cpu-1).operator [](app).operator [](task).count(thread)==0){
        containerChain[cpu-1][app][task][thread]=true;
        string name=PAJE_CONTAINER_NAME_THREAD_PREFIX+thread;
        string alias=cpu+"."+app+"."+task;
        string parent=alias;
        alias=alias+"."+thread;
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
