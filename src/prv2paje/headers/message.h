#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <fstream>
#include <string>

#define MESSAGE_INFO

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

namespace prv2paje{

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
