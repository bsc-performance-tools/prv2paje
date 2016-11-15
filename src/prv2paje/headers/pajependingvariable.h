#ifndef PAJEPENDINGVARIABLE_H
#define PAJEPENDINGVARIABLE_H

#include <string>

#include "pajependingevent.h"
#include <message.h>
#include <limits>

using namespace std;

namespace prv2paje{

    class PajePendingVariable: public PajePendingEvent
    {
    public:
        PajePendingVariable();
        PajePendingVariable(double timestamp);
        string className();
        void pushMe();
        long long getValue() const;
        void setValue(long long value);

    private:
        long long value;
    };

}

#endif // PAJEPENDINGVARIABLE_H
