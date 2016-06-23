#ifndef PAJEWRITER_H
#define PAJEWRITER_H

#include <cstdlib>
#include <iostream>
#include <ctime>

#include <fstream>
#include <map>
#include <poti.h>

#include "config.h"
#include "prvmetadata.h"
#include "pcfparser.h"
#include "pajepending.h"
#include "message.h"
#include "interpretercomponent.h"

using namespace std;

namespace prv2paje{

    class PajeWriter: public InterpreterComponent
    {
    public:
        PajeWriter(string pajePath);
        PajeWriter(string pajePath, bool basicHeader, bool oldHeader);
        ~PajeWriter();
        void pushEvents(int cpu, int app, int task, int thread, double timestamp, map<int, string>* events, long lineNumber);
        void pushState(int cpu, int app, int task, int thread, double startTimestamp, double endTimestamp, string value, long lineNumber);
        void pushCommunications(int cpu1, int app1, int task1, int thread1, int cpu2, int app2, int task2, int thread2,
                                double startTimestampSW, double startTimestampHW, double endTimestampSW, double endTimestampHW, string value, long lineNumber);
        void finalize();
        void initialize();

    private:
        void checkContainerChain(long int timestamp, int cpu, int app, int task, int thread);
        void generatePajeHeader();
        void defineAndCreatePajeContainers();
        void definePajeEvents();
        bool basicHeader;
        bool oldHeader;
        string pajePath;
        PajePending pajePending;
        vector<map<int, map<int, map<int, bool > > > > containerChain;
    };

}

#endif // PAJEWRITER_H
