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

#include "paraverfilemanager.h"

prvreader::ParaverFileManager::ParaverFileManager(string prvPath)
{
    prvValid=false;
    pcfValid=false;
    rowValid=false;
    this->prvPath=prvPath;
    prvStream=new ifstream();
    pcfStream=new ifstream();
    rowStream=new ifstream();
    if (string(this->prvPath.end()-3,this->prvPath.end()).compare(PRV_EXT)==0){
        prvStream->open(prvPath.c_str());
        if (!prvStream->is_open()){
            prvValid=false;
            pcfValid=false;
            rowValid=false;
        }
        else{
            prvValid=true;
            string prvExt=string(PRV_EXT);
            pcfPath=prvPath;
            string ext=string(PCF_EXT);
            pcfPath.replace(prvPath.size()-prvExt.size(), ext.size(), ext);
            rowPath=prvPath;
            ext=string(ROW_EXT);
            rowPath.replace(prvPath.size()-prvExt.size(), ext.size(), ext);
            pcfStream->open(pcfPath.c_str());
            if (pcfStream->is_open()){
                pcfValid=true;
            }else{
                pcfValid=false;
            }
            rowStream->open(rowPath.c_str());
            if (rowStream->is_open()){
                rowValid=true;
            }else{
                rowValid=false;
            }
        }
    }
}

prvreader::ParaverFileManager::~ParaverFileManager()
{
    if (prvValid){
        prvStream->close();
    }
    if (pcfStream){
        pcfStream->close();
    }
    if (rowStream){
        rowStream->close();
    }
    delete prvStream;
    delete pcfStream;
    delete rowStream;
}

string prvreader::ParaverFileManager::getRowPath() const
{
    return rowPath;
}

string prvreader::ParaverFileManager::getPcfPath() const
{
    return pcfPath;
}

string prvreader::ParaverFileManager::getPrvPath() const
{
    return prvPath;
}

ifstream* prvreader::ParaverFileManager::getRowStream() const
{
    return rowStream;
}

ifstream* prvreader::ParaverFileManager::getPcfStream() const
{
    return pcfStream;
}
ifstream* prvreader::ParaverFileManager::getPrvStream() const
{
    return prvStream;
}

bool prvreader::ParaverFileManager::getRowValid() const
{
    return rowValid;
}

bool prvreader::ParaverFileManager::getPcfValid() const
{
    return pcfValid;
}

bool prvreader::ParaverFileManager::getPrvValid() const
{
    return prvValid;
}
