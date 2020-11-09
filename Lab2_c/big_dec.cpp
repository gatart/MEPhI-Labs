#include "big_dec.h"
#include <cstring>


BigDec::BigDec(const long int set){
    int digit;
    long int put = set;
    bool zero = true;
    bool sign = false;
    length = 0;

    if (set < 0){
        sign = true;
        put *= -1;
    }

    while (put != 0){
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
    if (sign){
        num[0] = 1;
        put = -set;
    }else{
        num[0] = 0;
        put = set;
    }

    int i = length;
    while (put != 0){
        digit = put % 10;
        put /= 10;
        num[i--] = static_cast<char>(digit);
    }
}

BigDec::BigDec(const char *set){
    if (set == nullptr){
        throw invalid_argument("Initialization by nullptr");
    }
    int beg = 1; //beg changes for +228 and 228(no sign)
    int len = static_cast<int>(strlen(set));

    if (len < 1){ //empty string
        throw invalid_argument("Too short string");
    }
    if (set[0] != '+' && set[0] != '-'){
        if (set[0] < '0' || set[0] > '9')
            throw invalid_argument("Not number");
        beg = 0; //with no sign, like 228
    }

    length = static_cast<int>(strlen(set)) - beg;
    num = new char[static_cast<size_t>(length + 1)];

    if (set[0] == '-'){
        num[0] = 1;
    }else{
        num[0] = 0;
    }

    bool zero = true; //if number is 0 | don't copy useless 0
    int no_need = 0;
    for (int i = beg, k = 1; i <= length - 1 + beg; ++i, ++k){
        if (set[i] < '0' || set[i] > '9'){
            delete []num;
            throw invalid_argument("Not number");
        }else{
            if (!zero || set[i] != '0'){ //useful digits
                num[k] = set[i] - '0';
                zero = false;
            }else{ //useless 0
                ++no_need;
            }
        }
    }

    if (zero){
        char* tmp = new char[2];
        delete[]num;
        num = tmp;
        num[0] = 0;
        num[1] = 0;
        length = 1;
    }else{
        if (no_need != 0){ //has useless 0
            length = length - no_need;
            char* tmp = new char[static_cast<size_t>(length + 1)];
            tmp[0] = num[0];
            for (int i = 1; i <= length; ++i){
                tmp[i] = num[i + no_need];
            }
            delete[] num;
            num = tmp;
        }
    }
}

BigDec::BigDec(const BigDec &a){
    try {
        this->length = a.length;
        num = new char[static_cast<size_t>(length + 1)];
        for (int i = 0; i <= length; i++)
            num[i] = a.num[i];
    }catch (...) {
        cout << "Empty initialization!";
        length = 1;
        num = new char[2];
        num[0] = num[1] = 0;
    }
}

BigDec::~BigDec(){
    delete[]num;
}

const BigDec BigDec::enlarge(const int &length)const{
    BigDec ans;
    char* tmp = new char[static_cast<size_t>(length + 1)];
    delete[]ans.num;
    ans.length = length;
    ans.num = tmp;
    ans.num[0] = this->num[0];

    for (int i = length, k = this->length; i > 0; --i){
        if (k == 0){
            ans.num[i] = 0;
        }else{
            ans.num[i] = this->num[k--];
        }
    }
    return ans;
}

void BigDec::overflow(bool flag){
    if (flag){ //Sign
        this->num[0] = 0;
    }else{
        this->num[0] = 1;
    }

    char* a;
    a = ~(*this);
    delete[]this->num;
    this->num = a;
    if(!flag){
        this->num[0] = 1;
    }
    *this = this->enlarge(this->length + 1);
    this->num[1] = 1;
}

void BigDec::correction(char *a){
    int no_need = 0;
    for (int i = 1; i <= length; ++i){ //count useless 0
        if (a[i] != 0){
            break;
        }
        ++no_need;
    }

    if (no_need == length){ //all 0
        no_need = length - 1;
        a[0] = 0;
    }
    if (no_need == 0){ //no useless
        delete[]num;
        num = a;
        return;
    }
    char* tmp = new char[static_cast<size_t>(length - no_need + 1)];
    tmp[0] = a[0];
    for (int i = 1; i <= length - no_need; ++i){
        tmp[i] = a[i + no_need];
    }
    delete[]a;
    delete[]num;
    length = length - no_need;
    num = tmp;
}

int BigDec::comparison(const BigDec &num2) const{
    int sign = static_cast<int>(this->num[0] + num2.num[0]);
    int len = length - num2.length;

    if (sign != 1){
        if ((len > 0 && sign == 0) || (len < 0 && sign == 2)){
            return 1;
        }else if ((len < 0 && sign == 0) || (len > 0 && sign == 2)){
            return -1;
        }
    }else{ //different signs
        if (num[0] > num2.num[0]){
            return -1;
        }else return 1;
    }

    for (int i = 1, len = 0; i <= length; ++i){
        len = static_cast<int>(this->num[i] - num2.num[i]);
        if(len != 0){
            break;
        }
    }
    if ((len > 0 && sign == 0) || (len < 0 && sign == 2)){
        return 1;
    }else if (len == 0){
        return 0;
    }else return -1;
}

char* BigDec::operator ~()const{
    char * place = new char [static_cast<size_t>(length + 1)];
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
    if (flag){ // negative zero change to zero
        place[0] = 0;
    }
    return place;
}

std::ostream& operator <<(std::ostream& out, const BigDec& a){
    if (a.num[0] == 1 && !(a.length == 1 && a.num[1] == 0)){ //if '-' and not zero
        out <<'-';
    }

    for (int i = 1; i <= a.length; ++i){
        out<<static_cast<unsigned int>(a.num[i]);
    }
    return out << dec;
}

std::istream& operator >>(std::istream& in, BigDec& a){
    string input;
    getline(in, input);
    char* name = new char[input.length() + 1];
    strcpy(name, input.c_str());

    BigDec num(name); //check of string in constructor
    a = num;
    delete[] name;
    input.clear();
    return in;
}

BigDec operator +(const BigDec &num1, const BigDec &num2){
    char *a, *b;
    int length;

    if (num1.length > num2.length){ //get complements with same length
        length = num1.length;
        a = ~(num1);
        BigDec tmp;
        tmp = num2.enlarge(length);
        b = ~tmp;
    }else{
        b = ~num2;
        length = num2.length;
        if (num1.length < num2.length){
            BigDec tmp;
            tmp = num1.enlarge(length);
            a = ~tmp;
        }else{
            a = ~(num1);
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

    delete[]b;
    BigDec ans;
    delete[]ans.num;
    ans.length = length;
    ans.num = a;
    if (a[0] == 3){ //two negative numbers which sum don't get overflow
        bool flag = true;
        for (int i = 1; i <= length; ++i){
            if(a[i] != 0){
                flag = false;
                break;
            }
        }
        if (flag){ //all 0 and 1 to next bit
            ans.overflow(false);
            return ans;
        }
        a[0] = 1;
    }
    if (a[0] == 2) //overflow or negative number with positive one which was bigger
        a[0] = 0;

    if (a[0] == 1 && overflow == 1){ //positive overflow
        ans.overflow(true);
    }else{
        if (a[0] == 0 && overflow == 2){ //negative overflow
            ans.overflow(false);
        }else{ //normal
            a = ~(ans);
            ans.correction(a);
        }
    }

    return ans;
}

BigDec operator -(const BigDec &num1, const BigDec &num2){
    return num1 + (-num2);
}

const BigDec BigDec::operator - () const {
        BigDec res(*this);
        if (length == 1 && num[1] == 0){ // zero
            return *this;
        }
        res.num[0] = num[0] == 0 ? 1 : 0;
        return res;
}

BigDec& BigDec::operator =(const BigDec &num2){
    if(num != num2.num){
        length = num2.length;
        char* tmp = new char [static_cast<size_t>(length + 1)];
        if (num != nullptr){
            delete[]num;
        }
        num = tmp;
        for (int i = 0; i <= length; ++i){
            num[i] = num2.num[i];
        }
    }
    return *this;
}

BigDec& BigDec::operator=(BigDec&& num2){
    if (num != nullptr){
        delete[]num;
    }
    num = num2.num;
    length = num2.length;
    num2.num = nullptr;
    return *this;
}

int BigDec::operator[](int i){
    if (i < 0 || i > length){
        throw logic_error("Array index out of bounds");
    }
    return static_cast<int>(num[i]);
}

BigDec BigDec::operator<<(const int i)const{
    if (i < 0) throw invalid_argument("Negative shift argument");
    if (i == 0 || (this->length == 1 && this->num[1] == 0)) return *this;

    BigDec ans;
    char* tmp = new char[static_cast<size_t>(length + i + 1)];
    delete[]ans.num;
    ans.length = length + i;
    ans.num = tmp;
    ans.num[0] = num[0];
    for (int i = 1; i <= length; ++i){
        ans.num[i] = num[i];
    }
    for (int i = length + 1; i <= ans.length; ++i){
        ans.num[i] = 0;
    }
    return ans;
}

BigDec BigDec::operator>>(const int i)const{
    if (i < 0) throw invalid_argument("Negative shift argument");
    if (i == 0 || (this->length == 1 && this->num[1] == 0)) return *this;

    BigDec ans;
    if (i >= length) return ans;
    ans.length = length - i;
    char* tmp = new char[static_cast<size_t>(ans.length + 1)];
    delete[]ans.num;
    ans.num = tmp;
    ans.num[0] = num[0];
    for (int i = 1; i <= ans.length; ++i)
        ans.num[i] = num[i];
    return ans;
}

char* BigDec::to_string() const{
    char* ans = new char[static_cast<size_t>(length + 2)];

    if (num[0] == 1){
        ans[0] = '-';
    }else{
        ans[0] = '+';
    }

    for (int i = 1; i <= length; ++i){
        ans[i] = num[i] + '0';
    }
    ans[length + 1] = '\0';
    return ans;
}

bool operator>(const BigDec& num1, const BigDec& num2){
    if (num1.comparison(num2) > 0){
        return true;
    }
    return false;
}

bool operator<(const BigDec& num1, const BigDec& num2){
    if (num1.comparison(num2) < 0){
        return true;
    }
    return false;
}

bool operator>=(const BigDec& num1, const BigDec& num2){
    return !(num1 < num2);
}

bool operator<=(const BigDec& num1, const BigDec& num2){
    return !(num1 > num2);
}

bool operator==(const BigDec& num1, const BigDec& num2){
    if (num1.comparison(num2) == 0){
        return true;
    }
    return false;
}

bool operator!=(const BigDec& num1, const BigDec& num2){
    return !(num1 == num2);
}
