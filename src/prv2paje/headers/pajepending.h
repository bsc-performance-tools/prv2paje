#ifndef PAJEPENDING_H
#define PAJEPENDING_H

#include <list>
#include <string>
#include <poti.h>
#include "pajependingevent.h"
#include "pajependingendstate.h"

using namespace std;

namespace prv2paje{

    class PajePending
    {
    public:
        PajePending();
        void addPajePendingEvent(PajePendingEvent *pajePendingEndState);
        void addPajePendingEvent(PajePendingEvent *pajePendingEvent);
        void pushAllPendingEvents(long int timestamp);
    private:
        list<PajePendingEvent*> pajePendingEvents;
    };

}

#endif // PAJEPENDING_H
