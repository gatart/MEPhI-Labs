#ifndef BIG_DEC_H
#define BIG_DEC_H
#include <iostream>

using namespace std;


class BigDec
{
private:
    /// pointer to massive of digits (uses codes 0 to 9, not signs '0' to '9') | don't have '\0'
    char *num;
    /// length of number without sign
    int length;

    /// for ariphmetic operations adding zeros before meaning numbers
    const BigDec enlarge(const int &length)const;
    /// enlarging if overflow | true - positive, false - negative
    void overflow(bool flag);
    /// delete useless 0
    void correction(char* a);
    /// num[i] = 9 - num[i] | has CODES from 0 to 9 (not signs '0' to '9') | returns CHAR*!!! | don't have '\0'
    char* operator ~()const;
    ///comparison numbers (-1 - num1 < num2; 0 - num1 == num2; 1 - num1 > num2)
    int comparison(const BigDec& num2)const;

public:
    /// initialization constructor by long int (also default)
    BigDec(const long int set = 0);
    /// initialization constructor by string
    BigDec(const char* set);
    /// copy constructor
    BigDec(const BigDec &a);
    /// moving constructor
    BigDec(BigDec &&a) : num(a.num), length(a.length){
        a.num = nullptr;
    }
    /// destructor
    ~BigDec();

    /// output of a number
    friend std::ostream& operator <<(std::ostream& out, const BigDec& a);

    /// input of a number
    friend std::istream& operator >>(std::istream& in, BigDec& a);

    /// addition (also work with long int, char* or string.c_str())
    friend BigDec operator +(const BigDec &num1, const BigDec &num2);

    /// subtraction (also work with long int, char* or string.c_str())
    friend BigDec operator -(const BigDec &num1, const BigDec &num2);

    /// changeSign
    const BigDec operator - () const;

    /// assignment operator
    BigDec& operator =(const BigDec &num2);

    /// move assignment operator
    BigDec& operator=(BigDec&& num2);

    ///returns a digit of the i category, i = 0 returns sign (1 - minus, 0 - plus)
    int operator[](int i);

    /// decimal bitwise shift to the left on i bits
    BigDec operator >>(const int i)const;

    ///decimal bitwise shift to the right on i bits | don't care about the least bit
    BigDec operator <<(const int i)const;

    ///convert BigDec to char* with signs '0' to '9' with '-' or '+'
    char* to_string()const;

    ///comparison operators (true or false) | also work with long int, char* or string.c_str()
    friend bool operator>(const BigDec& num1, const BigDec& num2);
    friend bool operator<(const BigDec& num1, const BigDec& num2);
    friend bool operator>=(const BigDec& num1, const BigDec& num2);
    friend bool operator<=(const BigDec& num1, const BigDec& num2);
    friend bool operator==(const BigDec& num1, const BigDec& num2);
    friend bool operator!=(const BigDec& num1, const BigDec& num2);
};

#endif // DEC_INT_H
