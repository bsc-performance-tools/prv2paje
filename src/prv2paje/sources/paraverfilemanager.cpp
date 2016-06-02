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
    if (prvPath.substr(prvPath.end()-3).compare(PRV_EXT)==0){
        prvStream->open(prvPath);
        if (!prvStream->is_open()){
            prvValid=false;
            pcfValid=false;
            rowValid=false;
        }
        else{
            prvvalid=true;
            pcfPath=prvPath;
            pcfPath.replace(str.end()-3, 3, PCF_EXT);
            rowPath=prvPath;
            rowPath.replace(str.end()-3, 3, ROW_EXT);
            pcfStream->open(pcfPath);
            if (pcfStream->is_open()){
                pcfValid=true;
            }else{
                pcfValid=false;
            }
            rowStream->open(rowPath);
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
    prvStream->close();
    pcfStream->close();
    rowStream->close();
}

string ParaverFileManager::getRowPath() const
{
    return rowPath;
}

string ParaverFileManager::getPcfPath() const
{
    return pcfPath;
}

string ParaverFileManager::getPrvPath() const
{
    return prvPath;
}

ifstream *ParaverFileManager::getRowStream() const
{
    return rowStream;
}

ifstream *ParaverFileManager::getPcfStream() const
{
    return pcfStream;
}

ifstream *ParaverFileManager::getPrvStream() const
{
    return prvStream;
}

bool ParaverFileManager::getRowValid() const
{
    return rowValid;
}

bool ParaverFileManager::getPcfValid() const
{
    return pcfValid;
}

bool ParaverFileManager::getPrvValid() const
{
    return prvValid;
}
