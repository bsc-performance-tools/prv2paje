#include "prvfilter.h"


prvreader::PrvFilter::PrvFilter()
{
    setEnabled(false);
}

bool prvreader::PrvFilter::getEnabled() const
{
    return enabled;
}

void prvreader::PrvFilter::setEnabled(bool value)
{
    enabled = value;
    if (!enabled){
        disableStates=false;
        disableEvents=false;
        disableCommunications=false;
        disableFilterTypes=true;
    }
}

bool prvreader::PrvFilter::getDisableStates() const
{
    return disableStates;
}

void prvreader::PrvFilter::setDisableStates(bool value)
{
    if (enabled){
        disableStates = value;
    }
}

bool prvreader::PrvFilter::getDisableEvents() const
{
    return disableEvents;
}

void prvreader::PrvFilter::setDisableEvents(bool value)
{
    if (enabled){
        disableEvents = value;
    }
}

bool prvreader::PrvFilter::getDisableCommunications() const
{
    return disableCommunications;
}

void prvreader::PrvFilter::setDisableCommunications(bool value)
{
    if (enabled){
        disableCommunications = value;
    }
}

bool prvreader::PrvFilter::getDisableFilterTypes() const
{
    return disableFilterTypes;
}

void prvreader::PrvFilter::setDisableFilterTypes(bool value)
{
    if (enabled){
        disableFilterTypes = value;
    }
}

void prvreader::PrvFilter::addUnfilteredType(string type)
{
    if (!disableFilterTypes){
        unfilteredTypes[atoi(type.c_str())]=true;
    }
}

bool prvreader::PrvFilter::isFiltered(string type)
{
    if (!disableFilterTypes){
        if (unfilteredTypes.count(atoi(type.c_str()))>0){
            return true;
        }
    }
    return false;
}

void prvreader::PrvFilter::addUnfilteredType(int type)
{
    if (!disableFilterTypes){
        unfilteredTypes[type]=true;
    }
}

bool prvreader::PrvFilter::isFiltered(int type)
{
    if (!disableFilterTypes){
        if (unfilteredTypes.count(type)>0){
            return false;
        }
        else{
            return true;
        }
    }
    return false;
}
