#ifndef PAJEWRITER_H
#define PAJEWRITER_H

#include <iostream>
#include <fstream>
#include <map>
#include <poti.h>

#include "config.h"
#include "prvmetadata.h"
#include "pcfparser.h"

using namespace std;

namespace prv2paje{

    class PajeWriter
    {
    public:
        PajeWriter(string pajePath);
        ~PajeWriter();
        void pushEvents(int cpu, int app, int task, int thread, long timestamp, map<int, int>* events);
        void pushState(int cpu, int app, int task, int thread, long startTimstamp, long endTimestamp, int type);
        void generatePajeHeader();
        void definePajeContainers();
        void definePajeStates();
        PrvMetaData *getPrvMetaData() const;
        void setPrvMetaData(PrvMetaData *value);

        PcfParser *getPcfParser() const;
        void setPcfParser(PcfParser *value);

    private:
        string pajePath;
        PrvMetaData *prvMetaData;
        PcfParser *pcfParser;
    };

}

#endif // PAJEWRITER_H
