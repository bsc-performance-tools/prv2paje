#ifndef FILTERMANAGER_H
#define FILTERMANAGER_H

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <prvfilter.h>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim_all.hpp>

#include <stdlib.h>

#include "prv2paje_config.h"
#include <prvreader_config.h>
#include <message.h>

using namespace std;
using namespace prvreader;
using namespace boost::algorithm;

namespace prv2paje{

    class FilterManager
    {
    public:
        FilterManager(string pathFilter);
        FilterManager();
        ~FilterManager();
        bool getFilterValid() const;
        void parse();
        PrvFilter *getFilter() const;
    private:
        enum Mode{Unknown, Types, EventTypes};
        string filterPath;
        ifstream *filterStream;
        bool filterValid;
        PrvFilter* filter;

    };

}

#endif // FILTERMANAGER_H
