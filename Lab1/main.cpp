#include "workspace.cpp"

int main() {
    matrix M;
    double *V = nullptr;
    bool flag;
    cout <<"Enter matrix size"<<endl;
    try {
        getNum(M.lines, "Lines: ", -1, INT_MAX);
        getNum(M.rows, "Rows: ", -1, INT_MAX);
        buildMatrix(M);
        V = loccMem<double>(M.lines);
    } catch (istream::failure e) { //Stream failure
        cout <<e.what();
        return 0;
    } catch(std::bad_alloc& ba){ //Bad alloc
        cout <<ba.what();
        cleanMatrix(M);
        return 0;
    }
    //========================================================
    viewMatrix(M);
    flag = buildVector(M, V);
    if (flag)
        viewVector(V, M.lines);
    cleanData(M, V);
    return 0;
}
