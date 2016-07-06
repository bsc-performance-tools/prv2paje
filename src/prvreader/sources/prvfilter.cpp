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

#include "prvfilter.h"


prvreader::PrvFilter::PrvFilter()
{
    setEnabled(false);
}

bool prvreader::PrvFilter::getEnabled() const
{
    return enabled;
}

void prvreader::PrvFilter::setEnabled(bool value)
{
    enabled = value;
    if (!enabled){
        disableStates=false;
        disableEvents=false;
        disableCommunications=false;
        disableFilterTypes=true;
    }
}

bool prvreader::PrvFilter::getDisableStates() const
{
    return disableStates;
}

void prvreader::PrvFilter::setDisableStates(bool value)
{
    if (enabled){
        disableStates = value;
    }
}

bool prvreader::PrvFilter::getDisableEvents() const
{
    return disableEvents;
}

void prvreader::PrvFilter::setDisableEvents(bool value)
{
    if (enabled){
        disableEvents = value;
    }
}

bool prvreader::PrvFilter::getDisableCommunications() const
{
    return disableCommunications;
}

void prvreader::PrvFilter::setDisableCommunications(bool value)
{
    if (enabled){
        disableCommunications = value;
    }
}

bool prvreader::PrvFilter::getDisableFilterTypes() const
{
    return disableFilterTypes;
}

void prvreader::PrvFilter::setDisableFilterTypes(bool value)
{
    if (enabled){
        disableFilterTypes = value;
    }
}

void prvreader::PrvFilter::addUnfilteredType(string type)
{
    if (!disableFilterTypes){
        unfilteredTypes[atoi(type.c_str())]=true;
    }
}

bool prvreader::PrvFilter::isFiltered(string type)
{
    if (!disableFilterTypes){
        if (unfilteredTypes.count(atoi(type.c_str()))>0){
            return true;
        }
    }
    return false;
}

void prvreader::PrvFilter::addUnfilteredType(int type)
{
    if (!disableFilterTypes){
        unfilteredTypes[type]=true;
    }
}

bool prvreader::PrvFilter::isFiltered(int type)
{
    if (!disableFilterTypes){
        if (unfilteredTypes.count(type)>0){
            return false;
        }
        else{
            return true;
        }
    }
    return false;
}
