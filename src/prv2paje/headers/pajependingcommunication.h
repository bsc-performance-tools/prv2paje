#ifndef PAJEPENDINGCOMMUNICATION_H
#define PAJEPENDINGCOMMUNICATION_H


#include <string>
#include "pajependingevent.h"

using namespace std;

namespace prv2paje{

    class PajePendingCommunication: public PajePendingEvent
    {
    public:
        PajePendingCommunication();
        PajePendingCommunication(double timestamp);
        static void InitializeId();
        static string GetNextKey();
        string getKey() const;
        void setKey(const string &value);
        string getSubContainer() const;
        void setSubContainer(const string &value);
        long long getValue() const;
        void setValue(long long value);

    private:
        static int id;
        string key;
        string subContainer;
        long long value;
    };

}

#endif // PAJEPENDINGCOMMUNICATION_H
