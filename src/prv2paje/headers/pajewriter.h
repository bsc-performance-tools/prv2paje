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

using namespace std;
using namespace prvreader;

namespace prv2paje{

    class PajeWriter: public InterpreterComponent
    {
    public:
        PajeWriter(string pajePath);
        PajeWriter(string pajePath, bool basicHeader, bool oldHeader);
        ~PajeWriter();
        void pushEvents(int cpu, int app, int task, int thread, long timestamp, map<int, string>* events, long lineNumber);
        void pushState(int cpu, int app, int task, int thread, long startTimestamp, long endTimestamp, string value, long lineNumber);
        void pushCommunications(int cpu1, int app1, int task1, int thread1, int cpu2, int app2, int task2, int thread2,
                                long startTimestampSW, long startTimestampHW, long endTimestampSW, long endTimestampHW, string value, long lineNumber);
        void finalize();
        void initialize();
        double getTimeDivider();
        void setTimeDivider();

    private:
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
    };

}

#endif // PAJEWRITER_H
