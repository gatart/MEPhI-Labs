#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

typedef struct point{
    point *next;
    float info;
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
        cin>>a;
    while (!cin.good());
};

void buildMatrix(matrix M);
void generateMatrix(matrix M);
void buildVector(matrix M);
void viewAnswer();


#endif // WORKSPACE_H
