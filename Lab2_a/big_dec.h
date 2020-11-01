#ifndef BIG_DEC_H
#define BIG_DEC_H
#include <iostream>

using namespace std;

const int N = 47;

class BigDec
{
private:
    char num[48];
    int length = N;

public:
    void changeSign();
    BigDec(long int set = 0);
    BigDec(char* set);
    ~BigDec();
    ostream& print(ostream &out); //need overload
    istream& input(istream &in); //need overload
    void getComplement(const char num[N + 1], const int &length, char place[N + 1]); //need overload
    BigDec& add(const BigDec &num2); //need overload
    BigDec& sub(const BigDec &num2); //need overload
    void great10();
    void less10();

};

#endif // DEC_INT_H
