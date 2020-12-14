#ifndef CATALOG_H
#define CATALOG_H

#include "basefile.h"
#include "maintable.h"

class Catalog : private File{
private:
    Table _struct;
public:
    Catalog(const TYPE fileType);
    virtual void viewInfo();
    virtual ~Catalog();
};


class CommonFile : private File{
private:
    struct tm *crtTime;
    struct tm *modTime;

public:
    CommonFile(const TYPE fileType);
    virtual void viewInfo();
    virtual void chmod();
    virtual void chvol();
    virtual ~CommonFile();
};

enum class SPECTYPE{
    BYTE,
    BLOCK
};

class SpecialFile : private File{
private:
    const SPECTYPE _type;
public:
    SpecialFile(const TYPE fileType, const SPECTYPE type);
    virtual void viewInfo();
    virtual ~SpecialFile();
};

#endif // CATALOG_H
