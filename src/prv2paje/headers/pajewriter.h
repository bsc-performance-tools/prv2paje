#ifndef PAJEWRITER_H
#define PAJEWRITER_H

#include <cstdlib>
#include <iostream>
#include <ctime>

#include <fstream>
#include <map>
#include <poti.h>

#include "prv2paje_config.h"
#include <prvreader_config.h>
#include <prvmetadata.h>
#include <pcfparser.h>
#include "pajepending.h"
#include <message.h>
#include <interpretercomponent.h>
#include <prvparser.h>

using namespace std;
using namespace prvreader;

namespace prv2paje{

    class PajeWriter
    {
    public:
        PajeWriter(PrvParser* prvParser, string pajePath);
        PajeWriter(PrvParser* prvParser, string pajePath, bool basicHeader, bool oldHeader);
        ~PajeWriter();
        void push(PrvEvents*);
        void push(PrvState*);
        void push(PrvCommunications*);
        double getTimeDivider();
        void setTimeDivider();
        void generate();

        PrvParser *getPrvParser() const;

        PrvMetaData *getPrvMetaData() const;

        PcfParser *getPcfParser() const;


    private:
        void finalize();
        void initialize();
        void checkContainerChain(long int timestamp, int cpu, int app, int task, int thread);
        void generatePajeHeader();
        void defineAndCreatePajeContainers();
        void definePajeEvents();
        bool basicHeader;
        bool oldHeader;
        double timeDivider;
        string pajePath;
        PajePending pajePending;
        vector<map<int, map<int, map<int, bool > > > > containerChain;
        PrvParser *prvParser;
        PrvMetaData *prvMetaData;
        PcfParser *pcfParser;
    };

}

#endif // PAJEWRITER_H
