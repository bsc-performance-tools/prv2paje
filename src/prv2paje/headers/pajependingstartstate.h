#ifndef PAJEPENDINGSTARTSTATE_H
#define PAJEPENDINGSTARTSTATE_H

#include <string>

#include "pajependingevent.h"

using namespace std;

namespace prv2paje{

    class PajePendingStartState: public PajePendingEvent
    {
    public:
        PajePendingStartState();
        PajePendingStartState(double timestamp);
        string className();
        string getValue() const;
        void setValue(const string &value);

    private:
        string value;
    };

}

#endif // PAJEPENDINGSTARTSTATE_H
