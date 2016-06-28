#include "prvevents.h"


prvreader::PrvEvents::PrvEvents()
{
    type=prveventtype::Events;
}

prvreader::PrvEvents::~PrvEvents()
{
    delete events;
}

prvreader::PrvEvents::PrvEvents(int cpu, int app, int task, int thread, long timestamp, long lineNumber, map<int, string> *events):
    PrvEvent(cpu, app, task, thread, timestamp, lineNumber), events(events)
{
    type=prveventtype::Events;
}

map<int, string> *prvreader::PrvEvents::getEvents() const
{
    return events;
}

void prvreader::PrvEvents::setEvents(map<int, string> *value)
{
    events = value;
}
