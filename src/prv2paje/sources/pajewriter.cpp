#include "pajewriter.h"


prv2paje::PajeWriter::PajeWriter(string pajePath):pajePath(pajePath)
{

}

prv2paje::PajeWriter::~PajeWriter()
{

}

void prv2paje::PajeWriter::pushEvents(int cpu, int app, int task, int thread, long timestamp, map<int, int> *events)
{

}

void prv2paje::PajeWriter::pushState(int cpu, int app, int task, int thread, long startTimstamp, long endTimestamp, int type)
{

}

void prv2paje::PajeWriter::generatePajeHeader()
{
    poti_open(pajePath.c_str());
    poti_header(0, 0);
    //TODO manage old paje format, see https://github.com/schnorr/poti/tree/master/examples




}

void prv2paje::PajeWriter::definePajeContainers()
{
    poti_DefineContainerType(PAJE_CONTAINER_ALIAS_ROOT, "0", PAJE_CONTAINER_NAME_ROOT);
    poti_DefineContainerType(PAJE_CONTAINER_ALIAS_NODES, PAJE_CONTAINER_NAME_ROOT, PAJE_CONTAINER_NAME_NODES);
    poti_DefineContainerType(PAJE_CONTAINER_ALIAS_CPU, PAJE_CONTAINER_NAME_NODES, PAJE_CONTAINER_NAME_CPU);
    poti_DefineContainerType(PAJE_CONTAINER_ALIAS_APP, PAJE_CONTAINER_NAME_CPU, PAJE_CONTAINER_NAME_APP);
    poti_DefineContainerType(PAJE_CONTAINER_ALIAS_TASK, PAJE_CONTAINER_NAME_APP, PAJE_CONTAINER_ALIAS_TASK);
    poti_DefineContainerType(PAJE_CONTAINER_ALIAS_THREAD, PAJE_CONTAINER_NAME_TASK, PAJE_CONTAINER_NAME_THREAD);
}

void prv2paje::PajeWriter::definePajeStates()
{
    poti_DefineStateType(PAJE_PRVSTATE_ALIAS, PAJE_CONTAINER_NAME_THREAD, PAJE_PRVSTATE_NAME);
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


    //TODO to be continued
/**

    for (auto const &it : pcfParser->getPcfEvents()){
        if (it.second.getEventType()==State){
            char* buff;
            sprintf(buff, "%d", it.first);
            poti_DefineStateType(buff, PAJE_CONTAINER_NAME_THREAD, buff);
        }
    }

    **/
}

prv2paje::PcfParser *prv2paje::PajeWriter::getPcfParser() const
{
    return pcfParser;
}

void prv2paje::PajeWriter::setPcfParser(PcfParser *value)
{
    pcfParser = value;
}

prv2paje::PrvMetaData *prv2paje::PajeWriter::getPrvMetaData() const
{
    return prvMetaData;
}

void prv2paje::PajeWriter::setPrvMetaData(PrvMetaData *value)
{
    prvMetaData = value;
}
