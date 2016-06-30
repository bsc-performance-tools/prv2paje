#include "argumentmanager.h"

prv2paje::ArgumentManager::ArgumentManager(int argc, char **argv):valid(true), basic(false), old(false), fast(true), prvPath(""), pajePath("")
{
    if (argc<2){
        valid=false;
        me=string(argv[0]);
    }else{
        me=string(argv[0]);
        for (int i=1; i<argc; i++){
            string str=string(argv[i]);
            //Message::Info("Argument: "+str);
            if (ARGUMENT(str, "--basic-header", "--basic-header")){
                basic=true;
                Message::Info("Basic header enabled");
            }else if (ARGUMENT(str, "--old-header", "--old-header")){
                old=true;
                Message::Info("Old header enabled");
            }else if (ARGUMENT(str, "-s", "--strict")){
                fast=false;
                Message::Info("Strict mode enabled");
            }else if (ARGUMENT(str, "-o", "--output")){
                pajePath=string(argv[++i]);
                Message::Info("Output:"+pajePath);
            }else if (ARGUMENT(str, "-f", "--filter")){
                filterPath=string(argv[++i]);
                Message::Info("Filter configuration file:"+filterPath);
            }else{
                prvPath=str;
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
    Message::Info("\t -f --filter [filter-file]: filtering configuration file");
    Message::Info("\t --old-header: old Pajé header");
    Message::Info("\t --basic-header: basic Pajé header");
    Message::Info("\t -s --strict: check more strictly the trace integrity (increases computation duration and memory consumption)");
}

string prv2paje::ArgumentManager::getPajePath() const
{
    return pajePath;
}

bool prv2paje::ArgumentManager::getOld() const
{
    return old;
}

bool prv2paje::ArgumentManager::getFast() const
{
    return fast;
}

void prv2paje::ArgumentManager::setFast(bool value)
{
    fast = value;
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
