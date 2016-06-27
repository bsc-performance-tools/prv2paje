#ifndef INTERPRETERCOMPONENT_H
#define INTERPRETERCOMPONENT_H

#include <cstdlib>
#include <iostream>
#include <ctime>

#include <fstream>
#include <map>

#include "prvreader_config.h"
#include "prvmetadata.h"
#include "pcfparser.h"
#include "message.h"

using namespace std;

namespace prvreader{

    class InterpreterComponent
    {
    public:
        virtual void pushEvents(int cpu, int app, int task, int thread, double timestamp, map<int, string>* events, long lineNumber)=0;
        virtual void pushState(int cpu, int app, int task, int thread, double startTimestamp, double endTimestamp, string value, long lineNumber)=0;
        virtual void pushCommunications(int cpu1, int app1, int task1, int thread1, int cpu2, int app2, int task2, int thread2,
                                        double startTimestampSW, double startTimestampHW, double endTimestampSW, double endTimestampHW, string value, long lineNumber)=0;
        virtual void initialize()=0;
        virtual void finalize()=0;

        PrvMetaData *getPrvMetaData() const;
        void setPrvMetaData(PrvMetaData *value);

        PcfParser *getPcfParser() const;
        void setPcfParser(PcfParser *value);

    protected:
        PrvMetaData *prvMetaData;
        PcfParser *pcfParser;
    };

}

#endif // INTERPRETERCOMPONENT_H
