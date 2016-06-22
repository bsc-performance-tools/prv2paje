#ifndef PAJEPENDINGENDSTATE_H
#define PAJEPENDINGENDSTATE_H

#include <string>

#include "pajependingevent.h"

using namespace std;

namespace prv2paje{

    class PajePendingEndState: public PajePendingEvent
    {
    public:
        PajePendingEndState();
        PajePendingEndState(double timestamp);
        string className();
    };

}

#endif // PAJEPENDINGENDSTATE_H
