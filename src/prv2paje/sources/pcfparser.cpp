#include "pcfparser.h"


prv2paje::PcfParser::PcfParser(ifstream *pcfStream):
    pcfStream(pcfStream), pcfOptions(new map<string, PcfOptions>()), pcfStates(new map<int, PcfStates>()),
    pcfEvents(new map<int, PcfEvents>()), pcfGradient(new map<int, PcfGradient>()), pcfValues(new vector<map<int, PcfValue> >())
{

}

void prv2paje::PcfParser::parse(){
    string line;
    if (pcfStream){
        while(pcfStream,line, '\n'){

        }
    }
}
