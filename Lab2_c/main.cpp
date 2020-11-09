#include <iostream>
#include "big_dec.h"

using namespace std;


int main()
{
    long int smth = -1400569258;
    BigDec k(smth);
    cout <<"Long constructor: "<< k<<endl;

    BigDec a, b, c;

    cout <<">" << endl<<"Enter 1 number: ";
    cin >> a;
    cout<<"Enter 2 number: ";
    cin >> b;
    cout <<(a > b)<<endl;

    cin >> a;
    cout <<-a<<endl;
    cout <<"Add" << endl<<"Enter 1 number: ";
    cin >> a;
    cout<<"Enter 2 number: ";
    cin >> b;
    c = a + b;
    cout <<a <<endl<<b<<endl;
    cout <<"Output: " <<c <<endl;

    cout <<"Sub" <<endl <<"Enter 1 number: ";
    cin >> a;
    cout <<"Enter 2 number: ";
    cin >> b;
    c = a - b;
    //cout <<"Some shit happend"<<endl;
    cout <<a <<endl<<b<<endl;
    cout<<"Output: " <<c <<endl;

    cout <<"<<" <<endl <<"Enter number: ";
    cin >> c;
    cout <<"Enter shift: ";
    int j;
    cin >> j;
    cin.clear();
    cin.ignore(32767, '\n');
    a = c << j;
    cout<<"Output: " <<a <<endl;

    cout <<">>" <<endl <<"Enter number: ";
    cin >> c;
    cout <<"Enter shift: ";
    cin >> j;
    cin.clear();
    cin.ignore(32767, '\n');
    a = c >> j;
    cout<<"Output: " <<a <<endl;

    cout <<"Add" << endl<<"Enter number: ";
    cin >> a;
    char* o = new char[5];
    for (int i = 0; i < 4; ++i){
        o[i] = '1';
    }
    o[4] = '\0';
    c = a + o;
    cout <<a <<endl;
    cout <<"Output: " <<c <<endl;
    delete[]o;

    cout <<"Add" << endl<<"Enter number: ";
    cin >> a;
    string p = "1111";
    c = a + p.c_str();
    cout <<a <<endl;
    cout <<"Output: " <<c <<endl;

    cout <<"Index and to string" << endl<<"Enter number: ";
    cin >> a;
    cout <<"Enter index: ";
    cin >>j;
    o = a.to_string();
    cout <<"Output: " <<a[j] <<endl <<"Output: "<<o;
    delete[]o;
    return 0;
}
