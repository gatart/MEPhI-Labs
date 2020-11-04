#include <iostream>
#include "big_dec.h"

using namespace std;


int main()
{
    long int smth = -1400569258;
    BigDec k(smth);
    cout <<"Long constructor: "<< k<<endl;
    BigDec a, b, c;
    cout <<"Add" << endl<<"Enter 1 number: ";
    cin >> a;
    cout<<"Enter 2 number: ";
    cin >> b;
    c = a + b;
    cout <<"Output: " <<c <<endl;
    cout <<"Sub" <<endl <<"Enter 1 number: ";
    cin >> a;
    cout <<"Enter 2 number: ";
    cin >> b;
    c = a - b;
    cout<<"Output: " <<c <<endl;
    cout <<"*=10" <<endl <<"Enter number: ";
    cin >> c;
    a = c.great10();
    cout<<"Output: " <<a <<endl;
    cout <<"/=10" <<endl <<"Enter number: ";
    cin >> c;
    a = c.less10();
    cout<<"Output: " <<a <<endl;
    return 0;
}
