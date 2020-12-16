#include <iostream>
#include "typefiles.h"
#include <time.h>


std::map<std::string, std::string> &Catalog::getDir(){
    return _dir;
}

void Catalog::chvol(unsigned int vol){
    if (vol != 0){
        throw std::system_error();
    }
}

Catalog::~Catalog(){

}


CommonFile::CommonFile(const TYPE fileType, const std::string &ID, unsigned int volume, const std::string name)
    : File(fileType, ID, volume, name)
{
    setTime();
}

void CommonFile::chmod(int mod){
    File::chmod(mod);
    setTime();
}

void CommonFile::chvol(unsigned int vol){
    File::chvol(vol);
    setTime();
}

void CommonFile::setTime(){
    _time = time(nullptr);
}

const time_t* CommonFile::getTime(){
    return &_time;
}

CommonFile::~CommonFile(){
}
