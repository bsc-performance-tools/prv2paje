#include "pajepending.h"

prv2paje::PajePending::PajePending()
{

}

void prv2paje::PajePending::addPajePendingEvent(prv2paje::PajePendingEvent *pajePendingEvent)
{
    pajePendingEvents.push_back(pajePendingEvent);
}

int prv2paje::PajePending::addPajePendingEvent(prv2paje::PajePendingEndState *pajePendingEvent, bool check)
{

    if (check&&!findStartState(pajePendingEvent)){
        return -1;
    }
    addPajePendingEvent(pajePendingEvent);
    return 0;
}


void prv2paje::PajePending::addPajePendingEvent(prv2paje::PajePendingStartState *pajePendingEvent, bool check)
{
    if (check){
        pajePendingStartStates.push_back(pajePendingEvent);
    }
    poti_PushState (pajePendingEvent->getTimestamp(), pajePendingEvent->getContainer().c_str(), pajePendingEvent->getType().c_str(), pajePendingEvent->getValue().c_str());
}




void prv2paje::PajePending::pushPendingEvents(double timestamp)
{
    list<PajePendingEvent*> toDelete;
    pajePendingEvents.sort( prv2paje::PajePending::predicate );
    for (auto it =pajePendingEvents.begin(); it!=pajePendingEvents.end(); it++){
        if ((*it)->getTimestamp()>timestamp){
            break;
        }
        if ((*it)->className().compare("PajePendingEndState")==0){
            poti_PopState((*it)->getTimestamp(), (*it)->getContainer().c_str(), (*it)->getType().c_str());
        }
        else if ((*it)->className().compare("PajePendingEndCommunication")==0){
            PajePendingEndCommunication* cast = dynamic_cast<PajePendingEndCommunication*> (*it);
            poti_EndLink(cast->getTimestamp(), cast->getContainer().c_str(), cast->getType().c_str(), cast->getSubContainer().c_str(), cast->getValue().c_str(), cast->getKey().c_str());
        }
        else if ((*it)->className().compare("PajePendingStartCommunication")==0){
            PajePendingStartCommunication* cast = dynamic_cast<PajePendingStartCommunication*> (*it);
            poti_StartLink(cast->getTimestamp(), cast->getContainer().c_str(), cast->getType().c_str(), cast->getSubContainer().c_str(), cast->getValue().c_str(), cast->getKey().c_str());
        }
        toDelete.push_back(*it);
        it=pajePendingEvents.erase(it);
    }
    for (PajePendingEvent* it: toDelete){
        delete it;
    }
}

bool prv2paje::PajePending::predicate(const prv2paje::PajePendingEvent *p1, const prv2paje::PajePendingEvent *p2)
{
    return p1->getTimestamp()<p2->getTimestamp();
}

bool prv2paje::PajePending::findStartState(prv2paje::PajePendingEvent *pajePendingEvent)
{
    bool ret=false;
    list<PajePendingEvent*> toDelete;
    if (pajePendingStartStates.empty())
        return ret;
    for (auto it =pajePendingStartStates.begin(); it!=pajePendingStartStates.end(); it++){
        if (((*it)->getContainer().compare(pajePendingEvent->getContainer())==0)&&((*it)->getType().compare(pajePendingEvent->getType())==0)){
            toDelete.push_back(*it);
            it=pajePendingStartStates.erase(it);
            ret=true;
            break;
        }
    }
    for (PajePendingEvent* it2: toDelete){
        delete it2;
    }
    return ret;
}


