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
        string getValue() const;
        void setValue(string value);
        static int id;

    private:
        string key;
        string subContainer;
        string value;
    };

}



#endif // PAJEPENDINGCOMMUNICATION_H
