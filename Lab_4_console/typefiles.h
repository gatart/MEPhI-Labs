#ifndef CATALOG_H
#define CATALOG_H

#include "basefile.h"
//#include "maintable.h"

class Catalog : public File{
private:
    //Table _struct;
public:
    Catalog(const TYPE fileType, const std::string &ID);

    virtual void viewInfo();
    virtual void chmod(int mod);
    virtual void chvol(unsigned int vol);
    virtual ~Catalog();



    //void addCatalog(const std::string &ID, Table &table);
    void delCatalog(const std::string &ID);

};






























class CommonFile : public File{
private:
    struct tm *crtTime;
    struct tm *modTime;

public:
    CommonFile(const TYPE fileType, const std::string &ID, unsigned int volume);
    virtual void viewInfo();
    virtual void chmod(int mod);
    virtual void chvol(unsigned int vol);
    virtual ~CommonFile();
};


class SpecialFile : public File{
private:

public:
    SpecialFile(const TYPE fileType, const std::string &ID, unsigned int volume);
    virtual void viewInfo();
    virtual ~SpecialFile();
};

#endif // CATALOG_H
