#include "argumentmanager.h"

prv2paje::ArgumentManager::ArgumentManager(int argc, char **argv):valid(true), basic(false), old(false), prvPath(""), pajePath("")
{
    if (argc<2){
        valid=false;
        me=string(argv[0]);
    }else{
        me=string(argv[0]);
        for (int i=1; i<argc; i++){
            if (ARGUMENT(i, "--basic-header", "--basic-header")){
                basic=true;
            }else if (ARGUMENT(i, "--old-header", "--old-header")){
                old=true;
            }else if (ARGUMENT(i, "-o", "--output")){
                pajePath=string(argv[++i]);
            }else{
                prvPath=string(argv[i]);
                Message::Info("Input: "+prvPath);
            }
        }
    }
    if (prvPath.compare("")==0){
        valid=false;
    }
}

void prv2paje::ArgumentManager::usage()
{
    Message::Info("Usage");
    Message::Info(string(me.c_str())+" [input-trace].prv");
    Message::Info("Options:");
    Message::Info("\t -o --output [output-trace]: output Pajé trace");
    Message::Info("\t --old-header: old Pajé header");
    Message::Info("\t --basic-header: basic Pajé header");
}

string prv2paje::ArgumentManager::getPajePath() const
{
    return pajePath;
}

bool prv2paje::ArgumentManager::getOld() const
{
    return old;
}

bool prv2paje::ArgumentManager::getBasic() const
{
    return basic;
}

string prv2paje::ArgumentManager::getPrvPath() const
{
    return prvPath;
}

string prv2paje::ArgumentManager::getMe() const
{
    return me;
}

bool prv2paje::ArgumentManager::getValid() const
{
    return valid;
}
