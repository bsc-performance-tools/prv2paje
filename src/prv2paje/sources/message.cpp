#include "message.h"


void prv2paje::Message::Critical(string message)
{
#ifdef MESSAGE_CRITICAL
    cerr<<"!!!Critical!!!: "<<message<<endl;
#endif
}

void prv2paje::Message::Debug(string message)
{
#ifdef MESSAGE_DEBUG
    cerr<<"Debug: "<<message<<endl;
#endif
}

void prv2paje::Message::Error(string message)
{
#ifdef MESSAGE_ERROR
    cerr<<"!!Error!!: "<<message<<endl;
#endif
}

void prv2paje::Message::Info(string message, int level)
{
#ifdef MESSAGE_INFO
    for (int i=0; i<level; i++){
        cout<<"---";
    }
    if (level!=0){
        cout<<" ";
    }
    cout<<message<<endl;
#endif
}

void prv2paje::Message::Warning(string message)
{
#ifdef MESSAGE_WARNING
    cerr<<"!Warning!: "<<message<<endl;
#endif
}
