#include <iostream>
#include "big_dec.h"

using namespace std;


int main()
{
    long int smth = -1400569258;
    BigDec k(smth);
    cout <<"Long constructor: "<< k<<endl;

    BigDec a, b, c;
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
    cout <<a <<endl<<b<<endl;
    cout<<"Output: " <<c <<endl;

    cout <<"*=10" <<endl <<"Enter number: ";
    cin >> c;
    a = c << 0;
    cout<<"Output: " <<a <<endl;

    cout <<"/=10" <<endl <<"Enter number: ";
    cin >> c;
    a = c >> -1;
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

    cout <<"Add" << endl<<"Enter number: ";
    cin >> a;
    string p = "1111";
    c = a + p.c_str();
    cout <<a <<endl;
    cout <<"Output: " <<c <<endl;

    cout <<"Index" << endl<<"Enter number: ";
    cin >> a;
    int j;
    cin >>j;
    cout <<"Output: " <<a[j] <<endl;
    return 0;
}
