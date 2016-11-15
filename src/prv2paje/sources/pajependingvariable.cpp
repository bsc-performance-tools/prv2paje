#include "pajependingvariable.h"

prv2paje::PajePendingVariable::PajePendingVariable()
{

}

prv2paje::PajePendingVariable::PajePendingVariable(double timestamp):PajePendingEvent(timestamp)
{

}

string prv2paje::PajePendingVariable::className()
{
    return "PajePendingVariable";
}

void prv2paje::PajePendingVariable::pushMe()
{
    poti_SetVariable (timestamp, container.c_str(), type.c_str(), value);
    PajePendingEvent::LastTimestamp=timestamp;
}

long long prv2paje::PajePendingVariable::getValue() const
{
    return value;
}

void prv2paje::PajePendingVariable::setValue(long long val)
{
    value = val;
}
