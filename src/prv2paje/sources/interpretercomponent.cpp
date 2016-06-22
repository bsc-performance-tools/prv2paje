#include "interpretercomponent.h"

prv2paje::PrvMetaData *prv2paje::InterpreterComponent::getPrvMetaData() const
{
    return prvMetaData;
}

void prv2paje::InterpreterComponent::setPrvMetaData(PrvMetaData *value)
{
    prvMetaData = value;
}

prv2paje::PcfParser *prv2paje::InterpreterComponent::getPcfParser() const
{
    return pcfParser;
}

void prv2paje::InterpreterComponent::setPcfParser(PcfParser *value)
{
    pcfParser = value;
}
