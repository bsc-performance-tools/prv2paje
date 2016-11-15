/*****************************************************************************\
 *                        ANALYSIS PERFORMANCE TOOLS                         *
 *                                 prvreader                                 *
 *      Libraries and Tools for reading and converting Paraver traces        *
 *****************************************************************************
 *     ___     This library is free software; you can redistribute it and/or *
 *    /  __         modify it under the terms of the GNU LGPL as published   *
 *   /  /  _____    by the Free Software Foundation; either version 3        *
 *  /  /  /     \   of the License, or (at your option) any later version.   *
 * (  (  ( B S C )                                                           *
 *  \  \  \_____/   This library is distributed in hope that it will be      *
 *   \  \__         useful but WITHOUT ANY WARRANTY; without even the        *
 *    \___          implied warranty of MERCHANTABILITY or FITNESS FOR A     *
 *                  PARTICULAR PURPOSE. See the GNU LGPL for more details.   *
 *                                                                           *
 * You should have received a copy of the GNU Lesser General Public License  *
 * along with this library; if not, write to the Free Software Foundation,   *
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA          *
 * The GNU LEsser General Public License is contained in the file COPYING.   *
 *                                 ---------                                 *
 *   Barcelona Supercomputing Center - Centro Nacional de Supercomputacion   *
\*****************************************************************************/

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

void prv2paje::PajePending::finalizePajePendingVariables(double timestamp)
{
    list<PajePendingEvent*> toDelete;
    for (auto it: pajePendingVariables){
        for (auto it2: it.second){
            (*(it2.second)).setTimestamp(timestamp);
            (*(it2.second)).pushMe();
            toDelete.push_back((it2.second));
        }
    }
    for (PajePendingEvent* it: toDelete){
        delete it;
    }
}

void prv2paje::PajePending::addPajePendingEvent(prv2paje::PajePendingVariable *pajePendingEvent)
{
    if (pajePendingVariables.size()==0||pajePendingVariables.count(pajePendingEvent->getContainer())==0||
            pajePendingVariables.at(pajePendingEvent->getContainer()).count(pajePendingEvent->getType())==0){
        pajePendingEvent->pushMe();
        pajePendingVariables[pajePendingEvent->getContainer()][pajePendingEvent->getType()]=pajePendingEvent;
    }
    PajePendingVariable *pajePendingVariable=pajePendingVariables[pajePendingEvent->getContainer()][pajePendingEvent->getType()];
    pajePendingVariable->setTimestamp(pajePendingEvent->getTimestamp());
    pajePendingVariable->pushMe();
    delete pajePendingVariable;
    pajePendingVariables[pajePendingEvent->getContainer()][pajePendingEvent->getType()]=pajePendingEvent;
}

void prv2paje::PajePending::pushPendingEvents(double timestamp)
{
    list<PajePendingEvent*> toDelete;
    if (dirty){
        pajePendingEvents.sort( prv2paje::PajePending::predicate );
        dirty=false;
    }
    for (auto it =pajePendingEvents.begin(); it!=pajePendingEvents.end();){
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


