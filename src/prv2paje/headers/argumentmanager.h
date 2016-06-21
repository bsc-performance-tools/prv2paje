#ifndef ARGUMENTMANAGER_H
#define ARGUMENTMANAGER_H

#include <string>
#include <iostream>
#include "config.h"
#include "message.h"

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
        string me;
        string prvPath;
        string pajePath;
    };

}

#endif // ARGUMENTMANAGER_H
