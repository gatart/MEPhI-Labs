#include <iostream>
#include "menu.h"
#include <conio.h>

using std::endl;

Menu::Menu(){
    A = 1;
}

void Menu::getParam(long double & a){
    do{
        cout <<"Enter A: ";
        getNum(a);
    }while(a <= 0);
}

void Menu::startMenu(){
    int ans;
    cout <<"Welcome to a Catenary Modeling Programm!"<<endl
        <<"Enter parameters or use default?"<<endl
        <<"(1 - enter parameters, 0 - default)"<<endl<<">>>";
    getNum(ans);
    while (ans != 1 && ans != 0){
        cout <<"Oops, you entered not possible answer. Try again!"<<endl<<">>>";
        getNum(ans);
    }
    if (ans == 0){ //Default
       // Catenary catenary;
    }else{ //Users params
        getParam(A);
        catenary.setParam(A);
        //Catenary catenary(A); //why don't work? (Because Catenary() invoked earlier in Menu() ???)
    }
}

void Menu::mainMenu(){
    int ret;
    do{
        do{
            system("cls");
            cout <<"A = "<<A<<endl
                 <<"Menu:"<<endl
                 <<"[0] Change parameter"<<endl
                 <<"[1] Return the ordinate by the x value"<<endl
                 <<"[2] Return the length of the arc from its projection [x1,x2] "<<endl
                 <<"[3] Return the radius of curvature relative to x"<<endl
                 <<"[4] Return the coordinates of the center of curvature relative to x"<<endl
                 <<"[5] Return the area of the curved trapezoid from its projection [x1,x2]"<<endl
                 <<"[6] Exit"<<endl<<endl<<">>>";
            getNum(ret);
        }while(ret < 0 || ret > 6);
        system("cls");
        (this->*functionMass[ret])();
    }while (ret != 6);
}

void Menu::changeParm(){
    system("cls");
    getParam(A);
    catenary.setParam(A);
}

void Menu::getY(){
    long double x;
    cout <<"Enter x: ";
    getNum(x);
    cout<<"y = "<<catenary.findY(x)<<endl
        <<"Press any key to continue."<<endl;
    _getch();
}

void Menu::getLength(){
    long double x1, x2;
    cout <<"Enter x1: ";
    getNum(x1);
    cout <<"Enter x2: ";
    getNum(x2);
    cout<<"Length = "<<catenary.findLength(x1, x2)<<endl
        <<"Press any key to continue."<<endl;
    _getch();
}

void Menu::getR(){
    long double x;
    cout << "Enter x: ";
    getNum(x);
    cout<<"Radius = "<<catenary.findR(x)<<endl
        <<"Press any key to continue."<<endl;
    _getch();
}

void Menu::getOr(){ //bad
    long double x;
    cout<<"Enter x: ";
    getNum(x);
    cout<<"Coordinats of the center:"<<endl
        <<"x = 0 y = "<<catenary.findOr(x)<<endl
        <<"Press any key to continue."<<endl;
    _getch();
}

void Menu::getS(){ //bad
    long double x1, x2;
    cout <<"Enter x1: ";
    getNum(x1);
    cout <<"Enter x2: ";
    getNum(x2);
    cout<<"S = "<<catenary.findS(x1, x2)<<endl;
    cout<<"Press any key to continue."<<endl;
    _getch();
}

void Menu::exit(){
    cout <<"The program has finished its work."<<endl<<"Press any key to quit."<<endl;
}
