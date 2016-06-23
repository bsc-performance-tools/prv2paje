#ifndef PAJEPENDINGENDCOMMUNICATION_H
#define PAJEPENDINGENDCOMMUNICATION_H

#include "pajependingcommunication.h"

namespace prv2paje{

    class PajePendingStartCommunication : PajePendingCommunication
    {
    public:
        PajePendingStartCommunication();
        PajePendingStartCommunication(double timestamp);
        string className();
    };

}

#endif // PAJEPENDINGENDCOMMUNICATION_H
