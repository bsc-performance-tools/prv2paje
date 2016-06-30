#include "pajependingendstate.h"

prv2paje::PajePendingEndState::PajePendingEndState()
{

}

prv2paje::PajePendingEndState::PajePendingEndState(double timestamp):PajePendingEvent(timestamp)
{

}

string prv2paje::PajePendingEndState::className()
{
    return "PajePendingEndState";
}

void prv2paje::PajePendingEndState::pushMe()
{
    poti_PopState (timestamp, container.c_str(), type.c_str());
        LastTimestamp=timestamp;
}
