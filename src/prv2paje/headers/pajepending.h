#ifndef PAJEPENDING_H
#define PAJEPENDING_H

#include <list>
#include <string>
#include <iostream>
#include <poti.h>
#include "pajependingevent.h"
#include "pajependingendstate.h"

using namespace std;

namespace prv2paje{

    class PajePending
    {
    public:
        PajePending();
        void addPajePendingEvent(PajePendingEvent *pajePendingEvent);
        void pushPendingEvents(double timestamp);
    private:
        list<PajePendingEvent*> pajePendingEvents;
    };

}

#endif // PAJEPENDING_H
