#ifndef PAJEPENDINGENDSTATE_H
#define PAJEPENDINGENDSTATE_H

#include <string>

#include "pajependingevent.h"

using namespace std;

namespace prv2paje{

    class PajePendingEndState: PajePendingEvent
    {
    public:
        PajePendingEndState();
        PajePendingEndState(int long timestamp);
        string className();
    };

}

#endif // PAJEPENDINGENDSTATE_H
