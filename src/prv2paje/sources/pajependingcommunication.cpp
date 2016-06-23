#include "pajependingcommunication.h"

int prv2paje::PajePendingCommunication::id;

prv2paje::PajePendingCommunication::PajePendingCommunication()
{

}

prv2paje::PajePendingCommunication::PajePendingCommunication(double timestamp):PajePendingEvent(timestamp)
{

}

void prv2paje::PajePendingCommunication::InitializeId()
{
    prv2paje::PajePendingCommunication::id=0;
}

string prv2paje::PajePendingCommunication::GetNextKey()
{
    prv2paje::PajePendingCommunication::id++;
    return string(PAJE_COMMUNICATION_KEY_PREFIX)+to_string(prv2paje::PajePendingCommunication::id);
}

string prv2paje::PajePendingCommunication::getKey() const
{
    return key;
}

void prv2paje::PajePendingCommunication::setKey(const string &value)
{
    key = value;
}

string prv2paje::PajePendingCommunication::getSubContainer() const
{
    return subContainer;
}

void prv2paje::PajePendingCommunication::setSubContainer(const string &value)
{
    subContainer = value;
}

string prv2paje::PajePendingCommunication::getValue() const
{
    return value;
}

void prv2paje::PajePendingCommunication::setValue(string val)
{
    value = val;
}
