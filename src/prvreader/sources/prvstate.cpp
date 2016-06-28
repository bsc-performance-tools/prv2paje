#include "prvstate.h"

prvreader::PrvState::PrvState()
{
    type=prveventtype::State;
}

prvreader::PrvState::PrvState(int cpu, int app, int task, int thread, long timestamp, long lineNumber, long endTimestamp, string value):PrvEvent(cpu, app, task, thread, timestamp, lineNumber), endTimestamp(endTimestamp), value(value)
{
    type=prveventtype::State;
}

prvreader::PrvState::~PrvState()
{

}

string prvreader::PrvState::getValue() const
{
    return value;
}

void prvreader::PrvState::setValue(const string &val)
{
    value = val;
}

long prvreader::PrvState::getEndTimestamp() const
{
    return endTimestamp;
}

void prvreader::PrvState::setEndTimestamp(long value)
{
    endTimestamp = value;
}
