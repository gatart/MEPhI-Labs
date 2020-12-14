#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <vector>
#include <map>

#include "typefiles.h"
#include "maintable.h"

using std::istream;
using std::cout;
using std::cin;

template <class T>
void getNum(T & a){
    cin.exceptions(istream::failbit | istream::badbit);
    cin >>a;
}

class Menu
{
private:
   std::map<std::string, File*> _table;
   std::map<std::string, std::string> _root;

   void (Menu::*functionMass[6])() = {&Menu::addFile, &Menu::chmod,
           &Menu::chvol, &Menu::delFile, &Menu::viewInfo, &Menu::exit};

   std::string getName();
   TYPE getType();

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
