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
