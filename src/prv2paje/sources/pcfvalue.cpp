#include "pcfvalue.h"


int prv2paje::PcfValue::getType() const
{
    return type;
}

void prv2paje::PcfValue::setType(int value)
{
    type = value;
}

string prv2paje::PcfValue::getLongLabel() const
{
    return longLabel;
}

void prv2paje::PcfValue::setLongLabel(const string &value)
{
    longLabel = value;
}

string prv2paje::PcfValue::getShortLabel() const
{
    return shortLabel;
}

void prv2paje::PcfValue::setShortLabel(const string &value)
{
    shortLabel = value;
}

prv2paje::PcfValue::PcfValue():type(0), shortLabel(0), longLabel(0)
{

}

prv2paje::PcfValue::PcfValue(int type, string label):type(type), shortLabel(label), longLabel(label)
{

}

prv2paje::PcfValue::PcfValue(int type, string shortLabel, string longLabel):type(type),shortLabel(shortLabel),longLabel(longLabel)
{

}

void prv2paje::PcfValue::setLabel(string value)
{
    shortLabel=value;
    longLabel=value;
}
