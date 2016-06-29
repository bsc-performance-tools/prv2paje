#include "prvother.h"


prvreader::PrvOther::PrvOther():PrvEvent()
{

}

prvreader::PrvOther::PrvOther(long lineNumber):PrvEvent(lineNumber)
{

}

prvreader::PrvOther::PrvOther(long linenumber, prveventtype::PrvEventType type):PrvEvent(linenumber)
{
    this->type=type;
}

prvreader::PrvOther::~PrvOther()
{

}
