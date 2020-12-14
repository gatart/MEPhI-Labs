#include <iostream>
#include "typefiles.h"

Catalog::Catalog(const TYPE fileType, const std::string &ID, const std::string name)
    : File(fileType, ID, 0, name)
{

}

CommonFile::CommonFile(const TYPE fileType, const std::string &ID, unsigned int volume, const std::string name)
    : File(fileType, ID, volume, name)
{

}

SpecialFile::SpecialFile(const TYPE fileType, const std::string &ID, unsigned int volume, const std::string name)
    : File(fileType, ID, volume, name)
{

}


