#include "workspace.h"

void getSize(int &a, std::string L){
    do{
        cout <<L <<" ";
        getNum(a);
    }while (a <= 0);
};
bool buildMatrix(matrix &M){
    int i = 0, j, num; //A[i][j]
    line *tmp1 = nullptr;
    point *tmp2 = nullptr;
    bool zero, fline = true, flag = true;
    while (i < M.lines){
        cout << "Enter line " <<i + 1 <<":" <<endl;
        zero = true;
        j = 0;
        while (j < M.rows){
            getNum(num);
            if (num != 0){
                if (zero){
                    if (fline){ //first non-zero line
                        M.mass = loccMem<line>(flag, 1);
                        if (flag){
                            return true;
                        }
                        tmp1 = M.mass;
                        fline = false;
                    }else{ //non-zero line
                        tmp1->next = loccMem<line>(flag, 1);
                        if (flag){
                            return true;
                        }
                        tmp1 = tmp1->next;
                    }
                    zero = false;
                    tmp1->key = i;
                    tmp1->el = loccMem<point>(flag, 1); //first element
                    if (flag){
                        return true;
                    }
                    tmp2 = tmp1->el;
                }else{ //new element
                    tmp2->next = loccMem<point>(flag, 1);
                    if (flag){
                        return true;
                    }
                    tmp2 = tmp2->next;
                }
                tmp2->key = j;
                tmp2->info = num;
            }
            ++j;
        }
        ++i;
    }
    if (fline){
        cout <<"Zero matrix!" <<endl;
        return true;
    }
    return false;
}
bool buildVector(const matrix &M, double *V){
    int S, Max, Min, i = 0, j;
    line *tmp1 = M.mass;
    point *tmp2;
    bool flag;
    while(tmp1){
        tmp2 = tmp1->el;
        S = 0;
        Max = 0;
        Min = 0;
        j = 0;
        flag = true;
        while(tmp2){ //Count Sum, Max and Min in line
            S += tmp2->info;
            j++;
            if (flag){ //first non-zero element
                Max = tmp2->info;
                Min = tmp2->info;
                tmp2 = tmp2->next;
                flag = false;
                continue;
            }
            if (Max < tmp2->info)
                Max = tmp2->info;
            else if (Min > tmp2->info)
                Min = tmp2->info;
            tmp2 = tmp2->next;
        }
        if (j < M.rows - 1){ //if Min or Max is zero
            if (Max < 0)
                Max = 0;
            else if (Min > 0)
                Min = 0;
        }
        S -= Min;
        Max -= Min;
        try {
            if (Max == 0)
                throw "Division by zero!";
            V[i] = static_cast<double>(S) / Max;
        } catch (std::string L) {
            cout <<L<<endl;
            return false;
        }
        tmp1 = tmp1->next;
        ++i;
    }
    if (i < M.lines - 1){
        cout <<"Division by zero!"<<endl;
        return false;
    }
    return true;
}

void viewVector(double *V, int Lines){
    cout <<endl <<"Vector:" <<endl <<"{" << V[0];
    for (int i = 1; i < Lines; ++i)
        cout <<", " <<V[i];
    cout <<"}" <<endl<<endl;
}
void viewMatrix(const matrix &M){
    int i = 0, j;
    line *tmp1;
    point *tmp2;
    cout <<"Matrix:"<<endl;
    tmp1 = M.mass;
    while (i < M.lines){
        if (tmp1 && tmp1->key == i){
            j = 0;
            tmp2 = tmp1->el;
            while (j < M.rows){ //Line
                if (tmp2 && tmp2->key == j){
                    cout <<tmp2->info <<"   ";
                    tmp2 = tmp2->next;
                }else{
                    cout <<"0   ";
                }
                j++;
            }
            tmp1 = tmp1->next;
        }else{ //Zero line
            for(j = 0; j < M.rows; ++j)
                cout <<"0   ";
        }
        i++;
        cout <<endl;
    }
    cout <<endl;
}

void cleanMatrix(matrix &M){
    line *tmp1, *next1;
    point *tmp2, *next2;
    tmp1 = M.mass;
    while(tmp1){
        tmp2 = tmp1->el;
        while(tmp2){
            next2 = tmp2->next;
            delete tmp2;
            tmp2 = next2;
        }
        next1 = tmp1->next;
        delete tmp1;
        tmp1 = next1;
    }
    cout <<"Clearing complete!";
}
void cleanVector(double *V){
    delete [] V;
}
void cleanData(matrix &M, double *V){
    cleanVector(V);
    cleanMatrix(M);
}
