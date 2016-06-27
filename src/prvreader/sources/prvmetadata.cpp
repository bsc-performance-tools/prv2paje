#include "prvmetadata.h"

prvreader::PrvMetaData::PrvMetaData()
{

}

string prvreader::PrvMetaData::getFile() const
{
    return file;
}

void prvreader::PrvMetaData::setFile(const string &value)
{
    file = value;
}

long prvreader::PrvMetaData::getDuration() const
{
    return duration;
}

void prvreader::PrvMetaData::setDuration(long value)
{
    duration = value;
}

string prvreader::PrvMetaData::getTimeUnit() const
{
    return timeUnit;
}

void prvreader::PrvMetaData::setTimeUnit(const string &value)
{
    timeUnit = value;
}

int prvreader::PrvMetaData::getApplications() const
{
    return applications;
}

void prvreader::PrvMetaData::setApplications(int value)
{
    applications = value;
}

int prvreader::PrvMetaData::getNodes() const
{
    return nodes;
}

void prvreader::PrvMetaData::setNodes(int value)
{
    nodes = value;
}

string prvreader::PrvMetaData::getComment() const
{
    return comment;
}

void prvreader::PrvMetaData::setComment(const string &value)
{
    comment = value;
}

vector<int> *prvreader::PrvMetaData::getCpus() const
{
    return cpus;
}

void prvreader::PrvMetaData::setCpus(vector<int> *value)
{
    cpus = value;
}
