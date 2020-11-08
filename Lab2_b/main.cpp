#include <iostream>
#include "big_dec.h"

using namespace std;


int main()
{
    BigDec a, b, c;

    try {
        cout <<"Add" << endl<<"Enter 1 number: ";
        cin >> a;
        cout<<"Enter 2 number: ";
        cin >> b;
        cout<<"Output: ";
        c = a + b;
        cout <<c;
    } catch (...) {
        cout<<"Caught some error!";
    }

    try {
        cout <<endl<<"Sub"<<endl<<"Enter 1 number: ";
        cin >> a;
        cout <<"Enter 2 number: ";
        cin >> b;
        cout<<"Output: ";
        c = a - b;
        cout <<c;
    } catch (...) {
        cout<<"Caught some error!";
    }

    try {
        cout <<endl<<"*=10"<<endl<<"Enter number: ";
        cin >> c;
        cout<<"Output: ";
        a = c.great10();
        cout <<a;
    } catch (...) {
        cout<<"Caught some error!";
    }

    try {
        cout <<endl<<"/=10"<<endl<<"Enter number: ";
        cin >> c;
        cout<<"Output: ";
        a = c.less10();
        cout <<a <<endl;
    } catch (...) {
        cout<<"Caught some error!";
    }

    try {
        cout <<endl<<"Add" << endl<<"Enter 1 number: ";
        cin >> a;
        cout<<"Output: ";
        c = a + "1111";
        cout <<c;
    } catch (...) {
        cout<<"Caught some error!";
    }

    return 0;
}
