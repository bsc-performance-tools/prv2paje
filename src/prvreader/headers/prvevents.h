#ifndef PRVEVENTS_H
#define PRVEVENTS_H

#include <map>
#include <string>
#include "prvevent.h"

using namespace std;

namespace prvreader{

    class PrvEvents : public PrvEvent
    {
    public:
        PrvEvents();
        ~PrvEvents();
        PrvEvents(int cpu, int app, int task, int thread, long timestamp, long lineNumber, map<int, string> *events);
        map<int, string> *events;
        map<int, string> *getEvents() const;
        void setEvents(map<int, string> *value);
    };

}

#endif // PRVEVENTS_H
