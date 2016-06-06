#ifndef PCFPARSER_H
#define PCFPARSER_H

#include <iostream>
#include <string>
#include "pcfoptions.h"
#include "pcfstates.h"
#include "pcfevents.h"
#include "pcfgradient.h"
#include "pcfvalue.h"
#include "stringutils.h"

using namespace std;

namespace prv2paje{

    class PcfParser
    {
    public:
        PcfParser(ifstream* pcfStream);
    private:
        void parse();
        ifstream* pcfStream;
        map<string,PcfOptions> *pcfOptions;
        map<int, PcfStates> *pcfStates;
        map<int, PcfEvents> *pcfEvents;
        map<int, PcfGradient> *pcfGradient;
        vector<map<int, PcfValue> > *pcfValues;
    };

}

#endif // PCFPARSER_H
