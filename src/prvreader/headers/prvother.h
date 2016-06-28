#ifndef PRVOTHER_H
#define PRVOTHER_H

#include "prvevent.h"

namespace prvreader{

    class PrvOther: public PrvEvent
    {
    public:
        PrvOther();
        PrvOther(long linenumber);
        ~PrvOther();
    };

}

#endif // PRVOTHER_H
