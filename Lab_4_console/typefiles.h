#ifndef CATALOG_H
#define CATALOG_H
#include <map>


#include "basefile.h"


class Catalog : public File{
private:
    std::map<std::string, std::string> _dir; // map <Name, ID>
public:
    Catalog(const TYPE fileType, const std::string &ID, const std::string name)
        : File(fileType, ID, 0, name){}
    ~Catalog();

    virtual void chvol(unsigned int vol);
    std::map<std::string, std::string> &getDir();
};



class CommonFile : public File{
private:
    time_t _time;

public:
    CommonFile(const TYPE fileType, const std::string &ID, unsigned int volume, const std::string name);
    virtual void chmod(int mod);
    virtual void chvol(unsigned int vol);
    virtual ~CommonFile();

    void setTime();
    const time_t* getTime();
};


#endif // CATALOG_H
