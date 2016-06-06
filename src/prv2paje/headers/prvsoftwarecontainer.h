#ifndef PRVSOFTWARECONTAINER_H
#define PRVSOFTWARECONTAINER_H

#include "prvcontainer.h"

namespace prv2paje{

    enum PrvSoftwareContainerLevel{Application, Task, Thread, PrvSoftwareContainerLevel_COUNT};

    class PrvSoftwareContainer : public PrvContainer
    {
    public:
        PrvSoftwareContainer();
        static void InitInstanciation();
        static void NewInstance(PrvSoftwareContainerLevel);
    private:
        PrvSoftwareContainerLevel level;
        PrvSoftwareContainer *parent;
        static int instanciation[PrvSoftwareContainerLevel_COUNT];
        int cpu;
    };

}

#endif // PRVSOFTWARECONTAINER_H
