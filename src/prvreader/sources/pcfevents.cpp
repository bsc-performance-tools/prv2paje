#include "pcfevents.h"


prvreader::PcfEvents::PcfEvents(int gradient, int type):gradient(gradient), type(type), label("")
{

}

prvreader::PcfEvents::PcfEvents(int gradient, int type, string label): gradient(gradient), type(type), label(label)
{

}

int prvreader::PcfEvents::getGradient() const
{
    return gradient;
}

void prvreader::PcfEvents::setGradient(int value)
{
    gradient = value;
}

int prvreader::PcfEvents::getType() const
{
    return type;
}

void prvreader::PcfEvents::setType(int value)
{
    type = value;
}

string prvreader::PcfEvents::getLabel() const
{
    return label;
}

void prvreader::PcfEvents::setLabel(const string &value)
{
    label = value;
}

prvreader::PcfEventType prvreader::PcfEvents::getEventType() const
{
    return eventType;
}

void prvreader::PcfEvents::setEventType(const PcfEventType &value)
{
    eventType = value;
}

map<int, prvreader::PcfValue*> * prvreader::PcfEvents::getValues() const
{
    return values;
}

void prvreader::PcfEvents::setValues(map<int, PcfValue*> *value)
{
    values = value;
}
