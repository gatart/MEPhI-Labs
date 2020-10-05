#ifndef CATENARY_H
#define CATENARY_H


class Catenary {
private:
   long double m_a;
public:
   Catenary(); // Need a question!
   //Catenary(const long double &A); //Why use of default "const long double &A = 1" doesn't work????
   void setParam(const long double &newA);
   long double findY(const long double &x);
   long double findLength(const long double &x1, const long double &x2);
   long double findR(const long double &x);
   long double findOr(const long double &x);
   long double findS(const long double &x1, const long double &x2);
};

#endif // CATENARY_H
