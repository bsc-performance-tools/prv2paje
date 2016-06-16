#ifndef PAJEPENDINGEVENT_H
#define PAJEPENDINGEVENT_H

#include <string>

using namespace std;

namespace prv2paje{

    class PajePendingEvent
    {
    public:
        PajePendingEvent();
        PajePendingEvent(long int timestamp);
        friend bool operator> (const PajePendingEvent &object1, const PajePendingEvent &object2);
        friend bool operator<= (const PajePendingEvent &object1, const PajePendingEvent &object2);
        friend bool operator< (const PajePendingEvent &object1, const PajePendingEvent &object2);
        friend bool operator>= (const PajePendingEvent &object1, const PajePendingEvent &object2);
        friend bool operator== (const PajePendingEvent &object1, const PajePendingEvent &object2);
        friend bool operator!= (const PajePendingEvent &object1, const PajePendingEvent &object2);

        virtual string className() = 0;

        long getTimestamp() const;
        void setTimestamp(long value);

        string getContainer() const;
        void setContainer(const string &value);

        string getType() const;
        void setType(const string &value);

    private:
        long int timestamp;
        string container;
        string type;
    };

}

#endif // PAJEPENDINGEVENT_H
