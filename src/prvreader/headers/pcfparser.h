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

#ifndef PCFPARSER_H
#define PCFPARSER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim_all.hpp>

#include <stdlib.h>

#include "prvreader_config.h"
#include "pcfoptions.h"
#include "pcfstates.h"
#include "pcfevents.h"
#include "pcfgradient.h"
#include "pcfvalue.h"
#include "prvfilter.h"
#include "message.h"

using namespace std;
using namespace boost::algorithm;

namespace prvreader{

    class PcfParser
    {
    public:
        PcfParser(ifstream* pcfStream, PrvFilter* filter);
        ~PcfParser();
        map<string, PcfOptions *> *getPcfOptions() const;
        PcfStates *getPcfStates() const;
        map<int, PcfEvents *> *getPcfEvents() const;
        PcfGradient *getPcfGradient() const;
        vector<map<int, PcfValue *> *> *getPcfValues() const;
        void parse();
        PrvFilter *getFilter() const;
        void setFilter(PrvFilter *value);

    private:
        void filtering();
        enum Mode{Options, States, StatesColor, EventType, Values, GradientColor, GradientName, Unknown};
        ifstream* pcfStream;
        PrvFilter* filter;
        map<string,PcfOptions*> *pcfOptions;
        PcfStates* pcfStates;
        map<int, PcfEvents*> *pcfEvents;
        PcfGradient *pcfGradient;
        vector<map<int, PcfValue*>* > *pcfValues;
    };

}

#endif // PCFPARSER_H
