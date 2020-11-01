#include <iostream>
#include "big_dec.h"

using namespace std;


int main()
{
    BigDec a, b, c;
    cout <<"Add" << endl<<"Enter 1 number: ";
    a.input(cin);
    cout<<"Enter 2 number: ";
    b.input(cin);
    cout<<"Output: ";
    c = a.add(b);
    c.print(cout);
    cout <<endl<<"Sub"<<endl<<"Enter 1 number: ";
    a.input(cin);
    cout <<"Enter 2 number: ";
    b.input(cin);
    cout<<"Output:";
    c = a.sub(b);
    c.print(cout);
    cout <<endl<<"*=10"<<endl<<"Enter number: ";
    c.input(cin);
    cout<<"Output: ";
    a = c.great10();
    a.print(cout);
    cout <<endl<<"/=10"<<endl<<"Enter number: ";
    c.input(cin);
    cout<<"Output: ";
    a = c.less10();
    a.print(cout);
    return 0;
}
