#ifndef TABLE_H
#define TABLE_H
#include <iostream>
#include <vector>
#include <map>

#include "typefiles.h"


struct TableCell{
    std::string _id;
    bool _access;
    File* _define;
};

class Table{
private:
    std::map<std::string, File*> _table;
    std::map<std::string, std::string> _root;

public:
    Table();
    void newFile(const std::string &ID, const TYPE &type);
    void addSpecial(const std::string &ID);
    void addCatalog(const std::string &ID);
    void addCommon(const std::string &ID);
};

#endif // TABLE_H
