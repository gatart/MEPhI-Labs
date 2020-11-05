#ifndef BIG_DEC_H
#define BIG_DEC_H
#include <iostream>

using namespace std;


class BigDec
{
private:
    char *num;
    int length;
    const BigDec enlarge(const int &length)const; //for ariphmetic operations adding 0 before meaning numbers
    void overflow(bool flag); //enlarging if overflow | true - positive, false - negative
    void correction(char* a); //delete useless 0
public:
    BigDec(const long int set = 0); //unsigned long int has less digits that 47
    BigDec(const char* set);

    //BigDec(const BigDec &a); //copy constructor write
    ~BigDec(); //write

    friend std::ostream& operator <<(std::ostream& out, const BigDec& a);
    friend std::istream& operator >>(std::istream& in, BigDec& a);  //check of string in constructor
    BigDec& operator +(const BigDec &num2)const;
    BigDec& operator -(const BigDec &num2)const;
    const BigDec operator - () const; //changeSign
    char* operator ~()const; //num[i] = 9 - num[i]

    BigDec& great10();//V //bitwise shift to the left
    BigDec& less10();//V //bitwise shift to the right | don't care about the least bit

    //BigDec& operator =(const BigDec &num2)const; //make overload
};

#endif // DEC_INT_H
