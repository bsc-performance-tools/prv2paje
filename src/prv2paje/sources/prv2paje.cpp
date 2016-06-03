#include <iostream>
#include "argumentmanager.h"
#include "paraverfilemanager.h"
#include "pajefilemanager.h"

using namespace std;
using namespace prv2paje;

int main(int argc, char* argv[])
{
    ArgumentManager argumentManager(argc, argv);
    if (!argumentManager.getValid()){
        cerr<<"Invalid arguments"<<endl;
        argumentManager.usage();
        return 1;
    }
    ParaverFileManager paraverFileManager(argumentManager.getPrvPath());
    if (!paraverFileManager.getPrvValid()){
        cerr<<"Paraver trace file cannot be opened"<<endl;
        argumentManager.usage();
        return 2;
    }
    PajeFileManager pajeFileManager(argumentManager.getPajePath());
    if (!pajeFileManager.getPajeValid()){
        cerr<<"Paje trace file cannot be created"<<endl;
        argumentManager.usage();
        return 3;
    }
}
