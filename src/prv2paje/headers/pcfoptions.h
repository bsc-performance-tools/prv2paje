#ifndef PCFOPTIONS_H
#define PCFOPTIONS_H

#include <map>
#include <string>

using namespace std;

namespace prv2paje{

class PcfOptions
{
public:
    PcfOptions(string name);

    ~PcfOptions();

    void addOption(string name, string value);

    map<string, string> *getOptions() const;

    string getName() const;

private:
    string name;
    map<string, string> *options;
};

}

#endif // PCFOPTIONS_H
