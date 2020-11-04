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
    BigDec& enlarge(const int &length)const; //for ariphmetic operations adding 0 before meaning numbers
    void overflow(bool flag); //enlarging if overflow | true - positive, false - negative
public:
    BigDec(const long int set = 0);//V //unsigned long int has less digits that 47
    BigDec(const char* set); //V

    //BigDec(const BigDec &a); //copy constructor write
    ~BigDec(); //write

    BigDec& operator +(const BigDec &num2)const;
    BigDec& operator -(const BigDec &num2)const;//V
    char* operator ~()const;//V //num[i] = 9 - num[i]
    friend std::ostream& operator <<(std::ostream& out, const BigDec& a); //V
    friend std::istream& operator >>(std::istream& in, BigDec& a); //V //check of string in constructor
    BigDec& great10();//V //bitwise shift to the left
    BigDec& less10();//V //bitwise shift to the right | don't care about the least bit

    //BigDec& operator =(const BigDec &num2)const; //make overload
};

#endif // DEC_INT_H
