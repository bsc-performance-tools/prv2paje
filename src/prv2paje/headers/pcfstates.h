#ifndef PCFSTATES_H
#define PCFSTATES_H

#include <map>
#include "rgb.h"

namespace prv2paje{

class PcfStates
{
public:
    PcfStates();
    ~PcfStates();
    void addValue(int value, string label);
    void addColor(int value, RGB color);

private:
    map<int, string> *values;
    map<int, RGB> *colors;
};

}

#endif // PCFSTATES_H
