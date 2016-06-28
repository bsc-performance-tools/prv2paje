#ifndef PRVSTATE_H
#define PRVSTATE_H


#include <string>
#include "prvevent.h"

using namespace std;

namespace prvreader{

    class PrvState : public PrvEvent
    {
    public:
        PrvState();
        PrvState(int cpu, int app, int task, int thread, long timestamp, long lineNumber, long endTimestamp, string value);
        ~PrvState();
        long getEndTimestamp() const;
        void setEndTimestamp(long value);
        string getValue() const;
        void setValue(const string &value);

    private:
        long endTimestamp;
        string value;
    };

}

#endif // PRVSTATE_H
