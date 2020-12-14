#ifndef FILE_H
#define FILE_H
#include <iostream>
#include <array>
#include <time.h>

//#include "table.h"

enum class TYPE{
    COMMON,
    CATALOG,
    BYTE,
    BLOCK
};

class File {
private:
    File* _adress;

    bool _r;
    bool _w;
    bool _x;

    unsigned int _volume;
    const TYPE _fileType;
    const std::string _id;

public:
    File(const TYPE fileType, const std::string &ID, unsigned int volume)
        : _r(true), _w(true), _x(false),_volume(volume), _fileType(fileType), _id(ID){}

    virtual void viewInfo() = 0;
    virtual void chmod(int mod);
    virtual void chvol(unsigned int vol);
    virtual ~File();

    const TYPE &getType();
    int getmod();
    unsigned int getvol();
    void setAdress(File* adress);
};



#endif // FILE_H
