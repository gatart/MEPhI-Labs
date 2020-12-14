#include <iostream>
#include "menu.h"
#include <conio.h>
#include <string>

using std::endl;
using std::map;
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

std::string Menu::getName(){
    std::string name;
    bool flag;
    do{
        cout <<"Name can consist 24 symbols of a-z and A-Z)"<<endl
             <<"Enter file's name: "<<endl;
        cin >> name;
        flag = false;

        if (name.size() > 24){ //too long
            flag = true;
            continue;
        }
        for (char a : name){ //
            if (idCheck.find(a) == std::string::npos){
                flag = true;
                break;
            }
        }
    }while(flag);

    return name;
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
    TYPE type = getType();
    std::string ID = getName();

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
    // output of headers of collums

    map<std::string,File*>::iterator tmp;
    for (tmp = _table.begin(); tmp != _table.end(); tmp++){
        printf("%*s\t", 24, ((tmp->second)->getName()).c_str());
        printf("%*s\t", 24, (tmp->first).c_str());

        int mod = (tmp->second)->getmod();
        if (mod >= 4){
            mod -= 4;
            cout <<"-r";
        }else cout <<"--";
        if (mod >= 2){
            mod -= 2;
            cout <<"w";
        }else cout <<"-";
        if (mod == 1){
            cout <<"x    ";
        }else cout <<"-\t\t";

        //output type
        // output volume
        // output time (optional)


    }

    cout <<"Press any key to continue."<<endl;
    _getch();
}

void Menu::exit(){
    cout <<"The program has finished its work."<<endl<<"Press any key to quit."<<endl;
}
