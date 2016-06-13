#include "pajewriter.h"


prv2paje::PajeWriter::PajeWriter(string pajePath):pajePath(pajePath)
{

}

prv2paje::PajeWriter::~PajeWriter()
{

}

void prv2paje::PajeWriter::setPrvMetaData(PrvMetaData prvMetaData)
{

}

void prv2paje::PajeWriter::pushEvents(int cpu, int app, int task, int thread, long timestamp, map<int, int> *events)
{

}

void prv2paje::PajeWriter::pushState(int cpu, int app, int task, int thread, long startTimstamp, long endTimestamp, int type)
{

}

void prv2paje::PajeWriter::processMetaData()
{
    poti_open(pajePath.c_str());
    poti_header(0, 0);
    //TODO maybe manage old paje format, see https://github.com/schnorr/poti/tree/master/examples
}
