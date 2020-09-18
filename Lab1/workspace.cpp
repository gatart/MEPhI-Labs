#include "workspace.h"

void buildMatrix(matrix &M){
    point *tmp;
    int num;
    for (int i = 0; i < M.lines; ++i){
        tmp = &M.mass[i];
        cout << "Enter line " <<i + 1 <<":" <<endl;
        for (int j = 0; j < M.rows; ++j){
            getNum(num); //Can be bad alloc
            if (num != 0){
                tmp->next = new point; //Can be bad alloc
                tmp = tmp->next;
                tmp->key = j;
                tmp->info = num;
                tmp->next = nullptr;
            }
        }
    }
}
/*
void generateMatrix(matrix &M){
    point *tmp;
    int num;
    for (int i = 0; i < M.lines; ++i){
        tmp = &M.mass[i];
        for (int j = 0; j < M.rows; ++j) {

        }
    }
}
*/
void buildVector(matrix M, double *V){
    int S, Max, Min;
    bool flag;
    point *tmp;
    for (int i = 0; i < M.lines; ++i){
        S = 0;
        Max = 0;
        Min = 0;
        flag = true; //Check for first non-zero element
        tmp = M.mass[i].next;
        while(tmp){ //Count max, min and sum
            S += tmp->info;
            if (flag){ //first non-zero element
                Max = tmp->info;
                Min = tmp->info;
                tmp = tmp->next;
                flag = false;// После добавления этой строки вылетает
                continue;
            }
            if (Max < tmp->info)
                Max = tmp->info;
            else if (Min > tmp->info)
                Min = tmp->info;
            tmp = tmp->next;
        }
        cout <<"S = " <<S << "Max = " <<Max <<"Min = " <<Min<<endl;
        S -= Min;
        Max -= Min;
        V[i] = static_cast<double>(S) / Max; //Can be zero devision
        cout <<"Vector "<<i<<": "<< V[i]<<endl;
    }
}
void viewAnswer(matrix M, double *V){
    int i, j;
    point *tmp;
    cout <<"Matrix:";
    for (i = 0; i < M.lines; ++i){
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

    cout <<endl << "Vector:" <<endl <<"{" << V[0];
    for (i = 1; i < M.lines; ++i)
        cout <<", " <<V[i];
    cout <<"}" <<endl;
}
void cleanData(matrix &M, double *V){
    cout <<"clear";
}
