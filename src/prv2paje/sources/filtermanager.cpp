#include "filtermanager.h"

prv2paje::FilterManager::FilterManager(string filterPath):filterPath(filterPath),filter(new PrvFilter())
{
    filterValid=false;
    filterStream=new ifstream();
    filterStream->open(filterPath.c_str());
    if (filterStream->is_open()){
        filterValid=true;
    }
    filter->setEnabled(filterValid);
}

prv2paje::FilterManager::FilterManager():filter(new PrvFilter())
{
    filterValid=false;
    filter->setEnabled(filterValid);
}

prv2paje::FilterManager::~FilterManager()
{
    delete filter;
}

bool prv2paje::FilterManager::getFilterValid() const
{
    return filterValid;
}

void prv2paje::FilterManager::parse()
{
    if (!filter->getEnabled()){
        Message::Info("Filtering disabled",2);
        return;
    }
    Message::Info("Filtering enabled",2);
    long lineNumber=0;
    Mode mode = Unknown;
    string line;
    while(getline(*filterStream,line)){
        lineNumber++;
        //replace(line.begin(), line.end(), '\t', ' ');
        //trim_all(line);
        if (line.compare(FILTER_TYPES)==0){
            mode = Types;
            Message::Info("Filtering types",2);
            filter->setDisableStates(true);
            filter->setDisableEvents(true);
            filter->setDisableCommunications(true);
        }else if (line.compare(FILTER_EVENT_TYPES)==0){
            Message::Info("Filtering event types",2);
            mode = EventTypes;
            filter->setDisableFilterTypes(false);
        }else{
            if (mode==Types){
                if (line.compare("*")==0){
                    filter->setDisableStates(false);
                    filter->setDisableEvents(false);
                    filter->setDisableCommunications(false);
                    Message::Info("All types will be converted",3);
                    mode=Unknown;
                }else if (line.compare(PRV_BODY_STATE)==0){
                    filter->setDisableStates(false);
                    Message::Info("States will be converted",3);
                }else if (line.compare(PRV_BODY_EVENTS)==0){
                    filter->setDisableEvents(false);
                    Message::Info("Events will be converted",3);
                }else if (line.compare(PRV_BODY_COMMUNICATION)==0){
                    filter->setDisableCommunications(false);
                    Message::Info("Communications will be converted",3);
                }
            }else if (mode==EventTypes){
                if (line.compare("*")==0){
                    filter->setDisableFilterTypes(true);
                    Message::Info("All events types will be converted",3);
                }else{
                    try{
                        int type=stoi(line.c_str());
                        filter->addUnfilteredType(type);
                        Message::Info(line + " event types will be converted",3);
                    }catch (const std::invalid_argument& err) {
                        Message::Warning("filtering: invalid event type " + line + "will be ignored...");
                    }
                }
            }
        }
    }

}

PrvFilter *prv2paje::FilterManager::getFilter() const
{
    return filter;
}

