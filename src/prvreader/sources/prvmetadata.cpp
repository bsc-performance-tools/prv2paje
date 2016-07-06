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

#include "prvmetadata.h"

prvreader::PrvMetaData::PrvMetaData()
{

}

string prvreader::PrvMetaData::getFile() const
{
    return file;
}

void prvreader::PrvMetaData::setFile(const string &value)
{
    file = value;
}

long prvreader::PrvMetaData::getDuration() const
{
    return duration;
}

void prvreader::PrvMetaData::setDuration(long value)
{
    duration = value;
}

string prvreader::PrvMetaData::getTimeUnit() const
{
    return timeUnit;
}

void prvreader::PrvMetaData::setTimeUnit(const string &value)
{
    timeUnit = value;
}

int prvreader::PrvMetaData::getApplications() const
{
    return applications;
}

void prvreader::PrvMetaData::setApplications(int value)
{
    applications = value;
}

int prvreader::PrvMetaData::getNodes() const
{
    return nodes;
}

void prvreader::PrvMetaData::setNodes(int value)
{
    nodes = value;
}

string prvreader::PrvMetaData::getComment() const
{
    return comment;
}

void prvreader::PrvMetaData::setComment(const string &value)
{
    comment = value;
}

vector<int> *prvreader::PrvMetaData::getCpus() const
{
    return cpus;
}

void prvreader::PrvMetaData::setCpus(vector<int> *value)
{
    cpus = value;
}
