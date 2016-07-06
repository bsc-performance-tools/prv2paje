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

#include "pajependingcommunication.h"

int prv2paje::PajePendingCommunication::id;

prv2paje::PajePendingCommunication::PajePendingCommunication()
{

}

prv2paje::PajePendingCommunication::PajePendingCommunication(double timestamp):PajePendingEvent(timestamp)
{

}

void prv2paje::PajePendingCommunication::InitializeId()
{
    prv2paje::PajePendingCommunication::id=0;
}

string prv2paje::PajePendingCommunication::GetNextKey()
{
    prv2paje::PajePendingCommunication::id++;
    return string(PAJE_COMMUNICATION_KEY_PREFIX)+to_string(prv2paje::PajePendingCommunication::id);
}

string prv2paje::PajePendingCommunication::getKey() const
{
    return key;
}

void prv2paje::PajePendingCommunication::setKey(const string &value)
{
    key = value;
}

string prv2paje::PajePendingCommunication::getSubContainer() const
{
    return subContainer;
}

void prv2paje::PajePendingCommunication::setSubContainer(const string &value)
{
    subContainer = value;
}

string prv2paje::PajePendingCommunication::getValue() const
{
    return value;
}

void prv2paje::PajePendingCommunication::setValue(string val)
{
    value = val;
}
