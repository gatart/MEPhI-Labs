#ifndef TABLE_H
#define TABLE_H
#include <iostream>
#include <vector>

#include "basefile.h"
#include "typefiles.h"


class Catalog;

struct TableCell{
    std::string _id;
    bool _access;
    File* _define;
};

class Table{
private:
    std::vector<TableCell> _data;
    friend class Catalog;
    friend class Menu;

public:
    Table();
    void newFile(const std::string &ID, const TYPE &type);
    void addSpecial(const std::string &ID);
    void addCatalog(const std::string &ID);
    void addCommon(const std::string &ID);
};

#endif // TABLE_H
