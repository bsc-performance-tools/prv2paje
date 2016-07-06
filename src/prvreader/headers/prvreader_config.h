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

#ifndef PRVREADER_CONFIG_H
#define PRVREADER_CONFIG_H

#ifndef __BUILD_VERSION__
#define __BUILD_VERSION__ "Unknown"
#endif

#define MESSAGE_INFO

#define PRV_EXT                                     "prv"
#define PCF_EXT                                     "pcf"
#define ROW_EXT                                     "row"

#define PCF_STATES                                  "STATES"
#define PCF_STATES_COLOR                            "STATES_COLOR"
#define PCF_EVENT_TYPE                              "EVENT_TYPE"
#define PCF_VALUES                                  "VALUES"
#define PCF_GRADIENT_COLOR                          "GRADIENT_COLOR"
#define PCF_GRADIENT_NAMES                          "GRADIENT_NAMES"

#define PRV_HEADER_SEP_MAIN_CHAR                    ':'

#define PRV_HEADER_QUOTE_IN_CHAR                    '('
#define PRV_HEADER_QUOTE_OUT_CHAR                   ')'

#define GENERIC_QUOTE_CHAR                          '\"'

#define GENERIC_QUOTE                               "\""

#define GENERIC_ESCAPE_CHAR                         '\\'

#define GENERIC_SEP                                 ";"

#define GENERIC_SEP_CHAR                            ';'

#define PRV_HEADER_FIELD_COMMENT                    0
#define PRV_HEADER_FIELD_DURATION                   1
#define PRV_HEADER_SUBFIELD_DURATION_VALUE          0
#define PRV_HEADER_SUBFIELD_DURATION_UNIT           1
#define PRV_HEADER_SEP_DURATION                     "_"
#define PRV_HEADER_FIELD_HW                         2
#define PRV_HEADER_SUBFIELD_HW_NODES                0
#define PRV_HEADER_SUBFIELD_HW_CPUS                 1
#define PRV_HEADER_SEP_HW_CPUS                      ","

#define PRV_BODY_COMMUNICATOR                       "c"
#define PRV_BODY_STATE                              "1"
#define PRV_BODY_EVENTS                             "2"
#define PRV_BODY_COMMUNICATION                      "3"

#define PRV_BODY_FIELD_EVENTTYPE                    0
#define PRV_BODY_FIELD_CPU                          1
#define PRV_BODY_FIELD_APP                          2
#define PRV_BODY_FIELD_TASK                         3
#define PRV_BODY_FIELD_THREAD                       4

#define PRV_BODY_FIELD_EVENTS_TIMESTAMP             5

#define PRV_BODY_FIELD_STATE_STARTTIMESTAMP         5
#define PRV_BODY_FIELD_STATE_ENDTIMESTAMP           6
#define PRV_BODY_FIELD_STATE_TYPE                   7

#define PCF_EVENT_STATE_VALUE_END_STRING           "0"
#define PCF_EVENT_STATE_VALUE_END                   atoi(PCF_EVENT_STATE_VALUE_END_STRING)

#define PRV_TIME_UNIT_SECONDS                       "s"
#define PRV_TIME_UNIT_MILISECONDS                   "ms"
#define PRV_TIME_UNIT_MICROSECONDS                  "us"
#define PRV_TIME_UNIT_NANOSECONDS                   "ns"
#define PRV_TIME_UNIT_MINUTES                       "m"
#define PRV_TIME_UNIT_HOURS                         "h"

#define RETURN_OK                                   0
#define RETURN_ERR_PRV                              1
#define RETURN_ERR_PCF                              2
#define RETURN_ERR_PAJE                             3

#endif // PRVREADER_CONFIG_H
