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
    cout<<endl;
    cout <<"Sub"<<endl<<"Enter 1 number: ";
    a.input(cin);
    cout <<"Enter 2 number: ";
    b.input(cin);
    cout<<"Output:";
    c = a.sub(b);
    c.print(cout);
    cout <<endl<<"*=10"<<endl<<"Enter number: ";
    c.input(cin);
    cout<<"Output: ";
    c.great10();
    c.print(cout);
    cout <<endl<<"/=10"<<endl<<"Enter number: ";
    c.input(cin);
    cout<<"Output: ";
    c.less10();
    c.print(cout);
    return 0;
}
