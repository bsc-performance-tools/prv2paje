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


#ifndef ARGUMENTMANAGER_H
#define ARGUMENTMANAGER_H

#include <string>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "prv2paje_config.h"
#include <message.h>

#define ARGUMENT(n, flag, wholeflag) ((n.compare(flag)==0)||(n.compare(wholeflag)==0))

using namespace std;
using namespace prvreader;

namespace prv2paje{

    class ArgumentManager
    {
    public:
        ArgumentManager(int argc, char** argv);
        void usage();

        bool getValid() const;

        string getMe() const;

        string getPrvPath() const;

        string getPajePath() const;

        string getFilterPath() const;

        bool getBasic() const;

        bool getOld() const;

        bool getFast() const;

        void setFast(bool value);

    private:
        bool valid;
        bool basic;
        bool old;
        bool fast;
        bool filter;
        string me;
        string prvPath;
        string pajePath;
        string filterPath;
    };

}

#endif // ARGUMENTMANAGER_H
