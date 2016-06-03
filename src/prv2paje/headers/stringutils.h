#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <vector>
#include <string>

using namespace std;

namespace prv2paje{

    class StringUtils
    {
    public:
        StringUtils();
        static vector<string> split(string value, string delimiter);
    };

}

#endif // STRINGUTILS_H
