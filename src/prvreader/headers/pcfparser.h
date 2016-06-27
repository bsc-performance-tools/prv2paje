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

#include "prvreader_config.h"
#include "pcfoptions.h"
#include "pcfstates.h"
#include "pcfevents.h"
#include "pcfgradient.h"
#include "pcfvalue.h"

using namespace std;
using namespace boost::algorithm;

namespace prvreader{

    class PcfParser
    {
    public:
        PcfParser(ifstream* pcfStream);
        ~PcfParser();
        map<string, PcfOptions *> *getPcfOptions() const;
        PcfStates *getPcfStates() const;
        map<int, PcfEvents *> *getPcfEvents() const;
        PcfGradient *getPcfGradient() const;
        vector<map<int, PcfValue *> *> *getPcfValues() const;
        void parse();

    private:
        enum Mode{Options, States, StatesColor, EventType, Values, GradientColor, GradientName, Unknown};
        ifstream* pcfStream;
        map<string,PcfOptions*> *pcfOptions;
        PcfStates* pcfStates;
        map<int, PcfEvents*> *pcfEvents;
        PcfGradient *pcfGradient;
        vector<map<int, PcfValue*>* > *pcfValues;
    };

}

#endif // PCFPARSER_H
