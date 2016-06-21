#ifndef CONFIG_H
#define CONFIG_H

#ifndef __BUILD_VERSION__
#define __BUILD_VERSION__ "Unknown"
#endif

#define PRV_EXT                                     "prv"
#define PCF_EXT                                     "pcf"
#define ROW_EXT                                     "row"

#define PAJE_EXT                                    "pj"

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

#define PAJE_CONTAINER_DEF_NAME_ROOT                "ROOT"
#define PAJE_CONTAINER_DEF_NAME_NODE                "NODE"
#define PAJE_CONTAINER_DEF_NAME_CPU                 "CPU"
#define PAJE_CONTAINER_DEF_NAME_APP                 "APPLICATION"
#define PAJE_CONTAINER_DEF_NAME_TASK                "TASK"
#define PAJE_CONTAINER_DEF_NAME_THREAD              "THREAD"

#define PAJE_CONTAINER_DEF_ALIAS_ROOT               PAJE_CONTAINER_DEF_NAME_ROOT
#define PAJE_CONTAINER_DEF_ALIAS_NODE               PAJE_CONTAINER_DEF_NAME_NODE
#define PAJE_CONTAINER_DEF_ALIAS_CPU                PAJE_CONTAINER_DEF_NAME_CPU
#define PAJE_CONTAINER_DEF_ALIAS_APP                PAJE_CONTAINER_DEF_NAME_APP
#define PAJE_CONTAINER_DEF_ALIAS_TASK               PAJE_CONTAINER_DEF_NAME_TASK
#define PAJE_CONTAINER_DEF_ALIAS_THREAD             PAJE_CONTAINER_DEF_NAME_THREAD

#define PAJE_PRVSTATE_NAME                          "STATE"

#define PAJE_PRVSTATE_ALIAS                         PAJE_PRVSTATE_NAME

#define PAJE_CONTAINER_NAME_ROOT                    "root"
#define PAJE_CONTAINER_NAME_NODE_PREFIX             "node-"
#define PAJE_CONTAINER_NAME_CPU_PREFIX              "cpu-"
#define PAJE_CONTAINER_NAME_APP_PREFIX              "app-"
#define PAJE_CONTAINER_NAME_TASK_PREFIX             "task-"
#define PAJE_CONTAINER_NAME_THREAD_PREFIX           "thread-"

#define PAJE_CONTAINER_ALIAS_ROOT                   PAJE_CONTAINER_NAME_ROOT
#define PAJE_CONTAINER_ALIAS_NODE_PREFIX            PAJE_CONTAINER_NAME_NODE_PREFIX
#define PAJE_CONTAINER_ALIAS_CPU_PREFIX             PAJE_CONTAINER_NAME_CPU_PREFIX

#define PRV_TIME_UNIT_SECONDS                       "s"
#define PRV_TIME_UNIT_MILISECONDS                   "ms"
#define PRV_TIME_UNIT_MICROSECONDS                  "us"
#define PRV_TIME_UNIT_NANOSECONDS                   "ns"
#define PRV_TIME_UNIT_MINUTES                       "m"
#define PRV_TIME_UNIT_HOURS                         "h"

#define PAJE_TIME_DIVIDER_SECONDS                   1.0
#define PAJE_TIME_DIVIDER_MILISECONDS               1000.0
#define PAJE_TIME_DIVIDER_MICROSECONDS              1000000.0
#define PAJE_TIME_DIVIDER_NANOSECONDS               1000000000.0
#define PAJE_TIME_DIVIDER_MINUTES                   (1.0/60.0)
#define PAJE_TIME_DIVIDER_HOURS                     (1.0/3600.0)



#define RETURN_OK                                   0
#define RETURN_ERR_PRV                              1
#define RETURN_ERR_PCF                              2
#define RETURN_ERR_PAJE                             3

#endif // CONFIG_H
