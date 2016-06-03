#include "pcfevents.h"

prv2paje::PcfEvents::PcfEvents()
{

}

int prv2paje::PcfEvents::getGradient() const
{
    return gradient;
}

void prv2paje::PcfEvents::setGradient(int value)
{
    gradient = value;
}

int prv2paje::PcfEvents::getType() const
{
    return type;
}

void prv2paje::PcfEvents::setType(int value)
{
    type = value;
}

string prv2paje::PcfEvents::getLabel() const
{
    return label;
}

void prv2paje::PcfEvents::setLabel(const string &value)
{
    label = value;
}

prv2paje::PcfEventType prv2paje::PcfEvents::getEventType() const
{
    return eventType;
}

void prv2paje::PcfEvents::setEventType(const PcfEventType &value)
{
    eventType = value;
}

map<int, prv2paje::PcfValue> * prv2paje::PcfEvents::getValues() const
{
    return values;
}

void prv2paje::PcfEvents::setValues(map<int, PcfValue> *value)
{
    values = value;
}
