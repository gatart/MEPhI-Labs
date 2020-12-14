#include "typefiles.h"

Catalog::Catalog(const TYPE fileType, const std::string &ID)
    : File(fileType, ID, 0)
{

}

CommonFile::CommonFile(const TYPE fileType, const std::string &ID, unsigned int volume)
    : File(fileType, ID, volume)
{

}

SpecialFile::SpecialFile(const TYPE fileType, const std::string &ID, unsigned int volume)
    : File(fileType, ID, volume)
{

}
