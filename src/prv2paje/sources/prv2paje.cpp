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

#include <iostream>
#include "argumentmanager.h"
#include "paraverfilemanager.h"
#include "pajefilemanager.h"
#include "pcfparser.h"
#include "prvparser.h"
#include "pajewriter.h"
#include "message.h"
#include "filtermanager.h"

using namespace std;
using namespace prv2paje;

int main(int argc, char* argv[])
{
    Message::Info("prv2paje version "+string(__BUILD_VERSION__));
    ArgumentManager argumentManager(argc, argv);
    if (!argumentManager.getValid()){
        Message::Critical("invalid arguments");
        argumentManager.usage();
        return RETURN_ERR_PRV;
    }
    ParaverFileManager paraverFileManager(argumentManager.getPrvPath());
    if (!paraverFileManager.getPrvValid()){
        Message::Critical("Paraver trace file cannot be opened");
        argumentManager.usage();
        return RETURN_ERR_PCF;
    }
    PajeFileManager pajeFileManager(argumentManager.getPajePath().compare("")?argumentManager.getPajePath():PajeFileManager::PajeNameFromPrv(argumentManager.getPrvPath()));
    if (!pajeFileManager.getPajeValid()){
        Message::Critical("Pajé trace file cannot be created");
        argumentManager.usage();
        return RETURN_ERR_PAJE;
    }
    FilterManager *filterManager = new FilterManager(argumentManager.getFilterPath());
    if (filterManager->getFilterValid()){
        Message::Info("Parsing filter configuration file",1);
        filterManager->parse();
    }
    Message::Info("Parsing configuration file",1);
    PcfParser *pcfParser = new PcfParser(paraverFileManager.getPcfStream(), filterManager->getFilter());
    pcfParser->parse();
    PrvParser *prvParser = new PrvParser(paraverFileManager.getPrvStream(), pcfParser, argumentManager.getFast());
    Message::Info("Parsing paraver trace file and generating paje trace file",1);
    PajeWriter *pajeWriter = new PajeWriter(prvParser, pajeFileManager.getPajePath(), argumentManager.getBasic(), argumentManager.getOld());
    pajeWriter->generate();
    delete pajeWriter;
    delete prvParser;
    delete pcfParser;
    delete filterManager;
    return RETURN_OK;
}
