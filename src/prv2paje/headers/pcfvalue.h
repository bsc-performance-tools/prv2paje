#ifndef PCFVALUE_H
#define PCFVALUE_H

#include <string>

using namespace std;

namespace prv2paje{

    class PcfValue
    {
    public:
        PcfValue();
        PcfValue(int type, string label);
        int getType() const;
        void setType(int value);
        string getLabel() const;
        void setLabel(const string &value);
    private:
        int type;
        string label;
    };

}

#endif // PCFVALUE_H
