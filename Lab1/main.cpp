#include "workspace.cpp"

int main() {
    matrix M;
    bool flag;

    cout <<"Enter matrix size"<<endl<<"Lines: ";
    do
        getNum(M.lines);
    while (M.lines <= 0);
    cout <<"Rows: ";
    do
        getNum(M.rows);
    while (M.rows <= 0);
    M.mass = new point[M.lines]; //Can be bad alloc

    /*
    cout <<"Do you want to generate random matrix or enter it by yorself? (0 - no, 1 - yes)"<< endl;
    getNum(flag);
    if (flag)
        generateMatrix(M);
    else
    */
    buildMatrix(M);

    double *V = new double[M.lines];
    flag = buildVector(M, V);
    if (flag)
        viewAnswer(M, V);
    cleanData(M,V);
    return 0;
}
