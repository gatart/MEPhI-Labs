#include "workspace.cpp"

int main() {
    matrix M;
    bool flag;
    cout <<"Enter matrix size"<<endl;
    getSize(M.lines, "Lines: ");
    getSize(M.rows, "Rows: ");
    flag = buildMatrix(M);
    if (flag){ //bad alloc Matrix 2
        cleanMatrix(M);
        return 0;
    }
    double *V;
    V = loccMem<double>(flag);
    if (flag){
        cleanMatrix(M);
        return 0;
    }
    viewMatrix(M);
    flag = buildVector(M, V);
    if (flag)
        viewVector(V, M.lines);
    cleanData(M, V);
    return 0;
}
