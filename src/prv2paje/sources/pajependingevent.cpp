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

#include "pajependingevent.h"

double prv2paje::PajePendingEvent::LastTimestamp;

prv2paje::PajePendingEvent::PajePendingEvent()
{

}

prv2paje::PajePendingEvent::PajePendingEvent(double timestamp):timestamp(timestamp)
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

double prv2paje::PajePendingEvent::getTimestamp() const
{
    return timestamp;
}

void prv2paje::PajePendingEvent::setTimestamp(double value)
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
