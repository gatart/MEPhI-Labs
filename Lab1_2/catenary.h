#ifndef CATENARY_H
#define CATENARY_H


class Catenary {
private:
   double m_a;
public:
   Catenary();
   Catenary(const double &A);
   void setParam(const double &newA);
   double getParam();
   double findY(const double &x);
   double findLength(const double &x1, const double &x2);
   double findR(const double &x);
   double findOr(const double &x);
   double findS(const double &x1, const double &x2);
};

#endif // CATENARY_H
