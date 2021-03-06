## TemplateMap   
### Описание   
Контейнерный класс с небольшим количеством методов, достаточных для реализации Варианта 11 по лабораторной.   
Является сильнообрезанной версией `std::map`   

### Итераторы     
#### Класс iterator методы   
##### Конструктор итератора.    
`iterator()`    
Инициализирует его значением `nullptr`   


##### Копирующий оператор   
`iterator& operator=(const iterator&)`   



##### Инкремент итератора    
`iterator& operator++()`   
Меняет значение итератора на элемент следующий, после элемента внутри итератора.   
Если итератор указывал на самый крайний элемент - переходит на элемент со значением `nullptr`   


##### Оператор взятия значения по адресу   
`std::pair<Key, T>& operator*() const`   
Возвращает ссылку на пару ключ-значение, на которые указывал итератор.   


##### Оператор обращения по указателю   
`std::pair<Key, T>* operator->() const`   
Возвращает указатель на пару ключ-значение, на которые указывал итератор.   


##### Оператор сравнения равенство   
`bool operator==(iterator other) const`   
Возвращает `true`, если итераторы указывают на одну и ту же пару в мапе, иначе - `false`.   


##### Оператор сравнения неравенство   
`bool operator!=(iterator other) const`   
Возвращает `false`, если итераторы указывают на одну и ту же пару в мапе, иначе - `true`.   


### Методы класса `TemplateMap`   
#### Конструктор    
TemplateMap()    
Устанавливает размер равынй `0` и пустой контейнер.


#### Первый элемент    
iterator begin()    
Возвращает итератор указывающий на первый элемент мапы    


#### Конец мапы    
iterator end()    
Возвращает итератор указывающий на nullptr (самый последний элемент)   


#### Размер мапы    
size_t size()    
Возвращает текущее количество элементов в мапе


#### Найти элемент    
iterator find(Key key)     
Возвращает итератор указывающий на элемент, который находят по его ключу. В случае отсутствия такового возвращает nullptr


#### Освободить мапу    
void clear()    
Удаляет все элементы из мапы, устанавливает значение размера `0` и пустой контейнер


#### Добавить элемент в мапу      
void insert(Key key, T value)     
Добавляет в контейнер новый элемент по его ключу и значению. Если в мапе уже есть элемент с таким ключом, выбрасывает исключение `logic_error`


#### Извле элемент из мапы    
size_t erase(Key key)    
Удаляет указанный элемент по его ключу. В случае успешного удаления возвращает `0`, иначе `1`
