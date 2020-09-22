#include "workspace.h"

void getNum(int &a, std::string L, int min, int max){
    cin.exceptions(istream::failbit | istream::badbit);
    do{
        cout <<L;
        cin >>a;
    }while (a < min || a > max); //If less then INT_MIN - exception, with INT_MAX - same
};
void getPoint(int &i, int &j, int &num, const matrix &M){
    getNum(i, "First index: ", 1, M.lines);
    getNum(j, "Second index: ", 1, M.rows);
    getNum(num, "Value: ", INT_MIN, INT_MAX);
    i--;
    j--;
}
bool testMatrix(const matrix &M){
    if (M.mass){
        return false;
    }
    cout <<endl<<"Zero matrix!"<<endl;
    return true;
}

void buildMatrix(matrix &M){
    int i, j, num; //A[i][j] = num
    line head1 = {-1, nullptr, nullptr}, *tmp1 = nullptr;
    point head2{nullptr, 0, -1}, *tmp2 = nullptr;

    cout <<"Enter Matrix" <<endl <<"You can rewrite points!" <<endl
        <<"*** Enter 0 in Value to end. ***"<<endl;
    getPoint(i, j, num, M);
    while (num != 0){
        tmp1 = giveSmth<line>(head1, i);
        head2.next = tmp1->el;
        tmp2 = giveSmth<point>(head2, j);
        tmp2->info = num;
        tmp1->el = head2.next;
        getPoint(i, j, num, M);
    }
    M.mass = head1.next;
}
void buildVector(const matrix &M, double *V){
    int S, Max, Min, i = 0, j;
    line *tmp1 = M.mass;
    point *tmp2;
    if(testMatrix(M)){ //Zero matrix
        return;
    }
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
        if (Max == 0)
            throw "Division by zero!";
        V[i] = static_cast<double>(S) / Max;
        tmp1 = tmp1->next;
        ++i;
    }
    if (i < M.lines - 1){
        throw "Division by zero!";
    }
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
