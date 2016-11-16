#ifndef PAJEPENDING_H
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

#define PAJEPENDING_H

#include <list>
#include <string>
#include <iostream>
#include <map>
#include <poti.h>
#include "pajependingevent.h"
#include "pajependingstartstate.h"
#include "pajependingendstate.h"
#include "pajependingvariable.h"
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
        void addPajePendingEvent(PajePendingVariable *pajePendingEvent);
        void finalizePajePendingVariables(double timestamp);
        void pushPendingEvents(double timestamp);
    private:
        static bool predicate(const PajePendingEvent* p1, const PajePendingEvent *p2);
        bool findStartState(PajePendingEvent *pajePendingEvent);
        list<PajePendingEvent*> pajePendingEvents;
        //map<string,map<string,PajePendingVariable*> > pajePendingVariables;
        map<string,map<string, bool> > hasBeenPushed;
        bool dirty;
    };

}

#endif // PAJEPENDING_H
