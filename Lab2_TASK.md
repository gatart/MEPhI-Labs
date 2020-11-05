Вариант 1

1. Разработать класс "большое десятичное число" в соответствии со следующим заданием:

Состояние класса -

Целое число определяется его длиной (количество цифр в числе, например, до 47) и массивом значений десятичных цифр (типа char). Число со знаком хранится в прямом коде. При выполнении арифметических операций использовать дополнительный код. Память под массив выделяется стати-чески, во время компиляции, и задается массивом фиксированного предельного размера.

Протокол класса -

Определяет  возможности создания и инициализации экземпляров класса и правила их исполь-зования (методы класса).

Предусмотреть следующие возможности:

• пустой конструктор для инициализации экземпляров и массивов экземпляров класса по умолчанию;

• создание экземпляров класса с инициализацией значением целого длинного (типа long);

• создание экземпляров класса с инициализацией значением числа как строки символов;

• ввод экземпляров класса из входного потока и вывод их значений в выходной поток 

(с помощью перегруженных операторов >> и << );

• получение дополнительного кода числа ((*) с помощью перегруженного оператора ~ );

• выполнение операций сложения и вычитания чисел с учетом знаков чисел (с помощью пе-регруженных операторов + и - );

• выполнение операции “уменьшения числа в десять раз” (деление на 10 нацело);

• выполнение операции “увеличения числа в десять раз”.

2. Проектирование класса рекомендуется начать с представления состояния класса, учитываю-щего заданные операции, а затем реализации конструкторов и перегруженного оператора вывода. Для отладки и исчерпывающего тестирования других методов разработанного класса реализовать диалоговую программу, которая позволяет вводить параметры, отлаживаемых методов. Для обра-ботки ошибочных ситуаций использовать механизм исключительных ситуаций.

3. Повторить разработку класса при условии, что память под массив необходимой длины вы-деляется динамически, во время выполнения программы (с помощью оператора new; память задает-ся указателем на char в состоянии класса).

Дополнить интерфейс класса следующими возможностями:

• создание экземпляра класса с его инициализацией другим экземпляром класса (копирую-щий конструктор);

• переопределение экземпляра класса (с помощью перегруженного оператора присваива-ния).

 4. Написать прикладную программу, использующую разработанный класс.