#ifndef ARGUMENTMANAGER_H
#define ARGUMENTMANAGER_H

#include <string>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "prv2paje_config.h"
#include <message.h>

#define ARGUMENT(n, flag, wholeflag) ((n.compare(flag)==0)||(n.compare(wholeflag)==0))

using namespace std;
using namespace prvreader;

namespace prv2paje{

    class ArgumentManager
    {
    public:
        ArgumentManager(int argc, char** argv);
        void usage();

        bool getValid() const;

        string getMe() const;

        string getPrvPath() const;

        string getPajePath() const;

        bool getBasic() const;

        bool getOld() const;

        bool getFast() const;

        void setFast(bool value);

    private:
        bool valid;
        bool basic;
        bool old;
        bool fast;
        bool filter;
        string me;
        string prvPath;
        string pajePath;
        string filterPath;
    };

}

#endif // ARGUMENTMANAGER_H
