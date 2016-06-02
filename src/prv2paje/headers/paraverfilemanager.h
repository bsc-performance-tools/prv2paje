#ifndef PARAVERFILEMANAGER_H
#define PARAVERFILEMANAGER_H

#include <fstream>
#include <iostream>
#include <string>
#include "config.h"

using namespace std;

namespace prv2paje
{

    class ParaverFileManager
    {
        public:
            ParaverFileManager(String prvPath);
            ~ParaverFileManager();
            bool getPrvValid() const;

            bool getPcfValid() const;

            bool getRowValid() const;

            ifstream *getPrvStream() const;

            ifstream *getPcfStream() const;

            ifstream *getRowStream() const;

            string getPrvPath() const;

            string getPcfPath() const;

            string getRowPath() const;

    private:
            bool prvValid;
            bool pcfValid;
            bool rowValid;
            ifstream *prvStream;
            ifstream *pcfStream;
            ifstream *rowStream;
            string prvPath;
            string pcfPath;
            string rowPath;
    };

}

#endif // PARAVERFILEMANAGER_H
