#ifndef PRVCONTAINER_H
#define PRVCONTAINER_H

#include <string>

using namespace std;

namespace prv2paje{

    class PrvContainer
    {
    public:
        PrvContainer();
        static void initPrvContainer();
    private:
        string name;
        int id;
        long int timestamp;
        static int counter;
        int index;
    };

}

#endif // PRVCONTAINER_H
