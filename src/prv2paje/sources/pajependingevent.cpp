#include "pajependingevent.h"

prv2paje::PajePendingEvent::PajePendingEvent()
{

}

prv2paje::PajePendingEvent::PajePendingEvent(long timestamp):timestamp(timestamp)
{

}

bool operator>(const prv2paje::PajePendingEvent &object1, const prv2paje::PajePendingEvent &object2)
{
    return object1.getTimestamp()>object2.getTimestamp();
}

bool operator<=(const prv2paje::PajePendingEvent &object1, const prv2paje::PajePendingEvent &object2)
{
    return object1.getTimestamp()<=object2.getTimestamp();
}

bool operator<(const prv2paje::PajePendingEvent &object1, const prv2paje::PajePendingEvent &object2)
{
    return object1.getTimestamp()<object2.getTimestamp();
}

bool operator>=(const prv2paje::PajePendingEvent &object1, const prv2paje::PajePendingEvent &object2)
{
    return object1.getTimestamp()>=object2.getTimestamp();
}

bool operator==(const prv2paje::PajePendingEvent &object1, const prv2paje::PajePendingEvent &object2)
{
    return object1.getTimestamp()==object2.getTimestamp();
}

bool operator!=(const prv2paje::PajePendingEvent &object1, const prv2paje::PajePendingEvent &object2)
{
    return object1.getTimestamp()!=object2.getTimestamp();
}

long prv2paje::PajePendingEvent::getTimestamp() const
{
    return timestamp;
}

void prv2paje::PajePendingEvent::setTimestamp(long value)
{
    timestamp = value;
}

string prv2paje::PajePendingEvent::getContainer() const
{
    return container;
}

void prv2paje::PajePendingEvent::setContainer(const string &value)
{
    container = value;
}

string prv2paje::PajePendingEvent::getType() const
{
    return type;
}

void prv2paje::PajePendingEvent::setType(const string &value)
{
    type = value;
}
