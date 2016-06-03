#ifndef PAJEFILEMANAGER_H
#define PAJEFILEMANAGER_H

#include <fstream>
#include <iostream>
#include <string>
#include "config.h"

using namespace std;

namespace prv2paje{

    class PajeFileManager
    {
    public:
        PajeFileManager(string pajePath);
        ~PajeFileManager();
        bool getPajeValid() const;

    private:
        bool pajeValid;
        ofstream *pajeStream;
        string pajePath;
    };

}

#endif // PAJEFILEMANAGER_H
