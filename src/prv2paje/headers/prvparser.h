#ifndef PRVPARSER_H
#define PRVPARSER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim_all.hpp>

#include <stdlib.h>

#include "pajewriter.h"

using namespace std;

namespace prv2paje{

    class PrvParser
    {
    public:
        PrvParser(ifstream* prvStream, PajeWriter);
    private:
    };

}

#endif // PRVPARSER_H
