#ifndef PRVTHREADCONTAINER_H
#define PRVTHREADCONTAINER_H

#include "prvhardwarecontainer.h"

namespace prv2paje{

    class PrvThreadContainer : public PrvHardwareContainer
    {
    public:
        PrvThreadContainer();
    private:
        int cpu;
        int app;
        int task;
    };

}

#endif // PRVTHREADCONTAINER_H
