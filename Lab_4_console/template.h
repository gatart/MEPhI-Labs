#ifndef TEMPLATE_H
#define TEMPLATE_H
#include <iostream>
#include <vector>
#include <string>

using std::iterator;
using std::logic_error;
using std::pair;

template <class Key, class T>
class TemplateMap {
private:
    std::vector<pair<Key, T>> _data;

public:
    class iterator {
    private:
        // typename std::vector<pair<Key, T>>::iterator _point; // для наглой реализации
        size_t _pos; // для обычной реализации
        std::vector<pair<Key, T>>* _vect;

    public:
        iterator(); //v
        iterator& operator=(const iterator&); //v

        iterator& operator++(); //v
        std::pair<Key, T>& operator*() const; //v
        std::pair<Key, T>* operator->() const; //v

        bool operator==(iterator other) const; //v
        bool operator!=(iterator other) const; //v

        friend class TemplateMap;
    };

    TemplateMap(); //v
    ~TemplateMap(); //v
    iterator begin(); //v
    iterator end(); //v
    size_t size(); //v
    iterator find(Key key);
    void clear(); //v
    void insert(Key key, T value);
    size_t erase(Key key); //v
};

//iterator

template <class Key, class T>
TemplateMap<Key, T>::iterator::iterator() {
    // _point = nullptr; // наглая реализация
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
    // return *_point; // наглая реализация
    return _vect->at(_pos);
}

template <class Key, class T>
std::pair<Key, T>* TemplateMap<Key, T>::iterator::operator->() const {
    // return &(*_point); // наглая реализация
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
    // it._point = _data.begin(); // наглая реализация
    it._vect = &_data;
    it._pos = 0;
    return it;
}

template <class Key, class T>
typename TemplateMap<Key, T>::iterator TemplateMap<Key, T>::end() {
    iterator it;
    // it._point = _data.end(); // наглая реализация
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
