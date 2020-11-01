#include <iostream>
#include "big_dec.h"

using namespace std;


int main()
{
    BigDec a, b, c;
    a.input(cin);
    cout<<endl;
    b.input(cin);
    cout<<"Output:" <<endl;
    c = a.add(b);
    c.print(cout);
    cout<<endl;

    a.input(cin);
    cout<<endl;
    b.input(cin);
    cout<<"Output:" <<endl;
    c = a.sub(b);
    c.print(cout);
    return 0;
}
