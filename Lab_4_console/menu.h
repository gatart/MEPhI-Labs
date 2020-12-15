#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <vector>
#include <map>

#include "typefiles.h"

using std::istream;
using std::cout;
using std::cin;
using std::string;

template <class T>
T getSome(const string &str){
    bool fl = false;
    T a;
    do{
        cout <<str;
        try {
            cin >>a;
        } catch (...) {
            fl = true;
        }
    }while(fl);
    return a;
}

class Menu
{
private:
   std::map<string, File*> _table;
   std::map<string, string> _root;
   static std::string _id;

   void (Menu::*functionMass[6])() = {&Menu::addFile, &Menu::chmod,
           &Menu::chvol, &Menu::delFile, &Menu::viewInfo, &Menu::exit};

   string getName();
   TYPE getType();
   unsigned int getVol();
   int getNum();
   std::map<string, string> &getWay();

   string generateID();
   void nextID(std::string &ID);
   void defragment();
   bool findName(const string &name, std::map<string,string> &table);

public:
   Menu();
   void mainMenu();

   void addFile();
   void chmod();
   void chvol();
   void delFile();
   void viewInfo();

   void exit();
};

string Menu::_id = "aaaaaaaaaaaaaaaaaaaaaaaa"; //a - 24

#endif // MENU_H
