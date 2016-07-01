#ifndef PRVFILTER_H
#define PRVFILTER_H

#include <map>
#include <string>

using namespace std;

namespace prvreader{

    class PrvFilter
    {
    public:
        PrvFilter();
        bool getEnabled() const;
        void setEnabled(bool value);

        bool getDisableStates() const;
        void setDisableStates(bool value);

        bool getDisableEvents() const;
        void setDisableEvents(bool value);

        bool getDisableCommunications() const;
        void setDisableCommunications(bool value);

        bool getDisableFilterTypes() const;
        void setDisableFilterTypes(bool value);

        void addUnfilteredType(string type);
        bool isFiltered(string type);

        void addUnfilteredType(int type);
        bool isFiltered(int type);

    private:
        bool enabled;
        bool disableStates;
        bool disableEvents;
        bool disableCommunications;
        bool disableFilterTypes;
        map<int, bool> unfilteredTypes;
    };

}

#endif // PRVFILTER_H
