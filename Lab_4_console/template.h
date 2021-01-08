#ifndef TEMPLATE_H
#define TEMPLATE_H
#include <iostream>
#include <vector>
#include <string>

using std::iterator;
using std::logic_error;
using std::pair;

/*!
    \brief Шаблонный контейнерный класс, для замены std::map.
    \author Gatart
    \version 1.0
    \date Декабрь 2020 года
    \warning Данный класс создан в учебных целях!

    Данный контейнерный класс хранит в себе пары элементов <Ключ, Значение>, такие, что у каждой пары свой индивидуальный ключ.
    Класс является шаблонным, что позволяет использовать его для различных типов данных.
*/

template <class Key, class T>
class TemplateMap {
private:
    std::vector<pair<Key, T>> _data;

public:
    class iterator {        ///< Итератор
    private:
        size_t _pos;
        std::vector<pair<Key, T>>* _vect;

    public:
        iterator();         ///< Конструктор итератора
        /**
         * @brief Копирующий оператор присваивания
         */
        iterator& operator=(const iterator&);

        /**
         * @brief Префиксный инкремент
         * @return Возвращает итератор на следующий элемент
         * @throw std::out_of_range В случае если применить к end()
         */
        iterator& operator++();

        /**
         * @brief Перегруженный оператор взятия значения по адресу
         * @throw std::out_of_range В случае если применить к end()
         * @return Возвращает пару std::pair<Key, T> на которую указывает итератор
         */
        std::pair<Key, T>& operator*() const;
        /**
         * @brief operator ->
         * @return Возвращает указатель на пару std::pair<Key, T> на которую указывает итератор
         */
        std::pair<Key, T>* operator->() const;

        /**
         * @brief operator ==
         * @param other Итератор с которым сравнивают
         * @return
         */
        bool operator==(iterator other) const;
        /**
         * @brief operator !=
         * @param other Итератор с которым сравнивают
         * @return
         */
        bool operator!=(iterator other) const;

        friend class TemplateMap;
    };

    TemplateMap();      ///< Конструктор контейнерного класса
    ~TemplateMap();     ///< Деструктор контейнерного класса
    /**
     * @brief  Итератор на начало контейнера
     * @return Итератор на начало контейнера
     */
    iterator begin();
    /**
     * @brief Итератор на элемент после последнего в контейнере
     * @return Итератор на элемент после последнего в контейнере
     */
    iterator end();
    /**
     * @brief Текущий размер контейнера
     * @return Текущий размер контейнера
     */
    size_t size();
    /**
     * @brief Поиск элемента по ключу
     * @param key Ключ по которому идёт поиск
     * @return Итератор на найденный элемент. Если такового нет - end()
     */
    iterator find(Key key);
    /**
     * @brief Освобождение контейнера
     */
    void clear();
    /**
     * @brief Добавление нового элемента в контейнер
     * @param key Ключ к новому элементу
     * @param value Значение нового элемента
     * @throw std::logic_error В случае если элемент с таким ключём уже присутствует в контейнере
     */
    void insert(Key key, T value);
    /**
     * @brief Удаление элемента из контейнера
     * @param key Ключ элемента, который удаляют
     * @return Возвращает 0 в случае успеха, иначе - 1.
     */
    size_t erase(Key key);
};

//iterator

template <class Key, class T>
TemplateMap<Key, T>::iterator::iterator() {
    _vect = nullptr;
    _pos = std::string::npos;

}

template <class Key, class T>
typename TemplateMap<Key, T>::iterator& TemplateMap<Key, T>::iterator::operator=(const TemplateMap<Key, T>::iterator& other) {
    _vect = other._vect;
    _pos = other._pos;
    return *this;
}



template <class Key, class T>
std::pair<Key, T>& TemplateMap<Key, T>::iterator::operator*() const {
    return _vect->at(_pos);
}

template <class Key, class T>
std::pair<Key, T>* TemplateMap<Key, T>::iterator::operator->() const {
    return &(_vect->at(_pos));
}



template <class Key, class T>
bool TemplateMap<Key, T>::iterator::operator==(iterator other) const {
    return _pos == other._pos;
}

template <class Key, class T>
bool TemplateMap<Key, T>::iterator::operator!=(iterator other) const {
    return  _pos != other._pos;
}


template <class Key, class T>
typename TemplateMap<Key, T>::iterator& TemplateMap<Key, T>::iterator::operator++() {

    if (_pos == _vect->size() - 1) _pos = std::string::npos;
    else _pos++;

    return *this;
}


// public methods

template <class Key, class T>
TemplateMap<Key, T>::TemplateMap() {
}

template <class Key, class T>
TemplateMap<Key, T>::~TemplateMap() {
    _data.clear();
}

template <class Key, class T>
typename TemplateMap<Key, T>::iterator TemplateMap<Key, T>::begin() {

    if (_data.size() == 0) return end();

    iterator it;
    it._vect = &_data;
    it._pos = 0;
    return it;
}

template <class Key, class T>
typename TemplateMap<Key, T>::iterator TemplateMap<Key, T>::end() {
    iterator it;
    it._vect = &_data;
    it._pos = std::string::npos;
    return it;
}

template <class Key, class T>
size_t TemplateMap<Key, T>::size() {
    return _data.size();
}

template <class Key, class T>
typename TemplateMap<Key, T>::iterator TemplateMap<Key, T>::find(Key key) {
    iterator it;
    it._vect = &_data;
    size_t end = _data.size();
    if (end == 0){
        it._pos = std::string::npos;
        return it;
    }
    end -= 1;
    size_t beg = 0;
    size_t tmp;
    Key id;
    while(beg <= end){
        tmp = beg + (end - beg) / 2; // for case then beg + end > max size_t
        id = _data[tmp].first;
        if (id == key){
            it._pos = tmp;
            break;
        }
        if (id < key){
            beg = tmp + 1;
        }else{
            if (tmp == 0){
                end = 0;
                beg = 1;
                break;
            }
            end = tmp - 1;
        }
    }
    if (beg > end){
        it._pos = std::string::npos;
    }

    return it;
}

template <class Key, class T>
void TemplateMap<Key, T>::clear() {
    _data.clear();
}

template  <class Key, class T>
void TemplateMap<Key, T>::insert(Key key, T value){
    if (_data.size() == 0){
        _data.insert(_data.begin(), make_pair(key, value));
        return;
    }

    if(find(key) != end()){
        throw logic_error("Duplicate key");
    }
    iterator it = begin();
    while(it != end()){
        if (it->first > key) break;
        ++it;
    }
    if (it._pos == std::string::npos){
        _data.emplace(_data.end(), make_pair(key, value));
    }else{
        _data.emplace(_data.begin() + it._pos, make_pair(key, value));
    }
}

template <class Key, class T>
size_t TemplateMap<Key, T>::erase(Key key) {
    iterator it = find(key);
    if (it == end()){
        return 0;
    }

    _data.erase(_data.begin() + it._pos);

    return 1;
}

#endif
