#include "typefiles.h"

Catalog::Catalog(const TYPE fileType)
    : File(fileType)
{

}

CommonFile::CommonFile(const TYPE fileType)
    : File(fileType)
{

}

SpecialFile::SpecialFile(const TYPE fileType, const SPECTYPE type)
    : File(fileType), _type(type)
{

}
