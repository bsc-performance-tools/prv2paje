#ifndef PRVEVENT_H
#define PRVEVENT_H

namespace prveventtype{

    enum PrvEventType{Events, State, Communications, NotConform, Header, Skip, End, Critical, Filtered};

}

namespace prvreader{

    class PrvEvent
    {
    public:
        PrvEvent();
        PrvEvent(long linenumber);
        PrvEvent(int cpu, int app, int task, int thread, long timestamp, long linenumber);
        virtual ~PrvEvent() {}

        int getCpu() const;
        void setCpu(int value);

        int getApp() const;
        void setApp(int value);

        int getTask() const;
        void setTask(int value);

        int getThread() const;
        void setThread(int value);

        long getTimestamp() const;
        void setTimestamp(long value);

        long getLineNumber() const;
        void setLineNumber(long value);

        prveventtype::PrvEventType getType() const;
        void setType(const prveventtype::PrvEventType &value);

    protected:
        int cpu;
        int app;
        int task;
        int thread;
        long timestamp;
        long lineNumber;
        prveventtype::PrvEventType type;
    };

}

#endif // PRVEVENT_H
