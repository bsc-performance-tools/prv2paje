#include "pcfvalue.h"


int prv2paje::PcfValue::getType() const
{
    return type;
}

void prv2paje::PcfValue::setType(int value)
{
    type = value;
}

string prv2paje::PcfValue::getLabel() const
{
    return label;
}

prv2paje::PcfValue::PcfValue():type(0), label(0)
{

}

prv2paje::PcfValue::PcfValue(int type, string label):type(type), label(label)
{

}

void prv2paje::PcfValue::setLabel(const string &value)
{
    label=value;
}
