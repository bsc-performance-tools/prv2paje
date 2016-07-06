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

#include "argumentmanager.h"

prv2paje::ArgumentManager::ArgumentManager(int argc, char **argv):valid(true), basic(false), old(false), fast(true), prvPath(""), pajePath(""), filterPath("")
{
    if (argc<2){
        valid=false;
        me=string(argv[0]);
    }else{
        me=string(argv[0]);
        for (int i=1; i<argc; i++){
            string str=string(argv[i]);
            //Message::Info("Argument: "+str);
            if (ARGUMENT(str, "--basic-header", "--basic-header")){
                basic=true;
                Message::Info("Basic header enabled");
            }else if (ARGUMENT(str, "--old-header", "--old-header")){
                old=true;
                Message::Info("Old header enabled");
            }else if (ARGUMENT(str, "-s", "--strict")){
                fast=false;
                Message::Info("Strict mode enabled");
            }else if (ARGUMENT(str, "-o", "--output")){
                pajePath=string(argv[++i]);
                Message::Info("Output: "+pajePath);
            }else if (ARGUMENT(str, "-f", "--filter")){
                filterPath=string(argv[++i]);
                Message::Info("Filter configuration file: "+filterPath);
            }else{
                prvPath=str;
                Message::Info("Input: "+prvPath);
            }
        }
    }
    if (prvPath.compare("")==0){
        valid=false;
    }
}

void prv2paje::ArgumentManager::usage()
{
    Message::Info("Usage");
    Message::Info(string(me.c_str())+" [input-trace].prv");
    Message::Info("Options:");
    Message::Info("\t -o --output [output-trace]: output Pajé trace");
    Message::Info("\t -f --filter [filter-file]: filtering configuration file");
    Message::Info("\t --old-header: old Pajé header");
    Message::Info("\t --basic-header: basic Pajé header");
    Message::Info("\t -s --strict: check more strictly the trace integrity (increases computation duration and memory consumption)");
}

string prv2paje::ArgumentManager::getPajePath() const
{
    return pajePath;
}

bool prv2paje::ArgumentManager::getOld() const
{
    return old;
}

bool prv2paje::ArgumentManager::getFast() const
{
    return fast;
}

void prv2paje::ArgumentManager::setFast(bool value)
{
    fast = value;
}

string prv2paje::ArgumentManager::getFilterPath() const
{
    return filterPath;
}

bool prv2paje::ArgumentManager::getBasic() const
{
    return basic;
}

string prv2paje::ArgumentManager::getPrvPath() const
{
    return prvPath;
}

string prv2paje::ArgumentManager::getMe() const
{
    return me;
}

bool prv2paje::ArgumentManager::getValid() const
{
    return valid;
}
