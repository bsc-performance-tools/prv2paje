#include "pajependingstartstate.h"

prv2paje::PajePendingStartState::PajePendingStartState()
{

}

prv2paje::PajePendingStartState::PajePendingStartState(double timestamp):PajePendingEvent(timestamp)
{

}

string prv2paje::PajePendingStartState::className()
{
    return "PajePendingStartState";
}

string prv2paje::PajePendingStartState::getValue() const
{
    return value;
}

void prv2paje::PajePendingStartState::setValue(const string &val)
{
    value = val;
}
