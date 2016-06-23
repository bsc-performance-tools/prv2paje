#ifndef PAJEPENDING_H
#define PAJEPENDING_H

#include <list>
#include <string>
#include <iostream>
#include <poti.h>
#include "pajependingevent.h"
#include "pajependingendstate.h"
#include "pajependingstartcommunication.h"
#include "pajependingendcommunication.h"
#include "message.h"

using namespace std;

namespace prv2paje{

    class PajePending
    {
    public:
        PajePending();
        void addPajePendingEvent(PajePendingEvent *pajePendingEvent);
        void pushPendingEvents(double timestamp);
    private:
        static bool predicate(const PajePendingEvent* p1, const PajePendingEvent *p2);
        list<PajePendingEvent*> pajePendingEvents;
    };

}

#endif // PAJEPENDING_H
