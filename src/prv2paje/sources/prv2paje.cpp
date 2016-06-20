#include <iostream>
#include "argumentmanager.h"
#include "paraverfilemanager.h"
#include "pajefilemanager.h"
#include "pcfparser.h"
#include "prvparser.h"
#include "pajewriter.h"

using namespace std;
using namespace prv2paje;

int main(int argc, char* argv[])
{
    cout<<"prv2paje version "<<__BUILD_VERSION__<<endl;
    ArgumentManager argumentManager(argc, argv);
    if (!argumentManager.getValid()){
        cerr<<"Invalid arguments"<<endl;
        argumentManager.usage();
        return RETURN_ERR_PRV;
    }
    ParaverFileManager paraverFileManager(argumentManager.getPrvPath());
    if (!paraverFileManager.getPrvValid()){
        cerr<<"Paraver trace file cannot be opened"<<endl;
        argumentManager.usage();
        return RETURN_ERR_PCF;
    }
    PajeFileManager pajeFileManager(argumentManager.getPajePath());
    if (!pajeFileManager.getPajeValid()){
        cerr<<"Paje trace file cannot be created"<<endl;
        argumentManager.usage();
        return RETURN_ERR_PAJE;
    }

    cout<<"Parsing configuration file"<<endl;
    PcfParser *pcfParser = new PcfParser(paraverFileManager.getPcfStream());
    pcfParser->parse();
    PajeWriter *pajeWriter = new PajeWriter(pajeFileManager.getPajePath());
    PrvParser *prvParser = new PrvParser(paraverFileManager.getPrvStream(),pcfParser, pajeWriter);
    cout<<"Parsing paraver trace file and generating paje trace file"<<endl;
    prvParser->parse();
    cout<<"Done"<<endl;
    cout<<"--------------------------------------- "<<endl;
    delete pajeWriter;
    delete prvParser;
    delete pcfParser;
    return RETURN_OK;
}
