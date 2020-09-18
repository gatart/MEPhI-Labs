#include "workspace.h"

void getSize(int &a, std::string L){
    do{
        cout <<L <<" ";
        getNum(a);
    }while (a <= 0);
};

bool buildMatrix(matrix &M){
    point *tmp;
    int num;
    for (int i = 0; i < M.lines; ++i){
        tmp = &M.mass[i];
        cout << "Enter line " <<i + 1 <<":" <<endl;
        for (int j = 0; j < M.rows; ++j){
            getNum(num); //Can be bad alloc
            if (num != 0){
                try {
                    tmp->next = new point;
                } catch (std::bad_alloc& ba) {
                    cout <<ba.what();
                    return true;
                }
                tmp = tmp->next;
                tmp->key = j;
                tmp->info = num;
                tmp->next = nullptr;
            }
        }
    }
    return false;
}
bool buildVector(const matrix &M, double *V){
    int S, Max, Min, j;
    bool flag;
    point *tmp;
    for (int i = 0; i < M.lines; ++i){
        S = 0;
        Max = 0;
        Min = 0;
        j = 0;
        flag = true;
        tmp = M.mass[i].next;
        while(tmp){ //Count max, min and sum from non-zero elements
            S += tmp->info;
            j++;
            if (flag){ //first non-zero element
                Max = tmp->info;
                Min = tmp->info;
                tmp = tmp->next;
                flag = false;
                continue;
            }
            if (Max < tmp->info)
                Max = tmp->info;
            else if (Min > tmp->info)
                Min = tmp->info;
            tmp = tmp->next;
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
                throw 2;
            V[i] = static_cast<double>(S) / Max;
        } catch (int i) {
            cout <<"Devision by zero!"<<endl;
            return false;
        }
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
    int j;
    point *tmp;
    cout <<endl<<"Matrix:";
    for (int i = 0; i < M.lines; ++i){
        cout <<endl;
        j = 0;
        tmp = M.mass[i].next;
        while(j < M.rows){
            if (tmp && tmp->key == j){ //non-zero element
                cout << tmp->info <<"   ";
                tmp = tmp->next;
                j++;
                continue;
            }
            cout << "0   ";
            j++;
        }
    }
    cout <<endl;
}

void cleanMatrix(matrix &M){
    point *tmp, *next;

    for (int i = 0; i < M.lines; ++i){
        tmp = M.mass[i].next;
        while(tmp){
            next = tmp->next;
            delete tmp;
            tmp = next;
        }
    }
    delete M.mass;
    cout <<"Clearing complete!";
}
void cleanVector(double *V){
    delete V;
}
void cleanData(matrix &M, double *V){
    cleanMatrix(M);
    cleanVector(V);
}
