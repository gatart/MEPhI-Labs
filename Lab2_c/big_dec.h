#ifndef BIG_DEC_H
#define BIG_DEC_H
#include <iostream>

using namespace std;


class BigDec
{
private:
    char *num; //has CODES from 0 to 9 (not '0' to '9')
    int length;
    const BigDec enlarge(const int &length)const; //for ariphmetic operations adding zeros before meaning numbers
    void overflow(bool flag); //enlarging if overflow | true - positive, false - negative
    void correction(char* a); //delete useless 0
public:
    BigDec(const long int set = 0);
    BigDec(const char* set);
    BigDec(const BigDec &a);
    ~BigDec();

    friend std::ostream& operator <<(std::ostream& out, const BigDec& a);
    friend std::istream& operator >>(std::istream& in, BigDec& a);  //check of string in constructor

    BigDec& operator =(const BigDec &num2);
    BigDec& operator=(BigDec&& num2);
    BigDec& operator +(const BigDec &num2)const;
    BigDec& operator -(const BigDec &num2)const;
    const BigDec operator - () const; //changeSign
    char* operator ~()const; //num[i] = 9 - num[i] | has CODES from 0 to 9 (not '0' to '9') | returns CHAR*!!!

    BigDec& great10(); //bitwise shift to the left
    BigDec& less10(); //bitwise shift to the right | don't care about the least bit
};

#endif // DEC_INT_H
