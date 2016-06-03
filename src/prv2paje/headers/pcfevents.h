#ifndef PCFEVENTS_H
#define PCFEVENTS_H

#include <string>
#include <map>
#include <pcfvalue.h>

using namespace std;

namespace prv2paje{

    enum PcfEventType{Event, State, Variable, Communication, Undefined};

    class PcfEvents
    {
    public:
        PcfEvents();
        PcfEvents(int gradient, int type);
        PcfEvents(int gradient, int type, string label);
        int getGradient() const;
        void setGradient(int value);

        int getType() const;
        void setType(int value);

        string getLabel() const;
        void setLabel(const string &value);

        PcfEventType getEventType() const;
        void setEventType(const PcfEventType &value);

        map<int, PcfValue> *getValues() const;
        void setValues(map<int, PcfValue> *value);

    private:
        int gradient;
        int type;
        string label;
        PcfEventType eventType;
        map<int, PcfValue>* values;
    };

}

#endif // PCFEVENT_H
