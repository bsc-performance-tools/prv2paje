#include "metadatajniwrapper.h"

MetaDataJNIWrapper::MetaDataJNIWrapper()
{

}

MetaDataJNIWrapper::MetaDataJNIWrapper(PrvMetaData *prvMetaData):prvMetaData(prvMetaData)
{

}

void MetaDataJNIWrapper::setPrvMetaData(PrvMetaData *value)
{
    prvMetaData = value;
}
