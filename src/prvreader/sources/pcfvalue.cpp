#include "pcfvalue.h"


int prvreader::PcfValue::getType() const
{
    return type;
}

void prvreader::PcfValue::setType(int value)
{
    type = value;
}

string prvreader::PcfValue::getLabel() const
{
    return label;
}

prvreader::PcfValue::PcfValue():type(0), label(0)
{

}

prvreader::PcfValue::PcfValue(int type, string label):type(type), label(label)
{

}

void prvreader::PcfValue::setLabel(const string &value)
{
    label=value;
}
