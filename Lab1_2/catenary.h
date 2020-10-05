#ifndef CATENARY_H
#define CATENARY_H


class Catenary {
private:
   long double m_a;
public:
   Catenary();
   Catenary(const long double &A);
   void setParam(const long double &newA);
   long double findY(const long double &x);
   long double findLength(const long double &x1, const long double &x2);
   long double findR(const long double &x);
   long double findOr(const long double &x);
   long double findS(const long double &x1, const long double &x2);
};

#endif // CATENARY_H
