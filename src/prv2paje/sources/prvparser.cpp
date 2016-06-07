#include "../headers/prvparser.h"


prv2paje::PrvParser::PrvParser(ifstream *prvStream, prv2paje::PcfParser *pcfParser, prv2paje::PajeWriter *pajeWriter):
    prvStream(prvStream), pcfParser(pcfParser), pajeWriter(pajeWriter)
{

}

void prv2paje::PrvParser::parse()
{
    /*string line;
    Mode mode=Header;
    if (prvStream){
        while(getline(*prvStream,line)){
            lineNumber++;
            replace(line.begin(), line.end(), '\t', ' ');
            trim_all(line);
            if (!line.empty()){
                vector<string> tokens;
                split(tokens, line, is_any_of(":"));
                if (mode==Header){

                }*/
}
