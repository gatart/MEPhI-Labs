# Большое десятичное число, вариант С.
Класс большого целого числа неограниченной длинны. В классе предусмотрено динамическое выделение памяти, а так же 
использована возможность перегрузки операторов.

## Документация
Все следующийе функции и классы распологаются в пространстве имен `bigdec`  
## Заголовочный файл `bigdec.h`
### BidDec
Класс большого целого числа. Описывает целое число, содержащее неограниченное число цифр и знак.
#### Прототип класса:
```c++
class BigDec;
```

#### Конструкторы класса:
`BigDec(const long int set = 0);`  
Конструктор, инициальзирующий большое целое число значением типа `long int`  
Он же по умолчанию. Может вызвать следующие типы исключений:  
[bad_alloc][2]

`BigDec(const char* set);`  
Конструктор, инициализирущий большое целое число из ascii строки. Может вызвать следующие типы исключений:  
[invalid_argument][1], [bad_alloc][2]


#### Методы класса:

`friend std::ostream& operator <<(std::ostream& out, const BigDec& a);`  
Оператор вывода в поток `out`


`friend std::istream& operator >>(std::istream& in, BigDec& a);`  
Метод вводит число из потока `in`  
Может вызвать следующие исключения:  
[invalid_argument][1], [bad_alloc][2]


`friend BigDec operator +(const BigDec &num1, const BigDec &num2);`  
Оператор возвращает экземпляр класса `bigint`, содержащий сумму операндов
Может вызвать следующие типы исключений:  
[bad_alloc][2]


`friend BigDec operator -(const BigDec &num1, const BigDec &num2);`  
Оператор возвращает экземпляр класса `bigint`, содержащий разницу операндов
Может вызвать следующие типы исключений:  
[bad_alloc][2]


`const BigDec operator - () const;`  
Оператор возвращает экземпляр класса `bigint`, противоположный операнду знаком

 
`int operator[](int i);`  
Оператор возвращает символ `i`-го разряда в записи числа (число от 0 до 9, не ASCII код символа)  
При `i = 0` возвращает знак (1 - минус, 0 - плюс). Может вызвать исключение:  
[logic_error][3], если индекс `i` меньше нуля или больше размера числа (без учёта знака)


`BigDec operator >>(const int i)const;`  
Оператор возвращает новый экземпляр, сдвинутый вправо на `a`.  
`a` должно быть положительным числом.  
Может вызвать следующие исключения:  
[bad_alloc][2], [invalid_argument][1], если число `а` меньше нуля  


`BigDec operator <<(const int i)const;`  
Оператор возвращает новый экземпляр, сдвинутый влево на `a`.  
`a` должно быть положительным числом.  
Может вызвать следующие исключения:  
[bad_alloc][2], [invalid_argument][1], если число `а` меньше нуля  


`char* to_string()const;`  
Метод возвращает ascii строку, в которой записано данное число.  
Не рекомендую делать вывод `cin << a.to_string;`, это может привести к утечке памяти.
Может вызвать следующие исключения:  
[bad_alloc][2]

#### Методы для сравнения:
`friend bool operator>(const BigDec& num1, const BigDec& num2);`  

`friend bool operator<(const BigDec& num1, const BigDec& num2);`  

`friend bool operator>=(const BigDec& num1, const BigDec& num2);`  

`friend bool operator<=(const BigDec& num1, const BigDec& num2);`  

`friend bool operator==(const BigDec& num1, const BigDec& num2);`  

`friend bool operator!=(const BigDec& num1, const BigDec& num2);`  

Возвращают `true` или `false`.  

[1]: http://www.cplusplus.com/reference/stdexcept/invalid_argument/
[2]: http://www.cplusplus.com/reference/new/bad_alloc/
[3]: http://www.cplusplus.com/reference/stdexcept/logic_error/
