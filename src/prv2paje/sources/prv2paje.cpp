#include <iostream>
#include "argumentmanager.h"
#include "paraverfilemanager.h"
#include "pajefilemanager.h"
#include "pcfparser.h"
#include "prvparser.h"
#include "pajewriter.h"
#include "message.h"

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

    Message::Info("Parsing configuration file",1);
    PcfParser *pcfParser = new PcfParser(paraverFileManager.getPcfStream());
    pcfParser->parse();
    PajeWriter *pajeWriter = new PajeWriter(pajeFileManager.getPajePath());
    PrvParser *prvParser = new PrvParser(paraverFileManager.getPrvStream(),pcfParser, pajeWriter);
    Message::Info("Parsing paraver trace file and generating paje trace file",1);
    prvParser->parse();
    delete pajeWriter;
    delete prvParser;
    delete pcfParser;
    return RETURN_OK;
}
