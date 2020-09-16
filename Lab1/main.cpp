#include "workspace.h"

int main() {
    matrix M;
    bool flag;

    cout <<"Enter matrix size"<<endl<<"Lines: ";
    getNum(M.lines);
    cout <<"Rows: ";
    getNum(M.rows);
    cout <<"Do you want to generate random matrix or enter it by yorself? (0 - no, 1 - yes)"<< endl;
    getNum(flag);
    if (flag)
        generateMatrix(M);
    else
        buildMatrix(M);

    buildVector(M);
    viewAnswer();
    return 0;
}
