#include "pcfstates.h"


prvreader::PcfStates::PcfStates():values(new map<int, string>()), colors(new map<int, RGB>())
{

}

prvreader::PcfStates::~PcfStates()
{
    delete values;
    delete colors;
}

void prvreader::PcfStates::addValue(int value, string label)
{
    values->operator [](value)=label;
}

void prvreader::PcfStates::addColor(int value, RGB color)
{
    colors->operator [](value)=color;
}

map<int, prvreader::RGB> *prvreader::PcfStates::getColors() const
{
    return colors;
}

map<int, string> *prvreader::PcfStates::getValues() const
{
    return values;
}
