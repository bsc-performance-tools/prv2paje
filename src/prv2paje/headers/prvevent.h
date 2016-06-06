#ifndef PRVEVENT_H
#define PRVEVENT_H

#include "pcfevents.h"

namespace prv2paje{

    class PrvEvent
    {
    public:
        PrvEvent();
    private:
        int cpu;
        int app;
        int taks;
        int thread;
        long int timestamp;
        PcfEvents* type;
        int intType;
        PcfValue* value;
        int intValue;
    };

}

#endif // PRVEVENT_H
