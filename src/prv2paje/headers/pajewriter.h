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

#ifndef PAJEWRITER_H
#define PAJEWRITER_H

#include <cstdlib>
#include <iostream>
#include <ctime>

#include <fstream>
#include <map>
#include <poti.h>

#include "prv2paje_config.h"
#include <prvreader_config.h>
#include <prvmetadata.h>
#include <pcfparser.h>
#include "pajepending.h"
#include <message.h>
#include <interpretercomponent.h>
#include <prvparser.h>

using namespace std;
using namespace prvreader;

namespace prv2paje{

    class PajeWriter
    {
    public:
        PajeWriter(PrvParser* prvParser, string pajePath);
        PajeWriter(PrvParser* prvParser, string pajePath, bool basicHeader, bool oldHeader);
        ~PajeWriter();
        void push(PrvEvents*);
        void push(PrvState*);
        void push(PrvCommunications*);
        double getTimeDivider();
        void setTimeDivider();
        void generate();

        PrvParser *getPrvParser() const;

        PrvMetaData *getPrvMetaData() const;

        PcfParser *getPcfParser() const;


    private:
        void finalize();
        void initialize();
        void checkContainerChain(double timestamp, int cpu, int app, int task, int thread);
        void generatePajeHeader();
        void defineAndCreatePajeContainers();
        void definePajeEvents();
        bool basicHeader;
        bool oldHeader;
        double timeDivider;
        string pajePath;
        PajePending pajePending;
        vector<map<int, map<int, map<int, bool > > > > containerChain;
        PrvParser *prvParser;
        PrvMetaData *prvMetaData;
        PcfParser *pcfParser;
        PrvFilter* filter;
        bool fast;
        bool alias;
    };

}

#endif // PAJEWRITER_H
