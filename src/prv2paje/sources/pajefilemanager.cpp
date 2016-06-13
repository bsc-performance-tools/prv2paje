#include "pajefilemanager.h"


prv2paje::PajeFileManager::PajeFileManager(string pajePath):pajePath(pajePath)
{
    pajeValid=false;
    pajeStream=new ofstream();
    pajeStream->open(pajePath.c_str());
    if (pajeStream->is_open()){
        pajeValid=true;
    }

}

prv2paje::PajeFileManager::~PajeFileManager()
{
    if (pajeValid){
        pajeStream->close();
    }
    delete pajeStream;
}

bool prv2paje::PajeFileManager::getPajeValid() const
{
    return pajeValid;
}

string prv2paje::PajeFileManager::getPajePath() const
{
    return pajePath;
}
