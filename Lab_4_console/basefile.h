#ifndef FILE_H
#define FILE_H
#include <iostream>
#include <array>
#include <time.h>

//#include "table.h"

enum class TYPE{
    COMMON,
    CATALOG,
    SPECIAL
};

class File {
private:
    File* _adress;

    bool _r;
    bool _w;
    bool _x;

    unsigned int _volume;
    std::string _name;
    const TYPE _fileType;
    //const std::string _id;
    //static std::array<char> ID; реши, как хранить ID

public:
    File(const TYPE fileType);
    virtual void viewInfo();
    const TYPE &getType();
    virtual void chmod();
    virtual void chvol();
    virtual ~File();
};



#endif // FILE_H
