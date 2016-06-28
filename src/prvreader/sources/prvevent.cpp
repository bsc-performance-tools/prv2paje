#include "prvevent.h"

int prvreader::PrvEvent::getCpu() const
{
    return cpu;
}

void prvreader::PrvEvent::setCpu(int value)
{
    cpu = value;
}

int prvreader::PrvEvent::getApp() const
{
    return app;
}

void prvreader::PrvEvent::setApp(int value)
{
    app = value;
}

int prvreader::PrvEvent::getTask() const
{
    return task;
}

void prvreader::PrvEvent::setTask(int value)
{
    task = value;
}

int prvreader::PrvEvent::getThread() const
{
    return thread;
}

void prvreader::PrvEvent::setThread(int value)
{
    thread = value;
}

long prvreader::PrvEvent::getTimestamp() const
{
    return timestamp;
}

void prvreader::PrvEvent::setTimestamp(long value)
{
    timestamp = value;
}

long prvreader::PrvEvent::getLineNumber() const
{
    return lineNumber;
}

void prvreader::PrvEvent::setLineNumber(long value)
{
    lineNumber = value;
}

prveventtype::PrvEventType prvreader::PrvEvent::getType() const
{
    return type;
}

void prvreader::PrvEvent::setType(const prveventtype::PrvEventType &value)
{
    type = value;
}

prvreader::PrvEvent::PrvEvent()
{
    type=prveventtype::Skip;
}

prvreader::PrvEvent::PrvEvent(long lineNumber):lineNumber(lineNumber)
{
    type=prveventtype::NotConform;
}

prvreader::PrvEvent::PrvEvent(int cpu, int app, int task, int thread, long timestamp, long linenumber):cpu(cpu), app(app), task(task), thread(thread), timestamp(timestamp), lineNumber(linenumber)
{
    type=prveventtype::Skip;
}
