#include "big_dec.h"
#include <cstring>

void BigDec::changeSign(){
    if (num[0] == 1)
        num[0] = 0;
    else
        num[0] = 1;
}

BigDec::BigDec(const long int set){ //unsigned long int has less digits that 47
    int digit;
    long int put = set;
    bool zero = true;
    bool sign = false;
    length = 0;

    if (set < 0){ //findSign
        sign = true;
        put *= -1;
    }

    while (put != 0){ //counting length
        ++length;
        zero = false;
        put /= 10;
    }

    if (zero){ //num = 0
        length = 1;
        num = new char [2];
        num[0] = 0;
        num[1] = 0;
        return;
    }

    num = new char[static_cast<size_t>(length + 1)];

    if (sign){ //setSign
        num[0] = 1;
        put = -set;
    }else{
        num[0] = 0;
        put = set;
    }

    int i = length;
    while (put != 0){ //copy number from the end
        digit = put % 10;
        put /= 10;
        num[i--] = static_cast<char>(digit);
    }

}

BigDec::BigDec(const char *set){
    int end = 1; //end changes for +228 and 228(no sign)
    int len = static_cast<int>(strlen(set));

    if (len < 1){ //empty string
        throw invalid_argument("Too short string");
    }
    if (set[0] != '+' && set[0] != '-'){ //normal sign?
        if (set[0] < '0' || set[0] > '9')
            throw invalid_argument("Not number");
        end = 0; //with no sign, like 228
    }

    length = static_cast<int>(strlen(set)) - end;
    num = new char[static_cast<size_t>(length + 1)];

    if (set[0] == '-'){ //setSign
        num[0] = 1;
    }else{
        num[0] = 0;
    }

    for (int i = length - 1 + end, k = length; i >= end; --i, --k){
        if (set[i] < '0' || set[i] > '9'){
            delete []num;
            throw invalid_argument("Not number");
        }
        num[k] = set[i] - '0';
    }
}

std::ostream& operator <<(std::ostream& out, const BigDec& a){
    if (a.num[0] == 1 && !(a.length == 1 && a.num[1] == 0)){ //if '-' and not zero
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
    if (flag){
        out <<0;
    }
    return out << dec;
}

std::istream& operator >>(std::istream& in, BigDec& a){
    string input;
    getline(in, input);

    char* name;
    name = new char[input.length() + 1];
    strcpy(name, input.c_str());

    BigDec num(name); //check of string in constructor
    a = num;
    delete[] name;
    input.clear();
    return in;
}

BigDec& BigDec::enlarge(const int &length)const{
    BigDec *ans = new BigDec;
    ans->length = length;
    ans->num = new char[static_cast<size_t>(length + 1)];
    ans->num[0] = this->num[0];

    for (int i = length, k = this->length; i > 0; --i){
        if (k == 0){
            ans->num[i] = 0;
        }else{
            ans->num[i] = this->num[k--];
        }
    }
    return *ans;
}

void BigDec::overflow(bool flag){
    if (flag){ //Sign
        this->num[0] = 0;
    }else{
        this->num[0] = 1;
    }

    cout <<"Overflow: "<<endl;
    char* a;
    a = ~(*this);
    this->num = a;
    cout <<*this <<endl;
    *this = this->enlarge(this->length + 1);
    this->num[1] = 1;
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

BigDec& BigDec::operator +(const BigDec &num2)const{
    char *a, *b;
    int length;

    if (this->length > num2.length){ //get complements with same length
        length = this->length;
        a = ~(*this);
        BigDec tmp;
        tmp = num2.enlarge(length);
        b = ~tmp;
    }else{
        b = ~num2;
        length = num2.length;
        if (this->length < num2.length){
            BigDec tmp;
            tmp = this->enlarge(length);
            a = ~tmp;
        }else{
            a = ~(*this);
        }
    }

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

    for (int i = length; i >= 0; --i){
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

    BigDec *ans = new BigDec;
    ans->length = length;
    ans->num = a;
    if (a[0] == 1 && overflow == 1){ //positive overflow
        ans->overflow(true);
    }else{
        if (a[0] == 0 && overflow == 2){ //negative overflow
            ans->overflow(false);
        }else{ //normal
            a = ~(*ans);
            ans->num = a;
        }
    }

    return *ans;
}

BigDec& BigDec::operator -(const BigDec &num2)const{
    BigDec ans = num2;
    ans.changeSign(); //just change sign of second number and add it to first
    return *this + ans;
}

BigDec& BigDec::great10(){
    BigDec *ans = new BigDec;

    if (this->length == 1 && this->num[1] == 0){ //zero
        ans->length = 1;
        ans->num = new char[1];
        ans->num[1] = 0;
        return *ans;
    }

    ans->length = length + 1;
    ans->num = new char[static_cast<size_t>(length + 2)];

    ans->num[0] = num[0];
    for (int i = 1; i <= length; ++i)
        ans->num[i] = num[i];
    ans->num[ans->length] = 0;
    return *ans;
}

BigDec& BigDec::less10(){ //don't care about the least bit
    BigDec *ans = new BigDec;

    if (this->length == 1 && this->num[1] == 0){ //zero
        ans->length = 1;
        ans->num = new char[1];
        ans->num[1] = 0;
        return *ans;
    }

    ans->length = length - 1;
    ans->num = new char[static_cast<size_t>(length)];

    ans->num[0] = num[0];
    for (int i = 1; i <= ans->length; ++i)
        ans->num[i] = num[i];
    return *ans;
}

BigDec::~BigDec() = default;
