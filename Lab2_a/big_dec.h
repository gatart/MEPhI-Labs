#ifndef BIG_DEC_H
#define BIG_DEC_H
#include <iostream>

using namespace std;

const int N = 47;

class BigDec
{
private:
    unsigned char num[48];
    const int length = 47;
public:
    BigDec(long int set = 0);
    BigDec(char* set);
    ~BigDec();
    ostream& print(); //need overload
    istream& input(istream &in); //need overload
    void getComplement(); //need overload
    BigDec add(); //need overload
    BigDec sub(); //need overload
    void great10();
    void less10();

};

#endif // DEC_INT_H
