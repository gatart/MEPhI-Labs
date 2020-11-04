#ifndef BIG_DEC_H
#define BIG_DEC_H
#include <iostream>

using namespace std;

const int N = 47;

class BigDec
{
private:
    //char num[48]; //contains chars with CODES from 0 to 9 | 1 = '-' | 0 = '+'
    //int length = N;
    char *num;
    int length;
    void changeSign();
public:
    BigDec(const long int &set = 0);//V //unsigned long int has less digits that 47
    BigDec(const char* set); //V

    BigDec(const BigDec &a); //copy constructor write
    ~BigDec(); //write

    BigDec& operator +(const BigDec &num2)const;
    BigDec& operator -(const BigDec &num2)const;
    char* operator ~()const; //num[i] = 9 - num[i]
    friend std::ostream& operator <<(std::ostream& out, const BigDec& a);
    friend std::istream& operator >>(std::istream& in, BigDec& a); //check of string in constructor
    BigDec& great10(); //bitwise shift to the left
    BigDec& less10(); //bitwise shift to the right | don't care about the least bit

    BigDec& operator =(const BigDec &num2)const; //make overload
};

#endif // DEC_INT_H
