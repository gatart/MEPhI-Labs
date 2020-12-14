#include <iostream>
#include "menu.h"

using std::endl;

int main()
{
    Menu prog;
    try {
        prog.mainMenu();
    } catch (istream::failure& e) {
        cout<<"Oops, something bad happened. It seems to me that it is: "<<e.what()<<endl;
    }
    return 0;
}
