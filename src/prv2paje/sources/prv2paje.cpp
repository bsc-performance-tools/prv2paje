#include <iostream>
#include "argumentmanager.h"
#include "paraverfilemanager.h"
#include "pajefilemanager.h"
#include "pcfparser.h"

using namespace std;
using namespace prv2paje;

int main(int argc, char* argv[])
{
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
    cout<<"prv2paje version "<<__BUILD_VERSION__<<endl;
    cout<<"--------------------------------------- "<<endl;
    cout<<"Parsing .pcf file..."<<endl;
    PcfParser pcfParser(paraverFileManager.getPcfStream());
    cout<<"Done"<<endl;
    return RETURN_OK;
}
