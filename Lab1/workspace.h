#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <iostream>
#include <stdlib.h> //For exiting

using std::cin;
using std::cout;
using std::endl;

typedef struct point{
    point *next = nullptr;
    int info;
    int key;
}point;
typedef struct line{
    int key;
    point *el;
    line *next = nullptr;
}line;
typedef struct matrix{
    line *mass;
    int lines;
    int rows;
}matrix;

template <class T>
void getNum (T & a){
    do
        cin>>a; //can be bad alloc
    while (!cin.good());
}
void getSize(matrix &M, std::string L);
template <class T>
T* loccMem(bool &flag){
    T* tmp;
    try {
        tmp = new T;
    } catch (std::bad_alloc& ba) {
        cout <<ba.what()<<endl;
        flag = true;
        return nullptr;
    }
    flag = false;
    return tmp;
}

bool buildMatrix(matrix &M);
bool buildVector(const matrix &M, double *V);

void viewMatrix(const matrix &M);
void viewVector(double *V, int Lines);

void cleanMatrix(matrix &M);
void cleanData(matrix &M, double *V);
void cleanVector(double *V);

#endif // WORKSPACE_H
