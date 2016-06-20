#include "../headers/pajepending.h"

prv2paje::PajePending::PajePending()
{

}

void prv2paje::PajePending::addPajePendingEvent(prv2paje::PajePendingEvent *pajePendingEvent)
{
    pajePendingEvents.push_back(pajePendingEvent);
    pajePendingEvents.sort();
}

void prv2paje::PajePending::pushPendingEvents(long int timestamp)
{
    for (PajePendingEvent* it: pajePendingEvents){
        if (it->getTimestamp()>timestamp){
            break;
        }
        if (it->className().compare("PajePendingEndState")==0){
            poti_PopState  (it->getTimestamp(), it->getContainer().c_str(), it->getType().c_str());
        }
        pajePendingEvents.remove(it);
        delete it;
    }
}
