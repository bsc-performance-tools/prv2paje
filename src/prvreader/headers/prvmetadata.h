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

#ifndef PRVMETADATA_H
#define PRVMETADATA_H

#include <string>
#include <vector>

#include "prvreader_config.h"

using namespace std;

namespace prvreader{

    class PrvMetaData
    {
    public:
        PrvMetaData();
        string getFile() const;
        void setFile(const string &value);

        long getDuration() const;
        void setDuration(long value);

        string getTimeUnit() const;
        void setTimeUnit(const string &value);

        int getApplications() const;
        void setApplications(int value);

        int getNodes() const;
        void setNodes(int value);

        string getComment() const;
        void setComment(const string &value);

        vector<int> *getCpus() const;
        void setCpus(vector<int> *value);

    private:
        string comment;
        string file;
        long int duration;
        string timeUnit;
        int applications;
        int nodes;
        vector<int> *cpus;
    };

}

#endif // PRVMETADATA_H
