#include "rgb.h"

prv2paje::RGB::RGB():r(0), g(0), b(0)
{

}

int RGB::getR() const
{
    return r;
}

void RGB::setR(int value)
{
    if (value>=0&&value<=255){
        r = value;
    }
}

int RGB::getG() const
{
    return g;
}

void RGB::setG(int value)
{
    if (value>=0&&value<=255){
        g = value;
    }
}

int RGB::getB() const
{
    return b;
}

void RGB::setB(int value)
{
    if (value>=0&&value<=255){
        b = value;
    }
}

prv2paje::RGB::RGB(int r, int g, int b)
{
    this->r=0;
    this->g=0;
    this->b=0;
    setRGB(r, g, b);
}

void prv2paje::RGB::setRGB(int r, int g, int b)
{
    setR(r);
    setG(g);
    setB(b);
}

void prv2paje::RGB::setRGBFromPcf(string value)
{
    this->r=0;
    this->g=0;
    this->b=0;
    string rgb=value.substr(1,rgb.size()-1);
    vector<string> tokens=StringUtils.split(value, ",");
    if (tokens.size()==3){
        setRGB(Integer.parseInt(tokens[0]), Integer.parseInt(tokens[1]), Integer.parseInt(tokens[2]));
    }
}
