#include "workspace.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::istream;

int main() {
    matrix M;
    double *V = nullptr;
    //bool flag;
    cout <<"Enter matrix size"<<endl;
    try {
        getNum(M.lines, "Lines: ", -1, INT_MAX);
        getNum(M.rows, "Rows: ", -1, INT_MAX);
        buildMatrix(M);
        V = loccMem<double>(M.lines);
    } catch (istream::failure& e) { //Stream failure
        cout <<e.what()<<endl<<"Incorrect input value!"<<endl;
        cleanMatrix(M);
        return 0;
    } catch(std::bad_alloc& ba){ //Bad alloc
        cout <<ba.what()<<endl<<"Bad allocation of matrix!"<<endl;
        cleanMatrix(M);
        return 0;
    }
    viewMatrix(M);
    try {
        buildVector(M, V);
        viewVector(V, M.lines);
    } catch (const char *L) {
        cout <<L<<endl;
    }
    cleanData(M, V);
    return 0;
}
