#include "rgb.h"

prvreader::RGB::RGB():r(0), g(0), b(0)
{

}

int prvreader::RGB::getR() const
{
    return r;
}

void prvreader::RGB::setR(int value)
{
    if (value>=0&&value<=255){
        r = value;
    }
}

int prvreader::RGB::getG() const
{
    return g;
}

void prvreader::RGB::setG(int value)
{
    if (value>=0&&value<=255){
        g = value;
    }
}

int prvreader::RGB::getB() const
{
    return b;
}

void prvreader::RGB::setB(int value)
{
    if (value>=0&&value<=255){
        b = value;
    }
}

prvreader::RGB::RGB(int r, int g, int b)
{
    this->r=0;
    this->g=0;
    this->b=0;
    setRGB(r, g, b);
}

void prvreader::RGB::setRGB(int r, int g, int b)
{
    setR(r);
    setG(g);
    setB(b);
}

void prvreader::RGB::setRGBFromPcf(string value)
{
    this->r=0;
    this->g=0;
    this->b=0;
    string rgb=value.substr(1,rgb.size()-1);
    vector<string> tokens;
    split(tokens, rgb, is_any_of(" "));
    if (tokens.size()==3){
        setRGB(atoi(tokens[0].c_str()), atoi(tokens[1].c_str()), atoi(tokens[2].c_str()));
    }
}
