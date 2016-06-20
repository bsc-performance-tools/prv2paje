#ifndef PRVPARSER_H
#define PRVPARSER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim_all.hpp>

#include <boost/tokenizer.hpp>

#include <stdlib.h>

#include "config.h"
#include "pcfparser.h"
#include "pajewriter.h"
#include "prvmetadata.h"

using namespace std;
using namespace boost;

namespace prv2paje{

    class PrvParser
    {
    public:
        PrvParser(ifstream* prvStream, PcfParser* pcfParser, PajeWriter* pajeWriter);
        ~PrvParser();
        void parse();
    private:
        enum Mode{Header, Body};
        ifstream* prvStream;
        PajeWriter* pajeWriter;
        PcfParser* pcfParser;
        PrvMetaData* prvMetaData;
    };

}

#endif // PRVPARSER_H
