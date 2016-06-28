#include "prvcommunications.h"

long prvreader::PrvCommunications::getTimestampHW() const
{
    return timestampHW;
}

void prvreader::PrvCommunications::setTimestampHW(long value)
{
    timestampHW = value;
}

long prvreader::PrvCommunications::getTimestampEnd() const
{
    return timestampEnd;
}

void prvreader::PrvCommunications::setTimestampEnd(long value)
{
    timestampEnd = value;
}

long prvreader::PrvCommunications::getTimestampHWEnd() const
{
    return timestampHWEnd;
}

void prvreader::PrvCommunications::setTimestampHWEnd(long value)
{
    timestampHWEnd = value;
}

string prvreader::PrvCommunications::getValue() const
{
    return value;
}

void prvreader::PrvCommunications::setValue(const string &val)
{
    value = val;
}

int prvreader::PrvCommunications::getThread2() const
{
    return thread2;
}

void prvreader::PrvCommunications::setThread2(int value)
{
    thread2 = value;
}

int prvreader::PrvCommunications::getTask2() const
{
    return task2;
}

void prvreader::PrvCommunications::setTask2(int value)
{
    task2 = value;
}

int prvreader::PrvCommunications::getApp2() const
{
    return app2;
}

void prvreader::PrvCommunications::setApp2(int value)
{
    app2 = value;
}

int prvreader::PrvCommunications::getCpu2() const
{
    return cpu2;
}

void prvreader::PrvCommunications::setCpu2(int value)
{
    cpu2 = value;
}

prvreader::PrvCommunications::PrvCommunications()
{
    type=prveventtype::Communications;
}

prvreader::PrvCommunications::PrvCommunications(int cpu, int app, int task, int thread, long timestamp, long linenumber, int cpu2, int app2, int task2, int thread2, long timestampEnd, long timestampHW, long timestampHWEnd, string value):
    PrvEvent(cpu, app, task, thread, timestamp, linenumber), timestampEnd(timestampEnd), timestampHW(timestampHW), timestampHWEnd(timestampHWEnd), value(value), cpu2(cpu2), app2(app2), task2(task2), thread2(thread2)
{
    type=prveventtype::Communications;
}

prvreader::PrvCommunications::~PrvCommunications()
{

}
