#ifndef PCFPARSER_H
#define PCFPARSER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim_all.hpp>

#include <stdlib.h>

#include "config.h"
#include "pcfoptions.h"
#include "pcfstates.h"
#include "pcfevents.h"
#include "pcfgradient.h"
#include "pcfvalue.h"
#include "stringutils.h"

using namespace std;
using namespace boost::algorithm;

namespace prv2paje{

    class PcfParser
    {
    public:
        PcfParser(ifstream* pcfStream);
    private:
        enum Mode{Options, States, StatesColor, EventType, Values, GradientColor, GradientName, Unknown};
        void parse();
        ifstream* pcfStream;
        map<string,PcfOptions> *pcfOptions;
        PcfStates*pcfStates;
        map<int, PcfEvents*> *pcfEvents;
        PcfGradient* pcfGradient;
        vector<map<int, PcfValue*>* >*pcfValues;
    };

}

#endif // PCFPARSER_H
