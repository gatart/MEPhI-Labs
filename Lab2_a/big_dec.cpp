#include "big_dec.h"
#include <cstring>

BigDec::BigDec(long int set) //unsigned long int has less digits that 47
{
    int digit, i = length;
    for(unsigned char &c : num)
        c = 0;

    while (set != 0){
        digit = set % 10;
        set /= 10;
        num[i--] = static_cast<unsigned char>(digit);
    }

}

BigDec::BigDec(char *set){

}

ostream& BigDec::print(){

}

istream& BigDec::input(istream &in){
    char name[49];
        in.getline(name, 48);
        if (in.fail()) {
             in.clear();
             in.ignore(32767, '\n');
             throw invalid_argument("Wrong string");
        }
        BigDec num(name);
        *this = num;
        return in;
}

void BigDec::getComplement(){

}

BigDec BigDec::add(){

}

BigDec BigDec::sub(){

}

void BigDec::great10(){

}

void BigDec::less10(){

}

BigDec::~BigDec() = default;
