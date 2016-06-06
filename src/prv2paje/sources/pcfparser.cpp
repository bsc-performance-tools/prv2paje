#include "pcfparser.h"


prv2paje::PcfParser::PcfParser(ifstream *pcfStream):
    pcfStream(pcfStream), pcfOptions(new map<string, PcfOptions>()), pcfStates(new PcfStates()),
    pcfEvents(new map<int, PcfEvents*>()), pcfGradient(new PcfGradient()), pcfValues(new vector<map<int, PcfValue*>* >())
{

}

void prv2paje::PcfParser::parse(){
    string line;
    Mode mode=Unknown;
    string currentOption;
    int lineNumber=1;
    vector<int> eventBunch;
    if (pcfStream){
        while(getline(*pcfStream,line)){
            replace(line.begin(), line.end(), '\t', ' ');
            trim_all(line);
            if (!line.empty()){
                vector<string> tokens;
                split(tokens, line, is_any_of(" "));
                if (tokens.size()==1){
                    //Mode Options
                    if (tokens.operator [](0).compare(STATES)==0){
                        mode=States;
                    }else if(tokens.operator [](0).compare(STATES_COLOR)==0){
                        mode=StatesColor;
                    }else if(tokens.operator [](0).compare(EVENT_TYPE)==0){
                        mode=EventType;
                        eventBunch.clear();
                    }else if(tokens.operator [](0).compare(VALUES)==0){
                        mode=Values;
                        pcfValues->push_back(new map<int, PcfValue*>());
                        int i;
                        for (i=0; i<eventBunch.size();i++){
                           pcfEvents->at(eventBunch[i])->setEventType(State);
                           pcfEvents->at(eventBunch[i])->setValues(pcfValues->at(pcfValues->size()-1));
                        }
                    }else{
                        mode=Options;
                    }
                }else{
                    switch(mode){
                        case States:
                        {
                            string label="";
                            int i;
                            for (i=1;i<tokens.size();i++){
                                label+=tokens[i];
                                label+=" ";
                            }
                            trim_right(label);
                            pcfStates->addValue(atoi(tokens.operator [](0).c_str()), label);
                        }
                        break;
                        case StatesColor:
                        {
                            RGB rgb;
                            rgb.setRGBFromPcf(tokens[1]);
                            pcfStates->addColor(atoi(tokens.operator [](0).c_str()), rgb);
                        }
                        break;
                        case EventType:
                        {
                            string label="";
                            int i;
                            for (i=2;i<tokens.size();i++){
                                label+=tokens[i];
                                label+=" ";
                            }
                            trim_right(label);
                            int type=atoi(tokens.operator [](1).c_str());
                            pcfEvents->at(type)=new PcfEvents(atoi(tokens.operator [](0).c_str()), type, label);
                            pcfEvents->at(type)->setEventType(Undefined);
                            eventBunch.push_back(type);
                        }
                        break;
                        case Values:
                        {
                            string label="";
                            int i;
                            for (i=2;i<tokens.size();i++){
                                label+=tokens[i];
                                label+=" ";
                            }
                            trim_right(label);
                            int value=atoi(tokens.operator [](0).c_str());
                            pcfValues->at(pcfValues->size()-1)->at(value)=new PcfValue(value,tokens[1]);
                            if (label.compare("")!=0){
                                pcfValues->at(pcfValues->size()-1)->at(value)->setLongLabel(label);
                            }
                        }
                        break;
                        default:
                        break;
                    }
                }
            }
        }
    }
}
