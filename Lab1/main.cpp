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

    try { //bad alloc Matrix 1
        M.mass = new point[M.lines];
    } catch (std::bad_alloc& ba) {
        cout <<ba.what();
        return 0;
    }
    flag = buildMatrix(M);
    if (flag){ //bad alloc Matrix 2
        cleanData(M);
        return 0;
    }
    double *V;
    try { //bad alloc Vector
        V = new double[M.lines];
    } catch (std::bad_alloc& ba) {
        cout <<ba.what();
        return 0;
    }
    flag = buildVector(M, V);
    if (flag)
        viewAnswer(M, V);
    cleanData(M);
    delete V;
    return 0;
}
