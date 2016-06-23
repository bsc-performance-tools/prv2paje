#ifndef PAJEPENDINGSTARTCOMMUNICATION_H
#define PAJEPENDINGSTARTCOMMUNICATION_H

#include "pajependingcommunication.h"

namespace prv2paje{

    class PajePendingStartCommunication : public PajePendingCommunication
    {
    public:
        PajePendingStartCommunication();
        PajePendingStartCommunication(double timestamp);
        string className();
    };

}

#endif // PAJEPENDINGSTARTCOMMUNICATION_H
