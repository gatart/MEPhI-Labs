#include <iostream>
#include "menu.h"
#include <conio.h>
#include <string>

using std::endl;
using std::map;
using std::invalid_argument;
using std::logic_error;
using std::system_error;

const string nameCheck = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
const string EXISTS = "File with same name already exists in directory!";
const string DENIED = "Permission denied";
const string NOFILE = "No such file(s) with this name(s)";
const string NODIR = "No such directory(ies) with this name(s)";


Menu::Menu(){

}

void Menu::mainMenu(){ //Change or not!!!!!!!!!!!!!!!!!!!!!!!
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
            ret = getSome<int>("");
        }while(ret < 0 || ret > 5);
        system("cls");
        (this->*functionMass[ret])();
    }while (ret != 5);
}

string Menu::getName(){
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
            if (nameCheck.find(a) == std::string::npos){
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
        ans = getSome<int>("Choose file's type: ");
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

unsigned int Menu::getVol(){
    unsigned int vol = getSome<unsigned int>("Enter file's volume: ");
    return vol;
}

std::map<string, string> &Menu::getWay(){
    cout <<"Enter the way to file (example /dir1/dir2/dir3):" <<endl;
    string way = getSome<string>("/");
    string dir;
    map<string, string>::iterator tmp;
    map<string, File*>::iterator file;
    map<string, string> *table = &_root;
    size_t pos;
    while(!way.empty()){
        pos = way.find("/");
        if (pos == string::npos){
            dir = way;
        }else{
            dir = way.substr(0, pos);
            way.erase(0, pos + 1);
        }

        tmp = table->find(dir);
        if (tmp == table->end()){
            throw std::invalid_argument("No such file");
        }
        file = _table.find(tmp->second);
        if (file->second->getType() != TYPE::CATALOG){
            throw logic_error("Not dir");
        }
        if (file->second->getmod() - 4 < 2){
            throw system_error();
        }

        table = &dynamic_cast<Catalog*>(file->second)->getDir();
    }

    return *table;
}

void Menu::nextID(std::string &ID){
    int i = 23;
    while(i >= 0){
        ID[static_cast<size_t>(i)] += 1;
        if (ID[static_cast<size_t>(i)] > 'z'){
            ID[static_cast<size_t>(i)] = 'a';
            i--;
        }else{
            break;
        }
    }
    if (i == -1){
        ID.clear();
    }
}

void Menu::defragment(){ // !!!!!!!!!!!!!!!!!!!!!!!!Write MEEEEEEEEEEEEEEEEEEEEEE!!!!!!!!!!!!!!!!!!!!!!!!!
    _id = "aaaaaaaaaaaaaaaaaaaaaaaa";
    map<string,File*>::iterator tmp;
    for (tmp = _table.begin(); tmp != _table.end(); tmp++){

    }
}

bool Menu::findName(const string &name, std::map<string,string> &table){
    map<string,string>::iterator tmp = table.find(name);
    if (tmp == table.end()){
        return false;
    }
    return true;
}


string Menu::generateID(){
    if (_id.empty()){
        defragment();
        if (_id.empty()){
            throw std::overflow_error("All IDs already used");
        }
    }
    string ID = _id;
    nextID(_id);
    return ID;
}

void Menu::addFile(){ // !!!!!!!!!!!!!
    TYPE type = getType();
    string name = getName();

    if (type == TYPE::BYTE || type == TYPE::BLOCK){
        if (findName(name, _root)){
            system("cls");
            cout <<EXISTS<<endl;
        }else{
            string id;
            unsigned int vol = getVol();

            try {
                id = generateID();
                _root.insert(make_pair(name, id));
                File *specfile = new File(type, id, vol, name);
                try {
                    _table.insert(make_pair(id, specfile));
                    cout <<"File added successfully."<<endl;
                } catch (...) {
                    delete specfile;
                    throw;
                }
            } catch (std::overflow_error &e) {
                system("cls");
                cout <<e.what()<<endl;
            }
        }
    }else{
        try {
            map<string, string> &table = getWay();
            string id;
            if (type == TYPE::CATALOG){
                try {
                    id = generateID();
                    table.insert(make_pair(name, id));
                    File *dir = new Catalog(type, id, name);
                    try {
                        _table.insert(make_pair(id, dir));
                        cout <<"File added successfully."<<endl;
                    } catch (...) {
                        delete dir;
                        throw;
                    }
                } catch (std::overflow_error &e) {
                    system("cls");
                    cout <<e.what()<<endl;
                }
            }else{
                unsigned int vol = getVol();

                try {
                    id = generateID();
                    table.insert(make_pair(name, id));
                    File *common = new CommonFile(type, id, vol, name);
                    try {
                        _table.insert(make_pair(id, common));
                        cout <<"File added successfully."<<endl;
                    } catch (...) {
                        delete common;
                        throw;
                    }
                } catch (std::overflow_error &e) {
                    system("cls");
                    cout <<e.what()<<endl;
                }
            }
        } catch (invalid_argument) { //permission denied, no such directory
            cout << NOFILE<<endl;
        } catch (logic_error){
            cout <<NODIR <<endl;
        } catch (system_error){
            cout <<DENIED <<endl;
        }
    }

    cout <<"Press any key to continue."<<endl;
    _getch();
}

void Menu::chmod(){
    int mod;
    do{
        cout <<"(1 - execution, 2 - write, 4 - read)"<<endl<<"Enter access rights: ";
        mod = getSome<int>("Enter access rights: ");
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

void Menu::viewInfo(){ // !!!!!!!!!!!!!!!!!!!TIMEEEEEE!!!!!!!!!!!!!!!!!!!!!!!!
    cout <<"Name\t\t\t\t\t\tID\t\t\t\t\t\t\tAccess\tType\t\tVolume\t\t\t\tTime"<<endl;
    map<string,File*>::iterator tmp;
    for (tmp = _table.begin(); tmp != _table.end(); tmp++){
        printf("%*s\t", 24, (tmp->second->getName()).c_str());
        printf("%*s\t", 24, (tmp->first).c_str());
        cout << tmp->second->getID()<<"\t";

        int mod = tmp->second->getmod();
        if (mod >= 4){
            mod -= 4;
            cout <<"-r";
        }else cout <<"--";
        if (mod >= 2){
            mod -= 2;
            cout <<"w";
        }else cout <<"-";
        if (mod == 1){
            cout <<"x\t";
        }else cout <<"-\t";

        TYPE type = tmp->second->getType();
        if (type == TYPE::BYTE){
            cout <<"BYTE\t\t";
        }else if (type == TYPE::BLOCK){
            cout <<"BLOCK\t\t";
        }else if (type == TYPE::COMMON){
            cout <<"COMMON\t\t";
        }else{
            cout <<"CATALOG\t\t";
        }

        printf("%*d\t", 15, tmp->second->getvol());
        if (type == TYPE::COMMON){
            //cout<<TIME;
        }
        cout <<endl;
    }

    cout <<"Press any key to continue."<<endl;
    _getch();
}

void Menu::exit(){
    cout <<"The System has finished its work."<<endl<<"Press any key to quit."<<endl;
}
