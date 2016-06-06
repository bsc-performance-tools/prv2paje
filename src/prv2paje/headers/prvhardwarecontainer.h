#ifndef PRVHARDWARECONTAINER_H
#define PRVHARDWARECONTAINER_H

#include "prvcontainer.h"


namespace prv2paje{

    enum PrvHardwareContainerLevel{System, Node, Cpu, Thread};

    class PrvHardwareContainer : public PrvContainer
    {
    public:
        PrvHardwareContainer();
    private:
        PrvHardwareContainerLevel level;
        PrvHardwareContainer * parent;
    };

}

#endif // PRVHARDWARECONTAINER_H
