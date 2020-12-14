#include <iostream>
#include "menu.h"
#include <conio.h>
#include <string>

using std::endl;
const std::string idCheck = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";

Menu::Menu(){

}

void Menu::mainMenu(){
    int ret;
    do{
        do{
            system("cls");
            cout <<"Menu:"<<endl
                 <<"[0] Add file to the system"<<endl
                 <<"[1] Change access rights"<<endl
                 <<"[2] Change the volume of file"<<endl
                 <<"[3] Delete file"<<endl
                 <<"[4] Show information about files"<<endl
                 <<"[5] Exit"<<endl;
            getNum(ret);
        }while(ret < 0 || ret > 5);
        system("cls");
        (this->*functionMass[ret])();
    }while (ret != 5);
}

std::string Menu::getID(){
    std::string ID;
    bool flag;
    do{
        cout <<"Name can consist 24 symbols of a-z and A-Z)"<<endl
             <<"Enter file's name: "<<endl;
        cin >> ID;
        flag = false;

        if (ID.size() > 24){ //too long
            flag = true;
            continue;
        }
        for (char a : ID){ //
            if (idCheck.find(a) == std::string::npos){
                flag = true;
                break;
            }
        }
    }while(flag);

    return ID;
}

TYPE getType(){
    TYPE type;
    int ans;
    do{
        cout <<"(0 - catalog, 1 - common file, 2 - byte file, 3 - block file)"
             <<"Choose file's type: ";
        getNum(ans);
    }while(ans > 3 || ans < 0);

    if(ans == 0){
        type = TYPE::CATALOG;
    }else if (ans == 1){
        type = TYPE::COMMON;
    }else if (ans == 2){
        type = TYPE::BYTE;
    }else {
        type = TYPE::BLOCK;
    }

    return type;
}

void Menu::addFile(){ // !!!!!!!!!!!!!
    std::string ID = getID();

    //FIND ID IN THE TABLE!!!!!!!!!!!!!!!!

    TYPE type = getType();

    if (type == TYPE::BYTE || type == TYPE::BLOCK){


    }else{
        //ASK the WAY
        if (type == TYPE::CATALOG){


        }else{


        }
    }

    cout <<"File added successfully."<<endl
         <<"Press any key to continue."<<endl;
    _getch();
}

void Menu::chmod(){
    int mod;
    do{
        cout <<"(1 - execution, 2 - write, 4 - read)"<<endl<<"Enter access rights: ";
        getNum(mod);
    }while(mod > 7 || mod < 0);
    cout <<"Press any key to continue."<<endl;
    _getch();
}

void Menu::chvol(){
    cout <<"Press any key to continue."<<endl;
    _getch();
}

void Menu::delFile(){
    cout <<"Press any key to continue."<<endl;
    _getch();
}

void Menu::viewInfo(){
    cout <<"Press any key to continue."<<endl;
    _getch();
}

void Menu::exit(){
    cout <<"The program has finished its work."<<endl<<"Press any key to quit."<<endl;
}
