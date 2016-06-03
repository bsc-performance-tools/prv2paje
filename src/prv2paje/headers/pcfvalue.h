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
        PcfValue(int type, string shortLabel, string longLabel);
        int getType() const;
        void setType(int value);

        string getLongLabel() const;
        void setLongLabel(const string &value);

        string getShortLabel() const;
        void setShortLabel(const string &value);

        void setLabel(string value);

    private:
        int type;
        string longLabel;
        string shortLabel;
    };

}

#endif // PCFVALUE_H
