#ifndef METADATAJNIWRAPPER_H
#define METADATAJNIWRAPPER_H

#include <prvmetadata.h>

using namespace prvreader;

class MetaDataJNIWrapper
{
public:
    MetaDataJNIWrapper();
    MetaDataJNIWrapper(PrvMetaData* prvMetaData);
    void setPrvMetaData(PrvMetaData *value);

private:
    PrvMetaData* prvMetaData;

};

#endif // METADATAJNIWRAPPER_H
