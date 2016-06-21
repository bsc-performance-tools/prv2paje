#ifndef PAJEPENDINGEVENT_H
#define PAJEPENDINGEVENT_H

#include <string>

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

        double getTimestamp() const;
        void setTimestamp(double value);

        string getContainer() const;
        void setContainer(const string &value);

        string getType() const;
        void setType(const string &value);

    private:
        double timestamp;
        string container;
        string type;
    };

}

#endif // PAJEPENDINGEVENT_H
