#include "argumentmanager.h"

prv2paje::ArgumentManager::ArgumentManager(int argc, char **argv)
{
    if (argc!=3){
        valid=false;
        me=string(argv[0]);
    }else{
        valid=true;
        me=string(argv[0]);
        prvPath=string(argv[1]);
        pajePath=string(argv[2]);
    }
}

void prv2paje::ArgumentManager::usage()
{
    cerr<<"Usage:"<<endl;
    cerr<<me.c_str()<<" [input-trace].prv [output-trace]"<<endl;
}

string prv2paje::ArgumentManager::getPajePath() const
{
    return pajePath;
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
