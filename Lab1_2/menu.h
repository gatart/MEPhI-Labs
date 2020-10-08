#ifndef MENU_H
#define MENU_H
#include "catenary.h"
#include <iostream>

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
   double A;
   Catenary catenary;
   void (Menu::*functionMass[7])() = {&Menu::changeParm, &Menu::getY,
           &Menu::getLength, &Menu::getR, &Menu::getOr, &Menu::getS, &Menu::exit};
public:
   Menu();
   void startMenu();
   void mainMenu();
   void changeParm();
   void getY();
   void getLength();
   void getR();
   void getOr();
   void getS();
   void exit();
   void getParam(double & a);
};

#endif // MENU_H
