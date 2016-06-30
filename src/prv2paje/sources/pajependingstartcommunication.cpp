#include "pajependingstartcommunication.h"

prv2paje::PajePendingStartCommunication::PajePendingStartCommunication()
{

}

prv2paje::PajePendingStartCommunication::PajePendingStartCommunication(double timestamp):PajePendingCommunication(timestamp)
{

}

string prv2paje::PajePendingStartCommunication::className()
{
    return "PajePendingStartCommunication";
}

void prv2paje::PajePendingStartCommunication::pushMe()
{
    poti_StartLink(timestamp, container.c_str(), type.c_str(), subContainer.c_str(), value.c_str(), key.c_str());
    LastTimestamp=timestamp;
}
