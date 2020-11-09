#include "big_dec.h"
#include <cstring>

void BigDec::changeSign(){
    if (num[0] == 1)
        num[0] = 0;
    else
        num[0] = 1;
}

BigDec::BigDec(long int set){ //unsigned long int has less digits that 47
    int digit, i = length;
    for(char &c : num)
        c = 0;

    if (set < 0){ //setSign
        num[0] = 1;
        set *= -1;
    }

    while (set != 0){ //copy number from the end
        digit = set % 10;
        set /= 10;
        num[i--] = static_cast<char>(digit);
    }

}

BigDec::BigDec(const char *set){
    int end = 1, len = static_cast<int>(strlen(set)); //end changes for +228 and 228(no sign)
    for(char &c : num)
        c = 0;

    if (len < 1){
        throw invalid_argument("Too short string");
    }
    if (len == 1 && (set[0] < '0' || set[0] > '9')){ //only sign
        throw invalid_argument("Not number");
    }

    if (set[0] != '+' && set[0] != '-'){ //normal sign?
        if (set[0] < '0' || set[0] > '9')
            throw invalid_argument("Not number");
        if (len >= 48) //to long number without sign
            throw logic_error("Number Overflow");
        end = 0;
    }

    if (len > 48)
        throw logic_error("Number Overflow");

    if (set[0] == '-')
        num[0] = 1;
    else
        num[0] = 0;

    for (int i = len - 1, k = length; i >= end; --i, --k){
        if (set[i] < '0' || set[i] > '9')
            throw invalid_argument("Not number");
        num[k] = set[i] - '0';
    }
}

std::ostream& operator <<(std::ostream& out, const BigDec& a){
    bool zero = true;
    for (int i = 1; i <= a.length; ++i){ //zero?
        if (a.num[i] != 0)
            zero = false;
    }
    if (zero){ //zero
        out <<0;
        return out << dec;
    }
    if (a.num[0] == 1 && !zero){ //if '-' and not zero
        out <<'-';
    }
    bool flag = true; //flag for useless zeros
    for (int i = 1; i <= a.length; ++i){
        if (flag){ //skip useless zeros
            if (a.num[i] == 0)
                continue;
            else
                flag = false;
        }
        out<<static_cast<unsigned int>(a.num[i]);
    }
    return out << dec;
}

std::istream& operator >>(std::istream& in, BigDec& a){
    char name[N + 2];
    in.getline(name, N + 2);
    if (in.fail()) {
        in.clear();
        in.ignore(32767, '\n');
        throw invalid_argument("Wrong string");
    }

    BigDec num(name); //check of string in constructor
    a = num;
    return in;
}

char* BigDec::operator ~()const{
    char * place = new char [static_cast<size_t>(this->length + 1)];
    if (num[0] == 0){ //positive number
        for (int i = 0; i <= length; ++i)
            place[i] = num[i];
        return place;
    }

    bool flag = true; //negative number
    place[0] = 1;
    for (int i = length; i > 0; --i){
        place[i] = 9 - num[i]; //analog of binare inversion
        if (flag){ //flag of adding 1 to bite
            place[i] += 1;
            flag = false;
            if (place[i] == 10){
                place[i] = 0;
                flag = true;
            }
        }
    }
    if (flag) // negative zero change to zero
        place[0] = 0;
    return place;
}

BigDec operator +(const BigDec &num1, const BigDec &num2){
    char *a, *b;
    a = ~(num1);
    b = ~num2;
    bool flag = false; //flag of adding 1 to bite
    int overflow;
    if (a[0] == 0 && b[0] == 0)
        overflow = 1;
    else {
        if (a[0] == 1 && b[0] == 1)
            overflow = 2;
        else {
            overflow = 0;
        }
    }

    for (int i = num1.length; i >= 0; --i){
        a[i] = a[i] + b[i];
        if (flag){
            a[i] += 1;
            flag = false;
        }
        if (a[i] > 9){ //1 to next bite
            a[i] -= 10;
            flag = true;
        }
    }

    if (a[0] == 3) //two negative numbers which sum don't get overflow
        a[0] = 1;
    if (a[0] == 2) //overflow or negative number with positive one which was bigger
        a[0] = 0;
    if (a[0] == 1 && overflow == 1)
        throw logic_error("Positive Overflow");
    if (a[0] == 0 && overflow == 2)
        throw logic_error("Negative Overflow");
    BigDec ans;
    for (int i = 0; i <= num1.length; ++i){
        ans.num[i] = a[i];
    }
    delete[]a;
    a = ~(ans);
    for (int i = 0; i <= num1.length; ++i){
        ans.num[i] = a[i];
    }
    delete[]a;
    delete[]b;
    return ans;
}

BigDec operator -(const BigDec &num1, const BigDec &num2){
    BigDec ans = num2;
    ans.changeSign(); //just change sign of second number and add it to first
    return num1 + ans;
}

const BigDec BigDec::great10(){
    if (num[1] != 0) //lost of the greatest bit
        throw logic_error("Number Overflow");

    BigDec ans;
    ans.num[0] = num[0];
    for (int i = 1; i < length; ++i)
        ans.num[i] = num[i + 1];
    ans.num[length] = 0;
    return ans;
}

const BigDec BigDec::less10(){ //don't care about the least bit
    BigDec ans;
    ans.num[0] = num[0];
    for (int i = length; i > 1; --i)
        ans.num[i] = num[i - 1];
    ans.num[1] = 0;
    return ans;
}

BigDec::~BigDec() = default;
