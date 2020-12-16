#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <vector>
#include <map>
#include <limits>

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
        cin >>a;
        fl = false;
        if (cin.fail()){
            cin.clear();
            cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
            fl = true;
        }else{
            cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        }
    }while(fl);
    return a;
}

class Menu
{
private:
   std::map<string, File*> _table;
   std::map<string, string> _root;
   static std::string _ID;

   void (Menu::*functionMass[6])() = {&Menu::addFile, &Menu::chmod,
           &Menu::chvol, &Menu::delFile, &Menu::viewInfo, &Menu::exit};

   string setName();
   TYPE setType();
   unsigned int setVol();
   std::map<string, string> &getWay();

   string generateID();
   void nextID(std::string &ID);
   void defragment();
   bool findName(const string &name, std::map<string,string> &table);

   void delDir(string id);
   unsigned int getDirVol(string id);

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

#endif // MENU_H
