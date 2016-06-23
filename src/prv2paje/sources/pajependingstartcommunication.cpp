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
