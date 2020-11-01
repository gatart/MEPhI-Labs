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
    void getComplement(const char num[N + 1], const int &length, char place[N + 1]); //num[i] = 9 - num[i]
public:
    BigDec(long int set = 0); //unsigned long int has less digits that 47
    BigDec(char* set);
    ~BigDec(); //default
    ostream& print(ostream &out); //cout of BigDec
    istream& input(istream &in); //cin of BigDec | check of string in constructor
    BigDec& add(const BigDec &num2);
    BigDec& sub(const BigDec &num2);
    BigDec& great10(); //bitwise shift to the left
    BigDec& less10(); //bitwise shift to the right | don't care about the least bit

};

#endif // DEC_INT_H
