#ifndef ARGUMENTMANAGER_H
#define ARGUMENTMANAGER_H

#include <string>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "config.h"
#include "message.h"

#define ARGUMENT(n, flag, wholeflag) (strcmp(argv[n],flag)==0||strcmp(argv[n],wholeflag)==0)

using namespace std;

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

    private:
        bool valid;
        bool basic;
        bool old;
        string me;
        string prvPath;
        string pajePath;
    };

}

#endif // ARGUMENTMANAGER_H
