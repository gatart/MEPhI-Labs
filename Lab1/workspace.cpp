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
bool buildVector(matrix M, double *V){
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
            cout <<"Error " <<i<<" Devision by zero!"<<endl;
            return false;
        }
    }
    return true;
}
void viewAnswer(matrix M, double *V){
    int i, j;
    point *tmp;
    cout <<endl<<"Matrix:";
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

    cout <<endl << endl<< "Vector:" <<endl <<"{" << V[0];
    for (i = 1; i < M.lines; ++i)
        cout <<", " <<V[i];
    cout <<"}" <<endl<<endl;
}
void cleanData(matrix &M, double *V){
    point *tmp, *next;

    delete V;
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
