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
    void changeSign();
    void getComplement(const char num[N + 1], const int &length, char place[N + 1]);
public:
    BigDec(long int set = 0);
    BigDec(char* set);
    ~BigDec();
    ostream& print(ostream &out);
    istream& input(istream &in);
    BigDec& add(const BigDec &num2);
    BigDec& sub(const BigDec &num2);
    void great10();
    void less10();

};

#endif // DEC_INT_H
