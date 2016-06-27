#include "message.h"


void prvreader::Message::Critical(string message)
{
#ifdef MESSAGE_CRITICAL
    cerr<<"!!!Critical!!!: "<<message<<endl;
#endif
}

void prvreader::Message::Debug(string message)
{
#ifdef MESSAGE_DEBUG
    cerr<<"Debug: "<<message<<endl;
#endif
}

void prvreader::Message::Error(string message)
{
#ifdef MESSAGE_ERROR
    cerr<<"!!Error!!: "<<message<<endl;
#endif
}

void prvreader::Message::Info(string message, int level)
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

void prvreader::Message::Warning(string message)
{
#ifdef MESSAGE_WARNING
    cerr<<"!Warning!: "<<message<<endl;
#endif
}
