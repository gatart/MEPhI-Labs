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
typedef struct matrix{
    point *mass;
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

bool buildMatrix(matrix &M);
bool buildVector(const matrix &M, double *V);

void viewMatrix(const matrix &M);
void viewVector(double *V, int Lines);

void cleanMatrix(matrix &M);
void cleanData(matrix &M, double *V);
void cleanVector(double *V);

#endif // WORKSPACE_H
