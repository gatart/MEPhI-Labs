#include "workspace.h"

void getNum(int &a, std::string L, int min, int max){
    cin.exceptions(istream::failbit | istream::badbit);
    do{
        cout <<L;
        cin >>a;
    }while (a < min || a > max); //If less then INT_MIN - exception, with INT_MAX - same
};
void getPoint(int &i, int &j, int &num, const matrix &M){
    getNum(i, "First index: ", 0, M.lines);
    getNum(j, "Second index: ", 0, M.rows);
    getNum(num, "Value: ", INT_MIN, INT_MAX);
}

line* giveLine(line *tmp, const int &i){
    line *last = nullptr;
    while(tmp){
        if (tmp->key == i){ //Find
            return tmp;
        }
        if (tmp->key > i){ //Place between
            last->next = nullptr;
            last->next = loccMem<line>(1);
            last = last->next;
            last->next = tmp;
            last->key = i;
            return last;
        }
        last = tmp;
        tmp = tmp->next;
    }
    last->next = loccMem<line>(1); //place in the end
    tmp = last->next;
    tmp->key = i;
    return tmp;
};
void findPoint();

void buildMatrix(matrix &M){
    int i, j, num; //A[i][j] = num
    line head = {-1, nullptr, nullptr}, *tmp1 = nullptr;
    point *tmp2 = nullptr;

    tmp1 = &head;
    cout <<"Enter Matrix (enter 0 to end): "<<endl;
    getPoint(i, j, num, M);
    while (num != 0){
        //--------------
        tmp1 = giveLine(tmp1, i);
        tmp2 = tmp1->el;
        //tmp2 = giveLine(tmp2, j);

        //--------------
        getPoint(i, j, num, M);
    }
    M.mass = head.next;
}
/*
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
*/
bool buildVector(const matrix &M, double *V){
    int S, Max, Min, i = 0, j;
    line *tmp1 = M.mass;
    point *tmp2;
    while(tmp1){
        tmp2 = tmp1->el;
        S = 0;
        Max = INT_MIN;
        Min = INT_MAX;
        j = 0;
        while(tmp2){ //Count Sum, Max and Min in line
            S += tmp2->info;
            j++;
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
