#include "../headers/pajepending.h"

prv2paje::PajePending::PajePending()
{

}

void prv2paje::PajePending::addPajePendingEvent(prv2paje::PajePendingEndState *pajePendingEndState)
{
    pajePendingEvents.push_back(pajePendingEndState);
    pajePendingEvents.sort();
}

void prv2paje::PajePending::pushAllPendingEvents(long int timestamp)
{
    for (PajePendingEvent* it: pajePendingEvents){
        if (it->getTimestamp()>timestamp){
            break;
        }
        if (it->className().compare("PajePendingEndState")==0){
            poti_PopState  (it->getTimestamp(), it->getContainer(), it->getType());
        }
        pajePendingEvents.remove(it);
        delete it;
    }
}

long prv2paje::PajePending::getTimestamp() const
{
    return timestamp;
}

void prv2paje::PajePending::setTimestamp(long value)
{
    timestamp = value;
}

string prv2paje::PajePending::getContainer() const
{
    return container;
}

void prv2paje::PajePending::setContainer(const string &value)
{
    container = value;
}

string prv2paje::PajePending::getType() const
{
    return type;
}

void prv2paje::PajePending::setType(const string &value)
{
    type = value;
}
