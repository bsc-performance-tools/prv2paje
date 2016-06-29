#ifndef METADATAJNIWRAPPER_H
#define METADATAJNIWRAPPER_H

#include "prvmetadata.h"

using namespace prvreader;

class MetadataJNIWrapper
{
public:
    MetadataJNIWrapper();
    MetadataJNIWrapper(PrvMetaData* prvMetadata);
    void setPrvMetaData(PrvMetaData *value);

private:
    PrvMetaData* prvMetaData;
};

#endif // METADATAJNIWRAPPER_H
