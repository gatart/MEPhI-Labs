#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::istream;

typedef struct point{
    point *next = nullptr;
    int info;
    int key;
}point;
typedef struct line{
    int key;
    point *el = nullptr;
    line *next = nullptr;
}line;
typedef struct matrix{
    line *mass;
    int lines;
    int rows;
}matrix;

void getNum(matrix &M, std::string L);
void getPoint(int &i, int &j, int &num, const matrix &M);
template <class T>
T* loccMem(int num){ //Just for adding 1 class to project!!! I know that can use new without this function.
    T* tmp;
    tmp = new T[num];
    return tmp;
}
template<class T>
T *giveSmth(T & head, const int &i){ //gives line or point
    T *last = nullptr, *tmp = &head;
    while(tmp){
        if (tmp->key == i){ //Find
            return tmp;
        }
        if (tmp->key > i){ //Place between
            last->next = nullptr;
            last->next = loccMem<T>(1);
            last = last->next;
            last->next = tmp;
            last->key = i;
            return last;
        }
        last = tmp;
        tmp = tmp->next;
    }
    last->next = loccMem<T>(1); //place in the end
    tmp = last->next;
    tmp->key = i;
    return tmp;
};

void buildMatrix(matrix &M);
void buildVector(const matrix &M, double *V);
void testMatrix(const matrix M);

void viewMatrix(const matrix &M);
void viewVector(double *V, int Lines);

void cleanMatrix(matrix &M);
void cleanData(matrix &M, double *V);
void cleanVector(double *V);

#endif // WORKSPACE_H
