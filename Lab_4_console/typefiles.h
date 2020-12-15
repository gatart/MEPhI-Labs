#ifndef CATALOG_H
#define CATALOG_H
#include <map>

#include "basefile.h"

class Catalog : public File{
private:
    std::map<std::string, std::string> _dir; // map <Name, ID>
public:
    Catalog(const TYPE fileType, const std::string &ID, const std::string name);

    virtual void viewInfo();
    virtual void chmod(int mod);
    virtual void chvol(unsigned int vol);
    virtual ~Catalog();

    std::map<std::string, std::string> &getDir();
};






























class CommonFile : public File{
private:
    struct tm *_time;

public:
    CommonFile(const TYPE fileType, const std::string &ID, unsigned int volume, const std::string name);
    virtual void viewInfo();
    virtual void chmod(int mod);
    virtual void chvol(unsigned int vol);
    virtual ~CommonFile();
};


class SpecialFile : public File{
private:

public:
    SpecialFile(const TYPE fileType, const std::string &ID, unsigned int volume, const std::string name);
    virtual void viewInfo();
    virtual ~SpecialFile();
};

#endif // CATALOG_H
