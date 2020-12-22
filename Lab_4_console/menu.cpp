#include <iostream>
#include "menu.h"
#include <conio.h>
#include <string>

using std::endl;
using std::map;
using std::string;
using std::invalid_argument;
using std::logic_error;
using std::system_error;

const string nameCheck = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
const string EXISTS = "File with same name already exists in directory!";
const string DENIED = "Permission denied";
const string NOFILE = "No such file(s) with this name(s)";
const string NODIR = "No such directory(ies) with this name(s)";

string Menu::_ID = "aaaaaaaaaaaaaaaaaaaaaaaa"; //a - 24


Menu::Menu(){
    _table = new map<string, File*>;
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
                 <<"[5] Defragmentation"<<endl
                 <<"[6] Exit"<<endl;
            ret = getSome<int>(">>>");
        }while(ret < 0 || ret > 6);
        system("cls");
        (this->*functionMass[ret])();
    }while (ret != 6);
}

string Menu::setName(){
    string name;
    bool flag;
    do{
        cout <<"Name can consist 24 symbols of a-z and A-Z)"<<endl;
        name = getSome<string>("Enter file's name: ");
        flag = false;

        if (name.size() > 24){ //too long
            flag = true;
            continue;
        }
        if (name.empty()){
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

TYPE Menu::setType(){
    TYPE type;
    int ans;
    do{
        cout <<"(0 - catalog, 1 - common file, 2 - byte file, 3 - block file)"<<endl;
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

unsigned int Menu::setVol(){
    unsigned int vol = getSome<unsigned int>("Enter file's volume: ");
    return vol;
}

map<string, string> &Menu::getWay(){
    cout <<"Enter the way to file (example /dir1/dir2/dir3):" <<endl;
    string way;
    bool fl;
    do{
        cout << "/";
        getline(cin, way);
        fl = false;
        if (cin.fail()){
            cin.clear();
            cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
            fl = true;
        }
    }while(fl);
    string dir;
    map<string, string>::iterator tmp;
    map<string, File*>::iterator file;
    map<string, string> *table = &_root;
    size_t pos;
    while(!way.empty()){
        pos = way.find("/");
        if (pos == string::npos){
            dir = way;
            way.clear();
        }else{
            dir = way.substr(0, pos);
            way.erase(0, pos + 1);
        }

        tmp = table->find(dir);
        if (tmp == table->end()){
            throw std::invalid_argument("No such file");
        }
        file = _table->find(tmp->second);
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

void Menu::defragDir(string id, map<string, File*> &table){ // !!!!!!!!!!!!!!!!!WRITE MEEEEEEEEEEEEEEEEEEe!!!!!!!!!!!!!!!!!!!!!!!
    map<string, string> &Dir = dynamic_cast<Catalog*>(_table->find(id)->second)->getDir();
    map<string, string>::iterator dir = Dir.begin();

    cout <<"dirfrag"<<endl;
    while(dir != Dir.end()){
        table.insert(make_pair(_ID, _table->find(dir->second)->second));
        if (_table->find(dir->second)->second->getType() == TYPE::CATALOG){
            string newID = _ID;
            _table->find(dir->second)->second->putID(_ID);
            nextID(_ID);
            defragDir(dir->second, table);
            dir->second = newID;
        }else{
            _table->find(dir->second)->second->putID(_ID);
            dir->second = _ID;
            nextID(_ID);
        }
        dir++;
    }
}

void Menu::defragment(){ // !!!!!!!!!!!!!!!!!!!!!!!!Write MEEEEEEEEEEEEEEEEEEEEEE!!!!!!!!!!!!!!!!!!!!!!!!!
    _ID = "aaaaaaaaaaaaaaaaaaaaaaaa";
    map<string, File*> *table = new map<string, File*>;
    map<string, string>::iterator dir = _root.begin();

    while(dir != _root.end()){
        table->insert(make_pair(_ID, _table->find(dir->second)->second));
        cout <<_ID<<endl;
        if (_table->find(dir->second)->second->getType() == TYPE::CATALOG){
            string newID = _ID;
            _table->find(dir->second)->second->putID(_ID);
            nextID(_ID);
            defragDir(dir->second, *table);
            dir->second = newID;
        }else{
            _table->find(dir->second)->second->putID(_ID);
            dir->second = _ID;
            nextID(_ID);
        }
        dir++;
    }

    delete _table;
    _table = table;

    cout <<endl<<"Press any key to continue."<<endl;
    _getch();
}

bool Menu::findName(const string &name, map<string,string> &table){
    map<string,string>::iterator tmp = table.find(name);
    if (tmp == table.end()){
        return false;
    }
    return true;
}

void Menu::delDir(string id){
    map<string, string> &dir = dynamic_cast<Catalog *>(_table->find(id)->second)->getDir();
    map<string,string>::iterator tmp = dir.begin();
    while(tmp != dir.end()){
        if (_table->find(tmp->second)->second->getType() == TYPE::CATALOG){
            delDir(tmp->second);
        }
        delete _table->find(tmp->second)->second;
        _table->erase(tmp->second);
        tmp++;
    }
}

unsigned int Menu::getDirVol(string id){
    map<string, string> &dir = dynamic_cast<Catalog *>(_table->find(id)->second)->getDir();
    map<string,string>::iterator tmp = dir.begin();
    unsigned int vol = 0;
    while(tmp != dir.end()){
        if (_table->find(tmp->second)->second->getType() == TYPE::CATALOG){
            vol += getDirVol(tmp->second);
        }else{
            vol += _table->find(tmp->second)->second->getvol();
        }
        tmp++;
    }

    return vol;
}

string Menu::generateID(){
    if (_ID.empty()){
        defragment();
        if (_ID.empty()){
            throw std::overflow_error("All IDs already used");
        }
    }
    string ID = _ID;
    nextID(_ID);
    return ID;
}

void Menu::addFile(){
    TYPE type = setType();
    string name = setName();

    if (type == TYPE::BYTE || type == TYPE::BLOCK){
        if (findName(name, _root)){
            system("cls");
            cout <<EXISTS<<endl;
        }else{
            string id;
            unsigned int vol = setVol();

            try {
                id = generateID();
                _root.insert(make_pair(name, id));
                File *specfile = new File(type, id, vol, name);
                try {
                    _table->insert(make_pair(id, specfile));
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
                        _table->insert(make_pair(id, dir));
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
                unsigned int vol = setVol();

                try {
                    id = generateID();
                    table.insert(make_pair(name, id));
                    File *common = new CommonFile(type, id, vol, name);
                    try {
                        _table->insert(make_pair(id, common));
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
        } catch (invalid_argument) { //permission denied, no such directory/file
            system("cls");
            cout << NOFILE<<endl;
        } catch (logic_error){
            system("cls");
            cout <<NODIR <<endl;
        } catch (system_error){
            system("cls");
            cout <<DENIED <<endl;
        }
    }

    cout <<"Press any key to continue."<<endl;
    _getch();
}

void Menu::chmod(){
    try {
        map<string, string> &table = getWay();
        string name = setName();
        map<string, string>::iterator tmp;

        tmp = table.find(name);
        if (tmp == table.end()){
            system("cls");
            cout << NOFILE<<endl;
        }else{
            int mod;
            do{
                cout <<"(1 - execution, 2 - write, 4 - read)"<<endl;
                mod = getSome<int>("Enter access rights: ");
            }while(mod > 7 || mod < 0);

            _table->find(tmp->second)->second->chmod(mod);
        }
    }  catch (invalid_argument) { //permission denied, no such directory/file
        system("cls");
        cout << NOFILE<<endl;
    } catch (logic_error){
        system("cls");
        cout <<NODIR <<endl;
    } catch (system_error){
        system("cls");
        cout <<DENIED <<endl;
    }

    cout <<"Press any key to continue."<<endl;
    _getch();
}

void Menu::chvol(){
    try {
        map<string, string> &table = getWay();
        string name = setName();
        map<string, string>::iterator tmp;

        tmp = table.find(name);
        if (tmp == table.end()){
            system("cls");
            cout << NOFILE<<endl;
        }else{
            unsigned int vol = setVol();

            try {
                _table->find(tmp->second)->second->chvol(vol);
            } catch (system_error) {
                system("cls");
                cout <<"Directory's volume depends of files in it."<<endl<<DENIED <<endl;
            }
        }
    }  catch (invalid_argument) { //permission denied, no such directory/file
        system("cls");
        cout << NOFILE<<endl;
    } catch (logic_error){
        system("cls");
        cout <<NODIR <<endl;
    } catch (system_error){
        system("cls");
        cout <<DENIED <<endl;
    }

    cout <<"Press any key to continue."<<endl;
    _getch();
}

void Menu::delFile(){
    try {
        map<string, string> &table = getWay();
        string name = setName();
        map<string, string>::iterator tmp;

        tmp = table.find(name);
        if (tmp == table.end()){
            system("cls");
            cout << NOFILE<<endl;
        }else{
            if (_table->find(tmp->second)->second->getType() == TYPE::CATALOG){
                delDir(tmp->second);
            }
            delete _table->find(tmp->second)->second;
            _table->erase(tmp->second);
            table.erase(name);
            cout<<"File deleted successfully."<<endl;
        }
    }  catch (invalid_argument) { //permission denied, no such directory/file
        system("cls");
        cout << NOFILE<<endl;
    } catch (logic_error){
        system("cls");
        cout <<NODIR <<endl;
    } catch (system_error){
        system("cls");
        cout <<DENIED <<endl;
    }

    cout <<"Press any key to continue."<<endl;
    _getch();
}

void Menu::viewInfo(){
    cout <<"\t\t    Name\t\t       ID Access    Type      Volume  Time"<<endl;
    map<string,File*>::iterator tmp;
    for (tmp = _table->begin(); tmp != _table->end(); tmp++){
        File* file = tmp->second;
        printf("%*s ", 24, (file->getName()).c_str());
        cout << file->getID()<<" ";

        int mod = file->getmod();
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
        }else cout <<"-   ";

        TYPE type = file->getType();
        if (type == TYPE::BYTE){
            cout <<"BYTE     ";
        }else if (type == TYPE::BLOCK){
            cout <<"BLOCK    ";
        }else if (type == TYPE::COMMON){
            cout <<"COMMON   ";
        }else{
            cout <<"CATALOG  ";
        }

        if (type == TYPE::CATALOG){
            printf("%*d  ", 10, getDirVol(tmp->first));
        }else{
            printf("%*d  ", 10, file->getvol());
        }
        if (type == TYPE::COMMON){
            string time = string(asctime(localtime(dynamic_cast<CommonFile*>(file)->getTime())));
            time.erase(time.size() - 1);
            cout<<time;
        }
        cout <<endl;
    }

    cout <<endl<<"Press any key to continue."<<endl;
    _getch();
}

void Menu::exit(){
    cout <<"The System has finished its work."<<endl<<"Press any key to quit."<<endl;
}

Menu::~Menu(){
    map<string, File*>::iterator tmp = _table->begin();
    while(tmp != _table->end()){
        cout <<"begin";
        delete tmp->second;
        cout <<"end";
    }

    delete _table;
}
