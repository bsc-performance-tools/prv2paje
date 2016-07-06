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

#include "pcfevents.h"


prvreader::PcfEvents::PcfEvents(int gradient, int type):gradient(gradient), type(type), label("")
{

}

prvreader::PcfEvents::PcfEvents(int gradient, int type, string label): gradient(gradient), type(type), label(label)
{

}

int prvreader::PcfEvents::getGradient() const
{
    return gradient;
}

void prvreader::PcfEvents::setGradient(int value)
{
    gradient = value;
}

int prvreader::PcfEvents::getType() const
{
    return type;
}

void prvreader::PcfEvents::setType(int value)
{
    type = value;
}

string prvreader::PcfEvents::getLabel() const
{
    return label;
}

void prvreader::PcfEvents::setLabel(const string &value)
{
    label = value;
}

pcfeventtype::PcfEventType prvreader::PcfEvents::getEventType() const
{
    return eventType;
}

void prvreader::PcfEvents::setEventType(const pcfeventtype::PcfEventType &value)
{
    eventType = value;
}

map<int, prvreader::PcfValue*> * prvreader::PcfEvents::getValues() const
{
    return values;
}

void prvreader::PcfEvents::setValues(map<int, PcfValue*> *value)
{
    values = value;
}
