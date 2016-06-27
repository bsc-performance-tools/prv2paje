#include "prvmetadata.h"

prvreader::PrvMetaData::PrvMetaData():timeDivider(1.0)
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

double prvreader::PrvMetaData::getStandardDuration() const
{
    return double (duration)/timeDivider;
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
    if (timeUnit.compare(PRV_TIME_UNIT_SECONDS)==0){
        timeDivider=TIME_DIVIDER_SECONDS;
    }else if (timeUnit.compare(PRV_TIME_UNIT_MILISECONDS)==0){
        timeDivider=TIME_DIVIDER_MILISECONDS;
    }else if (timeUnit.compare(PRV_TIME_UNIT_MICROSECONDS)==0){
        timeDivider=TIME_DIVIDER_MICROSECONDS;
    }else if (timeUnit.compare(PRV_TIME_UNIT_NANOSECONDS)==0){
        timeDivider=TIME_DIVIDER_NANOSECONDS;
    }
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

double prvreader::PrvMetaData::getTimeDivider() const
{
    return timeDivider;
}
