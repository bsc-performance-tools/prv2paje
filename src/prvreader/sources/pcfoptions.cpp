#include "pcfoptions.h"

map<string, string> * prvreader::PcfOptions::getOptions() const
{
    return options;
}

string prvreader::PcfOptions::getName() const
{
    return name;
}

prvreader::PcfOptions::PcfOptions(string name):name(name),options(new map<string, string>())
{

}

prvreader::PcfOptions::~PcfOptions()
{
    delete options;
}

void prvreader::PcfOptions::addOption(string name, string value)
{
    options->operator [](name)=value;
}
