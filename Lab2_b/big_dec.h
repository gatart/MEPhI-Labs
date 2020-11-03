#ifndef BIG_DEC_H
#define BIG_DEC_H
#include <iostream>

using namespace std;

const int N = 47;

class BigDec
{
private:
    char num[48]; //contains chars with CODES from 0 to 9 | 1 = '-' | 0 = '+'
    int length = N;
    void changeSign();
public:
    BigDec(long int set = 0); //unsigned long int has less digits that 47
    BigDec(const char* set);
    ~BigDec(); //default
    BigDec& operator +(const BigDec &num2)const;
    BigDec& operator -(const BigDec &num2)const;
    char* operator ~()const; //num[i] = 9 - num[i]
    friend std::ostream& operator <<(std::ostream& out, const BigDec& a);
    friend std::istream& operator >>(std::istream& in, BigDec& a); //check of string in constructor
    BigDec& great10(); //bitwise shift to the left
    BigDec& less10(); //bitwise shift to the right | don't care about the least bit

};

#endif // DEC_INT_H
