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

#ifndef PAJEPENDINGEVENT_H
#define PAJEPENDINGEVENT_H

#include <string>
#include "prv2paje_config.h"
#include <poti.h>

using namespace std;

namespace prv2paje{

    class PajePendingEvent
    {
    public:
        PajePendingEvent();
        PajePendingEvent(double timestamp);
        friend bool operator> (const PajePendingEvent &object1, const PajePendingEvent &object2);
        friend bool operator<= (const PajePendingEvent &object1, const PajePendingEvent &object2);
        friend bool operator< (const PajePendingEvent &object1, const PajePendingEvent &object2);
        friend bool operator>= (const PajePendingEvent &object1, const PajePendingEvent &object2);
        friend bool operator== (const PajePendingEvent &object1, const PajePendingEvent &object2);
        friend bool operator!= (const PajePendingEvent &object1, const PajePendingEvent &object2);

        virtual string className() = 0;
        virtual void pushMe() = 0;

        double getTimestamp() const;
        void setTimestamp(double value);

        string getContainer() const;
        void setContainer(const string &value);

        string getType() const;
        void setType(const string &value);

        static double LastTimestamp;

    protected:
        double timestamp;
        string container;
        string type;
    };


}

#endif // PAJEPENDINGEVENT_H
