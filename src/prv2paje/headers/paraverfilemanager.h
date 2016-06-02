#ifndef PARAVERFILEMANAGER_H
#define PARAVERFILEMANAGER_H

#include <fstream>
#include <iostream>
#include <string>


using namespace std;

namespace prv2paje
{

    class ParaverFileManager
    {
        public:
            ParaverFileManager(String prvPath);
            ~ParaverFileManager();
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
