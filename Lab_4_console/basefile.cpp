#include "basefile.h"


void File::chmod(int mod){
    if (mod >= 4){
        mod -= 4;
        _r = true;
    }
    if (mod >= 2){
        mod -= 2;
        _w = true;}
    if (mod == 1) _x = true;
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

File::~File(){
}
