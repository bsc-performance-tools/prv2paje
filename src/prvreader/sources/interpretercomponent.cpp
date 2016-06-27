#include "interpretercomponent.h"

prvreader::PrvMetaData *prvreader::InterpreterComponent::getPrvMetaData() const
{
    return prvMetaData;
}

void prvreader::InterpreterComponent::setPrvMetaData(PrvMetaData *value)
{
    prvMetaData = value;
}

prvreader::PcfParser *prvreader::InterpreterComponent::getPcfParser() const
{
    return pcfParser;
}

void prvreader::InterpreterComponent::setPcfParser(PcfParser *value)
{
    pcfParser = value;
}
