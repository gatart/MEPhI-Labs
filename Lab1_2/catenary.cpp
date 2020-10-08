#include <iostream>
#include <cmath>
#include "catenary.h"


Catenary::Catenary(){
    m_a = 1;
}

Catenary::Catenary(const double &A){
    setParam(A);
}


void Catenary::setParam(const double &newA){
    if (newA <= 0){
        throw std::invalid_argument("Invalid parameter");
    }
    m_a = newA;
}

double Catenary::getParam(){
    return m_a;
}

double Catenary::findY(const double & x){ //A * ch(x / A)
    double y;
    y = m_a * cosh(x / m_a);
    return y;
}

double Catenary::findLength(const double &x1, const double &x2){ // |A *(sh(x2/A) - sh(x1/A))|
    double l;
    l = fabs(m_a * (sinh(x2 / m_a) - sinh(x1 / m_a)));
    return l;
}

double Catenary::findR(const double &x){ // A * ch(x/A)^2
    double R;
    R = findY(x);
    R *= R / m_a;
    return R;
}

double Catenary::findOr(const double &x){ // sqrt(R(x)^2 - x^2) + y(x)
    double y;
    y = findR(x);
    y = sqrt((y + x) * (y - x)) + findY(x);
    return y;
}

double Catenary::findS(const double &x1, const double &x2){ //  |(A^2)*(sh(x2/A) - sh(x1/A))|
    double S;
    S = fabs(m_a * m_a * (sinh(x2 / m_a) - sinh(x1 / m_a)));
    return S;
}
