#ifndef RGB_H
#define RGB_H

#include <string>
#include <stdlib.h>

#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost::algorithm;

namespace prvreader{

    class RGB
    {
    public:
        RGB();
        RGB(int r, int g, int b);

        int getR() const;
        void setR(int value);

        int getG() const;
        void setG(int value);

        int getB() const;
        void setB(int value);

        void setRGB(int r, int g, int b);
        void setRGBFromPcf(string value);

    private:
        int r;
        int g;
        int b;
    };

}

#endif // RGB_H
