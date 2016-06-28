#ifndef PRVCOMMUNICATIONS_H
#define PRVCOMMUNICATIONS_H

#include "prvevent.h"
#include <string>

using namespace std;

namespace prvreader{

    class PrvCommunications : public PrvEvent
    {
    public:
        PrvCommunications();
        PrvCommunications(int cpu, int app, int task, int thread, long timestamp, long linenumber, int cpu2, int app2, int task2, int thread2, long timestampEnd, long timestampHW, long timestampHWEnd, string value);
        ~PrvCommunications();

        long getTimestampHW() const;
        void setTimestampHW(long value);

        long getTimestampEnd() const;
        void setTimestampEnd(long value);

        long getTimestampHWEnd() const;
        void setTimestampHWEnd(long value);

        string getValue() const;
        void setValue(const string &value);

        int getCpu2() const;
        void setCpu2(int value);

        int getApp2() const;
        void setApp2(int value);

        int getTask2() const;
        void setTask2(int value);

        int getThread2() const;
        void setThread2(int value);

    private:
        int cpu2;
        int app2;
        int task2;
        int thread2;
        long timestampHW;
        long timestampEnd;
        long timestampHWEnd;
        string value;
    };

}

#endif // PRVCOMMUNICATIONS_H
