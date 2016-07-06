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

#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <fstream>
#include <string>
#include "prvreader_config.h"


#ifdef MESSAGE_DEBUG
#define MESSAGE_INFO
#endif

#ifdef MESSAGE_INFO
#define MESSAGE_WARNING
#endif

#ifdef MESSAGE_WARNING
#define MESSAGE_ERROR
#endif

#ifdef MESSAGE_ERROR
#define MESSAGE_CRITICAL
#endif

using namespace std;

namespace prvreader{

    class Message
    {
    public:
        static void Critical(string message);
        static void Debug(string message);
        static void Error(string message);
        static void Info(string message, int level=0);
        static void Warning(string message);
    };

}

#endif // MESSAGE_H
