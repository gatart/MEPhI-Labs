#include <iostream>
#include "big_dec.h"

using namespace std;


int main()
{
    BigDec a, b, c;
    cout <<"Add" << endl<<"Enter 1 number: ";
    cin >> a;
    cout<<"Enter 2 number: ";
    cin >> b;
    cout<<"Output: ";
    c = a + b;
    cout <<c;
    cout <<endl<<"Sub"<<endl<<"Enter 1 number: ";
    cin >> a;
    cout <<"Enter 2 number: ";
    cin >> b;
    cout<<"Output: ";
    c = a - b;
    cout <<c;
    cout <<endl<<"*=10"<<endl<<"Enter number: ";
    cin >> c;
    cout<<"Output: ";
    a = c.great10();
    cout <<a;
    cout <<endl<<"/=10"<<endl<<"Enter number: ";
    cin >> c;
    cout<<"Output: ";
    a = c.less10();
    cout <<a <<endl;
    return 0;
}