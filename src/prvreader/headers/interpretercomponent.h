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

#ifndef INTERPRETERCOMPONENT_H
#define INTERPRETERCOMPONENT_H

#include <cstdlib>
#include <iostream>
#include <ctime>

#include <fstream>
#include <map>

#include "prvreader_config.h"
#include "prvmetadata.h"
#include "pcfparser.h"
#include "message.h"

using namespace std;

namespace prvreader{

    class InterpreterComponent
    {
    public:
        virtual void pushEvents(int cpu, int app, int task, int thread, long timestamp, map<int, string>* events, long lineNumber)=0;
        virtual void pushState(int cpu, int app, int task, int thread, long startTimestamp, long endTimestamp, string value, long lineNumber)=0;
        virtual void pushCommunications(int cpu1, int app1, int task1, int thread1, int cpu2, int app2, int task2, int thread2,
                                        long startTimestampSW, long startTimestampHW, long endTimestampSW, long endTimestampHW, string value, long lineNumber)=0;
        virtual void initialize()=0;
        virtual void finalize()=0;

        PrvMetaData *getPrvMetaData() const;
        void setPrvMetaData(PrvMetaData *value);

        PcfParser *getPcfParser() const;
        void setPcfParser(PcfParser *value);

    protected:
        PrvMetaData *prvMetaData;
        PcfParser *pcfParser;
    };

}

#endif // INTERPRETERCOMPONENT_H
