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

#include "pajefilemanager.h"


prv2paje::PajeFileManager::PajeFileManager(string pajePath):pajePath(pajePath)
{
    pajeValid=false;
    pajeStream=new ofstream();
    pajeStream->open(pajePath.c_str());
    if (pajeStream->is_open()){
        pajeValid=true;
    }
}

prv2paje::PajeFileManager::~PajeFileManager()
{
    if (pajeValid){
        pajeStream->close();
    }
    delete pajeStream;
}

bool prv2paje::PajeFileManager::getPajeValid() const
{
    return pajeValid;
}

string prv2paje::PajeFileManager::getPajePath() const
{
    return pajePath;
}

string prv2paje::PajeFileManager::PajeNameFromPrv(string prvPath)
{
    string pajePath;
    string prvExt=string(PRV_EXT);
    pajePath=prvPath;
    string ext=string(PAJE_EXT);
    pajePath.replace(prvPath.size()-prvExt.size(), ext.size(), ext);
    return pajePath;
}
