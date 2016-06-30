#ifndef PAJEPENDING_H
#define PAJEPENDING_H

#include <list>
#include <string>
#include <iostream>
#include <map>
#include <poti.h>
#include "pajependingevent.h"
#include "pajependingstartstate.h"
#include "pajependingendstate.h"
#include "pajependingstartcommunication.h"
#include "pajependingendcommunication.h"
#include <message.h>

using namespace std;
using namespace prvreader;

namespace prv2paje{

    class PajePending
    {
    public:
        PajePending();
        void addPajePendingEvent(PajePendingEvent *pajePendingEvent);
        //void addPajePendingEvent(PajePendingStartCommunication *pajePendingEvent);
        int addPajePendingEvent(PajePendingEndState *pajePendingEvent, bool check, bool fast);
        void addPajePendingEvent(PajePendingStartState *pajePendingEvent, bool check, bool fast);
        void pushPendingEvents(double timestamp);
    private:
        static bool predicate(const PajePendingEvent* p1, const PajePendingEvent *p2);
        bool findStartState(PajePendingEvent *pajePendingEvent);
        list<PajePendingEvent*> pajePendingEvents;
        map<string,map<string, bool> > hasBeenPushed;
        bool dirty;
    };

}

#endif // PAJEPENDING_H
