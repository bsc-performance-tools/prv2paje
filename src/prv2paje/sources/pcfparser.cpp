#include "pcfparser.h"


prv2paje::PcfParser::PcfParser(ifstream *pcfStream):
    pcfStream(pcfStream), pcfOptions(new map<string, PcfOptions*>()), pcfStates(new PcfStates()),
    pcfEvents(new map<int, PcfEvents*>()), pcfGradient(new PcfGradient()), pcfValues(new vector<map<int, PcfValue*>* >())
{
    parse();
}

prv2paje::PcfParser::~PcfParser()
{

    for (auto it = pcfOptions->begin();it != pcfOptions->end(); it++) {
        delete it->second;
    }
    delete pcfOptions;
    delete pcfStates;
    for (auto it = pcfEvents->begin();it != pcfEvents->end(); it++){
        delete it->second;
    }
    delete pcfEvents;
    delete pcfGradient;
    for (auto it = pcfValues->begin();it != pcfValues->end(); it++){
        for (auto it2 = (*it)->begin();it2 != (*it)->end(); it2++){
            delete it2->second;
        }
        delete (*it);
    }
    delete pcfValues;
}

void prv2paje::PcfParser::parse(){
    string line;
    Mode mode=Unknown;
    string currentOption;
    int lineNumber=0;
    vector<int> eventBunch;
    if (pcfStream){
        while(getline(*pcfStream,line)){
            lineNumber++;
            replace(line.begin(), line.end(), '\t', ' ');
            trim_all(line);
            if (!line.empty()){
                vector<string> tokens;
                split(tokens, line, is_any_of(" "));
                if (tokens.size()==1){
                    if (tokens.operator [](0).compare(PCF_STATES)==0){
                        mode=States;
                    }else if(tokens.operator [](0).compare(PCF_STATES_COLOR)==0){
                        mode=StatesColor;
                    }else if (tokens.operator [](0).compare(PCF_GRADIENT_NAMES)==0){
                        mode=GradientName;
                    }else if(tokens.operator [](0).compare(PCF_GRADIENT_COLOR)==0){
                        mode=GradientColor;
                    }else if(tokens.operator [](0).compare(PCF_EVENT_TYPE)==0){
                        mode=EventType;
                        eventBunch.clear();
                    }else if(tokens.operator [](0).compare(PCF_VALUES)==0){
                        mode=Values;
                        pcfValues->push_back(new map<int, PcfValue*>());
                        int i;
                        for (i=0; i<eventBunch.size();i++){
                           pcfEvents->at(eventBunch[i])->setEventType(Event);
                           pcfEvents->at(eventBunch[i])->setValues(pcfValues->at(pcfValues->size()-1));
                        }
                    }else{
                        mode=Options;
                        pcfOptions->operator [](tokens[0])=new PcfOptions(tokens[0]);
                        currentOption=tokens[0];
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
                        case GradientName:
                        {
                            string label="";
                            int i;
                            for (i=1;i<tokens.size();i++){
                                label+=tokens[i];
                                label+=" ";
                            }
                            trim_right(label);
                            pcfGradient->addValue(atoi(tokens.operator [](0).c_str()), label);
                        }
                        break;
                        case GradientColor:
                        {
                            RGB rgb;
                            rgb.setRGBFromPcf(tokens[1]);
                            pcfGradient->addColor(atoi(tokens.operator [](0).c_str()), rgb);
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
                            pcfEvents->operator [](type)=new PcfEvents(atoi(tokens.operator [](0).c_str()), type, label);
                            pcfEvents->operator [](type)->setEventType(Variable);
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
                            if (value==PCF_EVENT_STATE_VALUE_END){
                                for (i=0; i<eventBunch.size();i++){
                                   pcfEvents->at(eventBunch[i])->setEventType(State);
                                }
                            }
                            pcfValues->operator [](pcfValues->size()-1)->operator [](value)=new PcfValue(value,tokens[1]);
                            if (label.compare("")!=0){
                                pcfValues->operator [](pcfValues->size()-1)->operator [](value)->setLongLabel(label);
                            }
                        }
                        break;
                        case Options:
                        {
                            string label="";
                            int i;
                            for (i=1;i<tokens.size();i++){
                                label+=tokens[i];
                                label+=" ";
                            }
                            trim_right(label);
                            pcfOptions->operator [](currentOption)->addOption(tokens[0], label);
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

vector<map<int, PcfValue *> *> * prv2paje::PcfParser::getPcfValues() const
{
    return pcfValues;
}

PcfGradient * prv2paje::PcfParser::getPcfGradient() const
{
    return pcfGradient;
}

map<int, PcfEvents *> * prv2paje::PcfParser::getPcfEvents() const
{
    return pcfEvents;
}

PcfStates * prv2paje::PcfParser::getPcfStates() const
{
    return pcfStates;
}

map<string, PcfOptions *> * prv2paje::PcfParser::getPcfOptions() const
{
    return pcfOptions;
}

void prv2paje::PcfParser::setPcfOptions(map<string, PcfOptions *> *value)
{
    pcfOptions = value;
}
