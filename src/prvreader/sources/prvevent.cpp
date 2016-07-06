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

#include "prvevent.h"

int prvreader::PrvEvent::getCpu() const
{
    return cpu;
}

void prvreader::PrvEvent::setCpu(int value)
{
    cpu = value;
}

int prvreader::PrvEvent::getApp() const
{
    return app;
}

void prvreader::PrvEvent::setApp(int value)
{
    app = value;
}

int prvreader::PrvEvent::getTask() const
{
    return task;
}

void prvreader::PrvEvent::setTask(int value)
{
    task = value;
}

int prvreader::PrvEvent::getThread() const
{
    return thread;
}

void prvreader::PrvEvent::setThread(int value)
{
    thread = value;
}

long prvreader::PrvEvent::getTimestamp() const
{
    return timestamp;
}

void prvreader::PrvEvent::setTimestamp(long value)
{
    timestamp = value;
}

long prvreader::PrvEvent::getLineNumber() const
{
    return lineNumber;
}

void prvreader::PrvEvent::setLineNumber(long value)
{
    lineNumber = value;
}

prveventtype::PrvEventType prvreader::PrvEvent::getType() const
{
    return type;
}

void prvreader::PrvEvent::setType(const prveventtype::PrvEventType &value)
{
    type = value;
}

prvreader::PrvEvent::PrvEvent()
{
    type=prveventtype::Skip;
}

prvreader::PrvEvent::PrvEvent(long lineNumber):lineNumber(lineNumber)
{
    type=prveventtype::NotConform;
}

prvreader::PrvEvent::PrvEvent(int cpu, int app, int task, int thread, long timestamp, long linenumber):cpu(cpu), app(app), task(task), thread(thread), timestamp(timestamp), lineNumber(linenumber)
{
    type=prveventtype::Skip;
}
