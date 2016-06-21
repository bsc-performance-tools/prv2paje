#include "message.h"


void prv2paje::Message::Critical(string message)
{
    cerr<<"!!!Critical!!!: "<<message<<endl;
}

void prv2paje::Message::Debug(string message)
{
    cerr<<"Debug: "<<message<<endl;
}

void prv2paje::Message::Error(string message)
{
    cerr<<"!!Error!!: "<<message<<endl;
}

void prv2paje::Message::Info(string message, int level)
{
    for (int i=0; i<level; i++){
        cout<<"---";
    }
    cout<<" ";
    cout<<message<<endl;
}

void prv2paje::Message::Warning(string message)
{
    cerr<<"!Warning!: "<<message<<endl;
}
