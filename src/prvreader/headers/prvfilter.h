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

#ifndef PRVFILTER_H
#define PRVFILTER_H

#include <map>
#include <string>

using namespace std;

namespace prvreader{

    class PrvFilter
    {
    public:
        PrvFilter();
        bool getEnabled() const;
        void setEnabled(bool value);

        bool getDisableStates() const;
        void setDisableStates(bool value);

        bool getDisableEvents() const;
        void setDisableEvents(bool value);

        bool getDisableCommunications() const;
        void setDisableCommunications(bool value);

        bool getDisableFilterTypes() const;
        void setDisableFilterTypes(bool value);

        void addUnfilteredType(string type);
        bool isFiltered(string type);

        void addUnfilteredType(int type);
        bool isFiltered(int type);

    private:
        bool enabled;
        bool disableStates;
        bool disableEvents;
        bool disableCommunications;
        bool disableFilterTypes;
        map<int, bool> unfilteredTypes;
    };

}

#endif // PRVFILTER_H
