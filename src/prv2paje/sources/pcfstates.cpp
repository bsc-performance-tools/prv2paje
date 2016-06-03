#include "pcfstates.h"


prv2paje::PcfStates::PcfStates():values(new map<int, string>()), colors(new map<int, RGB>())
{

}

prv2paje::PcfStates::~PcfStates()
{
    delete values;
    delete colors;
}

void prv2paje::PcfStates::addValue(int value, string label)
{
    values[value]=label;
}

void prv2paje::PcfStates::addColor(int value, RGB color)
{
    colors[value]=value;
}

map<int, RGB> prv2paje::PcfStates::getColors() const
{
    return colors;
}

map<int, string> prv2paje::PcfStates::getValues() const
{
    return values;
}
