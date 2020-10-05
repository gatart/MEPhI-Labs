#include <cmath>
#include "catenary.h"


Catenary::Catenary(){
    m_a = 1;
}

/*Catenary::Catenary(const long double &A){
    cout<<"constr"<<endl<<A<<endl;
    m_a = A;
    cout<<m_a<<endl;
}
*/

void Catenary::setParam(const long double &newA){
    m_a = newA;
}

long double Catenary::findY(const long double & x){ //A * ch(x / A)
    long double y;
    y = m_a * coshl(x / m_a);
    return y;
}

long double Catenary::findLength(const long double &x1, const long double &x2){ // |A *(sh(x2/A) - sh(x1/A))|
    long double l;
    l = fabsl(m_a * (sinhl(x2 / m_a) - sinhl(x1 / m_a)));
    return l;
}

long double Catenary::findR(const long double &x){ // A * ch(x/A)^2
    long double R;
    R = findY(x);
    R *= R / m_a;
    return R;
}

long double Catenary::findOr(const long double &x){ // sqrt(R(x)^2 - x^2) + y(x)
    long double y;
    y = findR(x);
    y = sqrtl((y + x) * (y - x)) + findY(x);
    return y;
}

long double Catenary::findS(const long double &x1, const long double &x2){ //  |(A^2)*(sh(x2/A) - sh(x1/A))|
    long double S;
    S = fabsl(m_a * m_a * (sinhl(x2 / m_a) - sinhl(x1 / m_a)));
    return S;
}
