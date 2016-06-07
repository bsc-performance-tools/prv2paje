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

#include "pcfparser.h"
#include "pajewriter.h"

using namespace std;

namespace prv2paje{

    class PrvParser
    {
    public:
        PrvParser(ifstream* prvStream, PcfParser* pcfParser, PajeWriter* pajeWriter);
    private:
        enum Mode{Header, Communicators, Communication, Event, };
        void parse();
        ifstream* prvStream;
        PajeWriter* pajeWriter;
        PcfParser* pcfParser;

    };

}

#endif // PRVPARSER_H
