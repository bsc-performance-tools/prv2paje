#include "pajependingendcommunication.h"

prv2paje::PajePendingEndCommunication::PajePendingEndCommunication()
{

}

prv2paje::PajePendingEndCommunication::PajePendingEndCommunication(double timestamp):PajePendingCommunication(timestamp)
{

}

string prv2paje::PajePendingEndCommunication::className()
{
    return "PajePendingEndCommunication";
}

void prv2paje::PajePendingEndCommunication::pushMe()
{
    poti_EndLink(timestamp, container.c_str(), type.c_str(), subContainer.c_str(), value.c_str(), key.c_str());
}
