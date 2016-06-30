#include "pajepending.h"

prv2paje::PajePending::PajePending():dirty(true)
{

}

void prv2paje::PajePending::addPajePendingEvent(prv2paje::PajePendingEvent *pajePendingEvent)
{
    pajePendingEvents.push_back(pajePendingEvent);
    dirty=true;
}

/*void prv2paje::PajePending::addPajePendingEvent(prv2paje::PajePendingStartCommunication *pajePendingEvent)
{
    pajePendingEvent->pushMe();
}*/

int prv2paje::PajePending::addPajePendingEvent(prv2paje::PajePendingEndState *pajePendingEvent, bool check, bool fast)
{

    if (check){
        if((!fast)&&(!findStartState(pajePendingEvent))){
            delete pajePendingEvent;
            return -1;
        }else{
            pajePendingEvent->pushMe();
            delete pajePendingEvent;
            return 0;
        }
    }
    addPajePendingEvent(pajePendingEvent);
    return 0;
}


void prv2paje::PajePending::addPajePendingEvent(prv2paje::PajePendingStartState *pajePendingEvent, bool check, bool fast)
{
    pajePendingEvent->pushMe();
    if ((!fast)&&check){
        hasBeenPushed[pajePendingEvent->getContainer()][pajePendingEvent->getType()]=true;
    }else{
        delete pajePendingEvent;
    }

}

void prv2paje::PajePending::pushPendingEvents(double timestamp)
{
    list<PajePendingEvent*> toDelete;
    if (dirty){
        pajePendingEvents.sort( prv2paje::PajePending::predicate );
        dirty=false;
    }
    for (auto it =pajePendingEvents.begin(); it!=pajePendingEvents.end(); it++){
        if ((*it)->getTimestamp()>timestamp){
            break;
        }
        (*it)->pushMe();
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
    if (hasBeenPushed.count(pajePendingEvent->getContainer())>0){
        if (hasBeenPushed.at(pajePendingEvent->getContainer()).count(pajePendingEvent->getType())>0){
            return true;
        }
        return false;
    }
    else{
        return false;
    }

}


