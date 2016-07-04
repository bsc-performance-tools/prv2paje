#include "pcfparser.h"


prvreader::PcfParser::PcfParser(ifstream *pcfStream, PrvFilter* filter):
    pcfStream(pcfStream), filter(filter), pcfOptions(new map<string, PcfOptions*>()), pcfStates(new PcfStates()),
    pcfEvents(new map<int, PcfEvents*>()), pcfGradient(new PcfGradient()), pcfValues(new vector<map<int, PcfValue*>* >())
{
}

prvreader::PcfParser::~PcfParser()
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

void prvreader::PcfParser::parse(){
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
                           pcfEvents->at(eventBunch[i])->setEventType(pcfeventtype::Event);
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
                            pcfEvents->operator [](type)->setEventType(pcfeventtype::Variable);
                            eventBunch.push_back(type);
                        }
                        break;
                        case Values:
                        {
                            int value=atoi(tokens.operator [](0).c_str());
                            int i;
                            if (value==PCF_EVENT_STATE_VALUE_END){
                                for (i=0; i<eventBunch.size();i++){
                                   pcfEvents->at(eventBunch[i])->setEventType(pcfeventtype::State);
                                }
                            }
                            string label;

                            for (i=1;i<tokens.size();i++){
                                label+=tokens[i];
                                label+=" ";
                            }
                            trim_right(label);
                            vector<string> tokensTemp;
                            split(tokensTemp, label, is_any_of("[]"));
                            if(tokensTemp.size()==0){

                            }else if (tokensTemp.size()==1){
                                label=tokensTemp[0];
                            }else if (tokensTemp.size()==2){
                                label=tokensTemp[1];
                            }else{
                                label=tokensTemp[1];
                            }
                            pcfValues->operator [](pcfValues->size()-1)->operator [](value)=new PcfValue(value,label);
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
    filtering();
}

void prvreader::PcfParser::filtering()
{
    if (filter->getDisableStates()){
        delete pcfStates;
        pcfStates=new PcfStates();
    }
    if (filter->getDisableEvents()){
        for (auto const &it : *pcfEvents){
            delete it.second;
        }
        pcfEvents->clear();
    }else if (filter->getDisableFilterTypes()){
        return;
    }else{
        list<PcfEvents*> temp;
        for (auto it = pcfEvents->begin(); it != pcfEvents->end(); it++){
            if (filter->isFiltered(it->first)){
                temp.push_back(it->second);
                pcfEvents->erase(it);
            }
        }
        for (PcfEvents* it: temp){
            delete it;
        }
    }
}

prvreader::PrvFilter *prvreader::PcfParser::getFilter() const
{
    return filter;
}

void prvreader::PcfParser::setFilter(PrvFilter *value)
{
    filter = value;
}

vector<map<int, prvreader::PcfValue *> *> * prvreader::PcfParser::getPcfValues() const
{
    return pcfValues;
}

prvreader::PcfGradient * prvreader::PcfParser::getPcfGradient() const
{
    return pcfGradient;
}

map<int, prvreader::PcfEvents *> * prvreader::PcfParser::getPcfEvents() const
{
    return pcfEvents;
}

prvreader::PcfStates * prvreader::PcfParser::getPcfStates() const
{
    return pcfStates;
}

map<string, prvreader::PcfOptions *> * prvreader::PcfParser::getPcfOptions() const
{
    return pcfOptions;
}
