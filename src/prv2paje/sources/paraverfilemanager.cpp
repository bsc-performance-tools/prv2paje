#include "paraverfilemanager.h"

prv2paje::ParaverFileManager::ParaverFileManager(string prvPath)
{
    prvValid=false;
    pcfValid=false;
    rowValid=false;
    this->prvPath=prvPath;
    prvStream=new ifstream();
    pcfStream=new ifstream();
    rowStream=new ifstream();
    if (string(this->prvPath.end()-3,this->prvPath.end()).compare(PRV_EXT)==0){
        prvStream->open(prvPath.c_str());
        if (!prvStream->is_open()){
            prvValid=false;
            pcfValid=false;
            rowValid=false;
        }
        else{
            prvValid=true;
            string prvExt=string(PRV_EXT);
            pcfPath=prvPath;
            string ext=string(PCF_EXT);
            pcfPath.replace(prvPath.size()-prvExt.size(), ext.size(), ext);
            rowPath=prvPath;
            ext=string(ROW_EXT);
            rowPath.replace(prvPath.size()-prvExt.size(), ext.size(), ext);
            pcfStream->open(pcfPath.c_str());
            if (pcfStream->is_open()){
                pcfValid=true;
            }else{
                pcfValid=false;
            }
            rowStream->open(rowPath.c_str());
            if (rowStream->is_open()){
                rowValid=true;
            }else{
                rowValid=false;
            }
        }
    }
}

prv2paje::ParaverFileManager::~ParaverFileManager()
{
    if (prvValid){
        prvStream->close();
    }
    if (pcfStream){
        pcfStream->close();
    }
    if (rowStream){
        rowStream->close();
    }
    delete prvStream;
    delete pcfStream;
    delete rowStream;
}

string prv2paje::ParaverFileManager::getRowPath() const
{
    return rowPath;
}

string prv2paje::ParaverFileManager::getPcfPath() const
{
    return pcfPath;
}

string prv2paje::ParaverFileManager::getPrvPath() const
{
    return prvPath;
}

ifstream* prv2paje::ParaverFileManager::getRowStream() const
{
    return rowStream;
}

ifstream* prv2paje::ParaverFileManager::getPcfStream() const
{
    return pcfStream;
}
ifstream* prv2paje::ParaverFileManager::getPrvStream() const
{
    return prvStream;
}

bool prv2paje::ParaverFileManager::getRowValid() const
{
    return rowValid;
}

bool prv2paje::ParaverFileManager::getPcfValid() const
{
    return pcfValid;
}

bool prv2paje::ParaverFileManager::getPrvValid() const
{
    return prvValid;
}
