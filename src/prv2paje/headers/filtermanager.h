#ifndef FILTERMANAGER_H
#define FILTERMANAGER_H

namespace prv2paje{

    class FilterManager
    {
    public:
        FilterManager();
    private:
        bool enabled;
        bool disableStates;
        bool disableEvents;
        bool disableCommunications;
        bool filterTypes;
        list<string> types;
    };

}

#endif // FILTERMANAGER_H
