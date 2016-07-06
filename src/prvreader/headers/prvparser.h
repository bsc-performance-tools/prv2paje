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

#ifndef PRVPARSER_H
#define PRVPARSER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim_all.hpp>

#include <boost/tokenizer.hpp>

#include <stdlib.h>

#include "prvreader_config.h"
#include "pcfparser.h"
#include "interpretercomponent.h"
#include "prvmetadata.h"
#include "prvevent.h"
#include "prvevents.h"
#include "prvstate.h"
#include "prvcommunications.h"
#include "prvother.h"
#include "prvfilter.h"




using namespace std;
using namespace boost;

namespace prvreader{

    class PrvParser
    {
    public:
        PrvParser(ifstream* prvStream, PcfParser* pcfParser, bool fast);
        PrvParser(ifstream* prvStream, PcfParser* pcfParser);
        ~PrvParser();
        PrvEvent* parseLine();
        PrvMetaData *getPrvMetaData() const;
        PcfParser *getPcfParser() const;
        bool getFast() const;
        void setFast(bool value);

    private:
        PrvEvent* parseHeader(tokenizer<escaped_list_separator<char> > *tokens);
        PrvEvent* parseEvents(tokenizer<escaped_list_separator<char> > *tokens, long lineNumber);
        PrvEvent* parseState(tokenizer<escaped_list_separator<char> > *tokens, long lineNumber);
        PrvEvent* parseCommunications(tokenizer<escaped_list_separator<char> > *tokens, long lineNumber);
        enum Mode{Header, Body};
        ifstream* prvStream;
        InterpreterComponent* interpreterComponent;
        PcfParser* pcfParser;
        PrvMetaData* prvMetaData;
        Mode mode;
        long lineNumber;
        long currentTimestamp;
        bool fast;
        PrvFilter* filter;
    };

}

#endif // PRVPARSER_H
