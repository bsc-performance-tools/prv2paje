#ifndef PCFEVENTS_H
#define PCFEVENTS_H

#include <string>
#include <map>
#include <pcfvalue.h>

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

using namespace std;

namespace pcfeventtype{

enum PcfEventType{Event, State, Variable, Communication, Undefined};

}

namespace prvreader{

    class PcfEvents
    {
    public:
        PcfEvents(int gradient, int type);
        PcfEvents(int gradient, int type, string label);
        int getGradient() const;
        void setGradient(int value);

        int getType() const;
        void setType(int value);

        string getLabel() const;
        void setLabel(const string &value);

        pcfeventtype::PcfEventType getEventType() const;
        void setEventType(const pcfeventtype::PcfEventType &value);

        map<int, PcfValue*> *getValues() const;
        void setValues(map<int, PcfValue*> *value);

    private:
        int gradient;
        int type;
        string label;
        pcfeventtype::PcfEventType eventType;
        map<int, PcfValue*>* values;
    };

}

#endif // PCFEVENT_H
