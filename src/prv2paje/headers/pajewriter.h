#ifndef PAJEWRITER_H
#define PAJEWRITER_H

#include <iostream>
#include <fstream>
#include <map>
#include <poti.h>

#include "prvmetadata.h"


using namespace std;

namespace prv2paje{

    class PajeWriter
    {
    public:
        PajeWriter(string pajePath);
        ~PajeWriter();
        void setPrvMetaData(PrvMetaData prvMetaData);
        void pushEvents(int cpu, int app, int task, int thread, long timestamp, map<int, int>* events);
        void pushState(int cpu, int app, int task, int thread, long startTimstamp, long endTimestamp, int type);
        void processMetaData();
    private:
        string pajePath;
    };

}

#endif // PAJEWRITER_H
