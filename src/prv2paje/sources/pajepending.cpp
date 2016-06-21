#include "pajepending.h"

prv2paje::PajePending::PajePending()
{

}

void prv2paje::PajePending::addPajePendingEvent(prv2paje::PajePendingEvent *pajePendingEvent)
{
    pajePendingEvents.push_back(pajePendingEvent);
    pajePendingEvents.sort();
}

void prv2paje::PajePending::pushPendingEvents(double timestamp)
{
    list<PajePendingEvent*> toDelete;
    for (auto it =pajePendingEvents.begin(); it!=pajePendingEvents.end(); it++){
        if ((*it)->getTimestamp()>timestamp){
            break;
        }
        if ((*it)->className().compare("PajePendingEndState")==0){
            poti_PopState  ((*it)->getTimestamp(), (*it)->getContainer().c_str(), (*it)->getType().c_str());
        }
        toDelete.push_back(*it);
        it=pajePendingEvents.erase(it);
    }
    for (PajePendingEvent* it: toDelete){
        delete it;
    }
}
