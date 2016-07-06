/*****************************************************************************\
 *                        ANALYSIS PERFORMANCE TOOLS                         *
 *                                 prvreader                                 *
 *      Libraries and Tools for reading and converting Paraver traces        *
 *****************************************************************************
 *     ___     This library is free software; you can redistribute it and/or *
 *    /  __         modify it under the terms of the GNU LGPL as published   *
 *   /  /  _____    by the Free Software Foundation; either version 3        *
 *  /  /  /     \   of the License, or (at your option) any later version.   *
 * (  (  ( B S C )                                                           *
 *  \  \  \_____/   This library is distributed in hope that it will be      *
 *   \  \__         useful but WITHOUT ANY WARRANTY; without even the        *
 *    \___          implied warranty of MERCHANTABILITY or FITNESS FOR A     *
 *                  PARTICULAR PURPOSE. See the GNU LGPL for more details.   *
 *                                                                           *
 * You should have received a copy of the GNU Lesser General Public License  *
 * along with this library; if not, write to the Free Software Foundation,   *
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA          *
 * The GNU LEsser General Public License is contained in the file COPYING.   *
 *                                 ---------                                 *
 *   Barcelona Supercomputing Center - Centro Nacional de Supercomputacion   *
\*****************************************************************************/

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
