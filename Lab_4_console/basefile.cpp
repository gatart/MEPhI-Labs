#include "basefile.h"


void File::chmod(int mod){
    if (mod >= 4){
        mod -= 4;
        _r = true;
    }else{
        _r = false;
    }
    if (mod >= 2){
        mod -= 2;
        _w = true;
    }else{
        _w = false;
    }
    if (mod == 1) _x = true;
    else _x = false;
}

void File::chvol(unsigned int vol){
    _volume = vol;
}


const TYPE &File::getType()const{
    return _fileType;
}

const std::string &File::getName()const{
    return _name;
}

const std::string &File::getID()const{
    return _id;
}


int File::getmod(){
    int mod = 0;
    if (_r) mod += 4;
    if (_w) mod += 2;
    if (_x) mod += 1;

    return mod;
}

unsigned int File::getvol(){
    return _volume;
}

void File::setAdress(File* adress){
    _adress = adress;
}

void File::putID(const std::string &ID){
    _id = ID;
}

File::~File(){
}
