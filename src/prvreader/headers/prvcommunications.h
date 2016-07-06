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

#ifndef PRVCOMMUNICATIONS_H
#define PRVCOMMUNICATIONS_H

#include "prvevent.h"
#include <string>

using namespace std;

namespace prvreader{

    class PrvCommunications : public PrvEvent
    {
    public:
        PrvCommunications();
        PrvCommunications(int cpu, int app, int task, int thread, long timestamp, long linenumber, int cpu2, int app2, int task2, int thread2, long timestampEnd, long timestampHW, long timestampHWEnd, string value);
        ~PrvCommunications();

        long getTimestampHW() const;
        void setTimestampHW(long value);

        long getTimestampEnd() const;
        void setTimestampEnd(long value);

        long getTimestampHWEnd() const;
        void setTimestampHWEnd(long value);

        string getValue() const;
        void setValue(const string &value);

        int getCpu2() const;
        void setCpu2(int value);

        int getApp2() const;
        void setApp2(int value);

        int getTask2() const;
        void setTask2(int value);

        int getThread2() const;
        void setThread2(int value);

    private:
        int cpu2;
        int app2;
        int task2;
        int thread2;
        long timestampHW;
        long timestampEnd;
        long timestampHWEnd;
        string value;
    };

}

#endif // PRVCOMMUNICATIONS_H
