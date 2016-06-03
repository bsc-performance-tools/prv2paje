#include "stringutils.h"

StringUtils::StringUtils()
{

}

vector<string> prv2paje::StringUtils::split(string value, string delimiter)
{
    string valueCopy=value;
    string::size_type stTemp = valueCopy.find(delimiter);
    vector<string> tokens();
    while(stTemp != string::npos)
    {
        tokens.push_back(valueCopy.substr(0, stTemp));
        valueCopy = valueCopy.substr(stTemp + 1);
        stTemp = valueCopy.find(delimiter);
    }
    tokens.push_back(valueCopy);
    return tokens;
}
