#include "pajependingendstate.h"

prv2paje::PajePendingEndState::PajePendingEndState()
{

}

prv2paje::PajePendingEndState::PajePendingEndState(long timestamp):PajePendingEvent(timestamp)
{

}

string prv2paje::PajePendingEndState::className()
{
    return "PajePendingEndState";
}
