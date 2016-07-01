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
