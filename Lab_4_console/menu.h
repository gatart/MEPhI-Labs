#ifndef MENU_H
#define MENU_H
#include <iostream>

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
   Table _root;
   void (Menu::*functionMass[6])() = {&Menu::addFile, &Menu::chmod,
           &Menu::chvol, &Menu::delFile, &Menu::viewInfo, &Menu::exit};

   std::string getID();
   TYPE getType();
   void addSpecial(const std::string &ID, Table &root);
   void delSpecial(const std::string &ID, Table &root);


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
