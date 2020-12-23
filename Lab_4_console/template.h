#ifndef TEMPLATE_H
#define TEMPLATE_H
#include <iostream>
#include <memory>
#include <map>

using std::iterator;
using std::logic_error;


template <class Key, class T>
class TemplateMap {
private:
    class Node {
    public:
        std::pair<Key, T> data;
        Node* left;
        Node* right;
        Node* parent;
    };
    Node* root;
    size_t size_;

    Node* insert(Key key, T value, Node*& leaf, Node* parent);
    Node* find(Key key, Node* leaf);
    Node* clear(Node* leaf);
    bool removeLeaf(Node*& leaf, Key key);
public:
    class iterator {
    private:
        Node* node;
        Node* root;
    public:
        iterator();
        iterator& operator=(const iterator&);

        iterator& operator++();
        std::pair<Key, T>& operator*() const;
        std::pair<Key, T>* operator->() const;

        bool operator==(iterator other) const;
        bool operator!=(iterator other) const;

        friend class TemplateMap;
    };


    TemplateMap();
    ~TemplateMap();
    iterator begin();
    iterator end();
    size_t size();
    iterator find(Key key);
    void clear();
    void insert(Key key, T value);
    size_t erase(Key key);
};


template <class Key, class T>
typename TemplateMap<Key, T>::Node* TemplateMap<Key, T>::insert(Key key, T value, Node*& leaf, Node* parent) {

    if (!leaf)
    {
        leaf = new Node;
        leaf->left = leaf->right = nullptr;
        leaf->data.second = value;
        leaf->data.first = key;
        leaf->parent = parent;
        size_++;
        return leaf;
    }
    else if (key < leaf->data.first)
    {
        return insert(key, value, leaf->left, leaf);
    }
    else if (key > leaf->data.first)
    {
        return insert(key, value, leaf->right, leaf);
    }
    else
        return leaf;
}

template <class Key, class T>
typename TemplateMap<Key, T>::Node* TemplateMap<Key, T>::find(Key key, Node* leaf) {

    if (!leaf || leaf->data.first == key)
        return leaf;
    if (key < leaf->data.first)
        return find(key, leaf->left);
    else
        return find(key, leaf->right);
}

template <class Key, class T>
typename TemplateMap<Key, T>::Node* TemplateMap<Key, T>::clear(Node* leaf) {

    if (leaf)
    {
        leaf->left = clear(leaf->left);
        leaf->right = clear(leaf->right);
        delete leaf;
    }
    return nullptr;
}

template <class Key, class T>
bool TemplateMap<Key, T>::removeLeaf(Node*& leaf, Key key) {

    if (!leaf)
        return false;

    if (key < leaf->data.first)
        return removeLeaf(leaf->left, key);
    else if (key > leaf->data.first)
        return removeLeaf(leaf->right, key);
    else if (leaf->left && leaf->right) {
        Node* tmp = leaf->right;
        while (tmp && tmp->left)
            tmp = tmp->left;
        leaf->data = tmp->data;
        removeLeaf(leaf->right, tmp->data.first);
        return true;
    }
    else {
        Node* toDel = leaf;
        if (!leaf->left)
            leaf = leaf->right;
        else
            leaf = leaf->left;
        if (leaf)
            leaf->parent = toDel->parent;
        delete toDel;
        return true;
    }
}


template <class Key, class T>
TemplateMap<Key, T>::iterator::iterator() {
    node = nullptr;
    root = nullptr;
}

template <class Key, class T>
typename TemplateMap<Key, T>::iterator& TemplateMap<Key, T>::iterator::operator=(const TemplateMap<Key, T>::iterator& other) {
    node = other.node;
    root = other.root;
    return *this;
}

template <class Key, class T>
typename TemplateMap<Key, T>::iterator& TemplateMap<Key, T>::iterator::operator++() {

    if (node->right) {
        node = node->right;
        while (node->left) {
            node = node->left;
        }
    }
    else {
        Node* p = node->parent;
        while (p && node == p->right) {
            node = p;
            p = p->parent;
        }
        node = p;
    }
    return *this;
}

template <class Key, class T>
std::pair<Key, T>& TemplateMap<Key, T>::iterator::operator*() const {
    return node->data;
}

template <class Key, class T>
std::pair<Key, T>* TemplateMap<Key, T>::iterator::operator->() const {
    return &(node->data);
}

template <class Key, class T>
bool TemplateMap<Key, T>::iterator::operator==(iterator other) const {
    return node == other.node;
}

template <class Key, class T>
bool TemplateMap<Key, T>::iterator::operator!=(iterator other) const {
    return node != other.node;
}


template <class Key, class T>
TemplateMap<Key, T>::TemplateMap() {
    size_ = 0;
    root = nullptr;
}

template <class Key, class T>
TemplateMap<Key, T>::~TemplateMap() {
    root = clear(root);
}

template <class Key, class T>
size_t TemplateMap<Key, T>::size() {
    return size_;
}

template <class Key, class T>
typename TemplateMap<Key, T>::iterator TemplateMap<Key, T>::begin() {

    iterator it;
    it.root = it.node = root;
    while (it.node && it.node->left) {
        it.node = it.node->left;
    }
    return it;
}

template <class Key, class T>
typename TemplateMap<Key, T>::iterator TemplateMap<Key, T>::end() {

    iterator it;
    it.root = root;
    it.node = nullptr;
    return it;
}

template <class Key, class T>
typename TemplateMap<Key, T>::iterator TemplateMap<Key, T>::find(Key key) {
    iterator it;
    it.node = find(key, root);
    return it;
}

template <class Key, class T>
void TemplateMap<Key, T>::clear() {
    root = clear(root);
    size_ = 0;
}

template <class Key, class T>
size_t TemplateMap<Key, T>::erase(Key key) {
    if (removeLeaf(root, key)) {
        size_--;
        return 1;
    }
    else
        return 0;
}

template  <class Key, class T>
void TemplateMap<Key, T>::insert(Key key, T value){
    if(find(key) != end()){
        throw logic_error("Duplicate key");
    }
    insert(key, value, root, root);
}


#endif // TEMPLATE_H
