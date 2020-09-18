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

void buildMatrix(matrix &M);
void generateMatrix(matrix &M);
bool buildVector(matrix M, double *V);
void viewAnswer(matrix M, double *V);
void cleanData(matrix &M, double *V);


#endif // WORKSPACE_H
