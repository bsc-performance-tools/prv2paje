#ifndef PAJEPENDINGEVENT_H
#define PAJEPENDINGEVENT_H

#include <string>
#include "prv2paje_config.h"
#include <poti.h>

using namespace std;

namespace prv2paje{

    class PajePendingEvent
    {
    public:
        PajePendingEvent();
        PajePendingEvent(double timestamp);
        friend bool operator> (const PajePendingEvent &object1, const PajePendingEvent &object2);
        friend bool operator<= (const PajePendingEvent &object1, const PajePendingEvent &object2);
        friend bool operator< (const PajePendingEvent &object1, const PajePendingEvent &object2);
        friend bool operator>= (const PajePendingEvent &object1, const PajePendingEvent &object2);
        friend bool operator== (const PajePendingEvent &object1, const PajePendingEvent &object2);
        friend bool operator!= (const PajePendingEvent &object1, const PajePendingEvent &object2);

        virtual string className() = 0;
        virtual void pushMe() = 0;

        double getTimestamp() const;
        void setTimestamp(double value);

        string getContainer() const;
        void setContainer(const string &value);

        string getType() const;
        void setType(const string &value);

        static double LastTimestamp;

    protected:
        double timestamp;
        string container;
        string type;
    };


}

#endif // PAJEPENDINGEVENT_H
