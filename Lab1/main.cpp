#include "workspace.cpp"

int main() {
    matrix M;
    bool flag;
    cout <<"Enter matrix size"<<endl;
    getSize(M.lines, "Lines: ");
    getSize(M.rows, "Rows: ");

    try { //bad alloc Matrix 1
        M.mass = new point[M.lines];
    } catch (std::bad_alloc& ba) {
        cout <<ba.what();
        return 0;
    }
    flag = buildMatrix(M);
    if (flag){ //bad alloc Matrix 2
        cleanMatrix(M);
        return 0;
    }
    double *V;
    try { //bad alloc Vector
        V = new double[M.lines];
    } catch (std::bad_alloc& ba) {
        cout <<ba.what();
        return 0;
    }
    viewMatrix(M);
    flag = buildVector(M, V);
    if (flag)
        viewVector(V, M.lines);
    cleanData(M, V);
    return 0;
}
