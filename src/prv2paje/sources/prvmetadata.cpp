#include "../headers/prvmetadata.h"

prv2paje::PrvMetaData::PrvMetaData()
{

}

string prv2paje::PrvMetaData::getFile() const
{
    return file;
}

void prv2paje::PrvMetaData::setFile(const string &value)
{
    file = value;
}

long prv2paje::PrvMetaData::getDuration() const
{
    return duration;
}

void prv2paje::PrvMetaData::setDuration(long value)
{
    duration = value;
}

string prv2paje::PrvMetaData::getTimeUnit() const
{
    return timeUnit;
}

void prv2paje::PrvMetaData::setTimeUnit(const string &value)
{
    timeUnit = value;
}

int prv2paje::PrvMetaData::getApplications() const
{
    return applications;
}

void prv2paje::PrvMetaData::setApplications(int value)
{
    applications = value;
}

int prv2paje::PrvMetaData::getNodes() const
{
    return nodes;
}

void prv2paje::PrvMetaData::setNodes(int value)
{
    nodes = value;
}

string prv2paje::PrvMetaData::getComment() const
{
    return comment;
}

void prv2paje::PrvMetaData::setComment(const string &value)
{
    comment = value;
}

vector<int> *prv2paje::PrvMetaData::getCpus() const
{
    return cpus;
}

void prv2paje::PrvMetaData::setCpus(vector<int> *value)
{
    cpus = value;
}
