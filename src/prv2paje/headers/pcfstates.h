#ifndef PCFSTATES_H
#define PCFSTATES_H

#include <map>
#include <string>
#include "rgb.h"

using namespace std;

namespace prv2paje{

class PcfStates
{
public:
    PcfStates();
    ~PcfStates();
    void addValue(int value, string label);
    void addColor(int value, RGB color);

    map<int, string> *getValues() const;

    map<int, RGB> *getColors() const;

private:
    map<int, string> *values;
    map<int, RGB> *colors;
};

}

#endif // PCFSTATES_H
