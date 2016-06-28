#ifndef PCFEVENTS_H
#define PCFEVENTS_H

#include <string>
#include <map>
#include <pcfvalue.h>

using namespace std;

namespace pcfeventtype{

enum PcfEventType{Event, State, Variable, Communication, Undefined};

}

namespace prvreader{

    class PcfEvents
    {
    public:
        PcfEvents(int gradient, int type);
        PcfEvents(int gradient, int type, string label);
        int getGradient() const;
        void setGradient(int value);

        int getType() const;
        void setType(int value);

        string getLabel() const;
        void setLabel(const string &value);

        pcfeventtype::PcfEventType getEventType() const;
        void setEventType(const pcfeventtype::PcfEventType &value);

        map<int, PcfValue*> *getValues() const;
        void setValues(map<int, PcfValue*> *value);

    private:
        int gradient;
        int type;
        string label;
        pcfeventtype::PcfEventType eventType;
        map<int, PcfValue*>* values;
    };

}

#endif // PCFEVENT_H
