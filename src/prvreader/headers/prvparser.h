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

#include "prvreader_config.h"
#include "pcfparser.h"
#include "interpretercomponent.h"
#include "prvmetadata.h"

using namespace std;
using namespace boost;

namespace prvreader{

    class PrvParser
    {
    public:
        PrvParser(ifstream* prvStream, PcfParser* pcfParser, InterpreterComponent* interpreterComponent);
        ~PrvParser();
        void parse();
    private:
        void parseHeader(tokenizer<escaped_list_separator<char> > *tokens);
        void parseEvents(tokenizer<escaped_list_separator<char> > *tokens, double * currentTimestamp, long lineNumber);
        void parseState(tokenizer<escaped_list_separator<char> > *tokens, double * currentTimestamp, long lineNumber);
        void parseCommunications(tokenizer<escaped_list_separator<char> > *tokens, double * currentTimestamp, long lineNumber);
        enum Mode{Header, Body};
        ifstream* prvStream;
        InterpreterComponent* interpreterComponent;
        PcfParser* pcfParser;
        PrvMetaData* prvMetaData;
    };

}

#endif // PRVPARSER_H
