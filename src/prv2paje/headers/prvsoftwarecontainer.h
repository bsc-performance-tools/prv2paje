#ifndef PRVSOFTWARECONTAINER_H
#define PRVSOFTWARECONTAINER_H

#include "prvcontainer.h"

//Will not be used for the moment

namespace prv2paje{

    enum PrvSoftwareContainerLevel{System, Application, Task};

    class PrvSoftwareContainer : public PrvContainer
    {
    public:
        PrvSoftwareContainer();
    private:
        PrvSoftwareContainerLevel level;
        PrvSoftwareContainer *parent;
        int cpu;
    };

}

#endif // PRVSOFTWARECONTAINER_H
