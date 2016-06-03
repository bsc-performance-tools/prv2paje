#include "pcfoptions.h"

map<string, string> * prv2paje::PcfOptions::getOptions() const
{
    return options;
}

string prv2paje::PcfOptions::getName() const
{
    return name;
}

prv2paje::PcfOptions::PcfOptions(string name):name(name),options(new map<string, string>())
{

}

prv2paje::PcfOptions::~PcfOptions()
{
    delete options;
}

void prv2paje::PcfOptions::addOption(string name, string value)
{
    options->operator [](name)=value;
}
