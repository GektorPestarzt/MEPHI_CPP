#ifndef SRC_LIBS_HASHTABLE_HPP_
#define SRC_LIBS_HASHTABLE_HPP_

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

#define START_POWER 20

template<class Arr, typename Key>
class HashTable {
public:
    HashTable();
    HashTable(std::size_t power);
    ~HashTable();

    Arr* get_item(const Key& key);

    bool push_item(Arr *item);
    bool push_item(const Key& key);

    std::size_t erase(const Key& key);
    void resize(std::size_t new_power);

private:
    std::size_t power;
    std::vector<std::list<Arr *> *> *data;
    std::size_t size;

    std::size_t func(std::size_t hash, std::size_t power);
};


template<class Arr, typename Key>
HashTable<Arr, Key>::HashTable(std::size_t power) : power(power), size(0) {
    this->data = new std::vector<std::list<Arr*> *>(power);
    for (std::size_t i = 0; i < power; ++i) {
        (*this->data)[i] = new std::list<Arr*>();
    }
}

template<class Arr, typename Key>
HashTable<Arr, Key>::HashTable() : power(START_POWER), size(0) {
    this->data = new std::vector<std::list<Arr*> *>(power);
    for (std::size_t i = 0; i < power; ++i) {
        (*this->data)[i] = new std::list<Arr*>();
    }
}

template<class Arr, typename Key>
HashTable<Arr, Key>::~HashTable() {
    for (std::list<Arr *> *list : *this->data) {
        delete list;
    }
    delete(this->data);
}

template<class Arr, typename Key>
Arr* HashTable<Arr, Key>::get_item(const Key& key) {
    Arr *item_to_return = nullptr;
    std::size_t hash = std::hash<Key>{}(key);
    std::list<Arr*> *list = (*this->data)[this->func(hash, this->power)];

    for(Arr *item : *list) {
        if (item->hash == hash) {
            item_to_return = item;
        }
    }

    return item_to_return;
}

template<class Arr, typename Key>
bool HashTable<Arr, Key>::push_item(Arr *item) {
    Arr *check = this->get_item(item->data);
    bool status = 1;

    if (!check) {
        (*this->data)[this->func(item->hash, this->power)]->push_back(item);
        ++(this->size);
        status = 0;
    }

    return status;
}

template<class Arr, typename Key>
bool HashTable<Arr, Key>::push_item(const Key& key) {
    Arr *item = this->get_item(key);
    bool status = 1;

    if (!item) {
        Arr *new_item = new Arr(key);
        (*this->data)[this->func(new_item->hash, this->power)]->push_back(new_item);
        ++(this->size);
        status = 0;
    }

    return status;
}

template<class Arr, typename Key>
std::size_t HashTable<Arr, Key>::erase(const Key& key) {
    std::size_t hash = std::hash<Key>{}(key);
    std::size_t item_amount = 0;
    std::list<Arr*> *list = (*this->data)[this->func(hash, this->power)];

    typename std::list<Arr *>::iterator it;
    for(it = list->begin(); (*it)->hash != hash && it != list->end(); ++it) {}

    if (it != list->end()) {
        list->erase(it);
    }

    --(this->size);
    return item_amount;
}

template<class Arr, typename Key>
void HashTable<Arr, Key>::resize(std::size_t new_power) {
    auto new_data = new std::vector<std::list<Arr*> *>(new_power);
    for (std::size_t i = 0; i < new_power; ++i) {
        (*new_data)[i] = new std::list<Arr*>();
    }

    for (std::list<Arr*> *list : *this->data) {
        for (Arr *item : *list) {
            (*new_data)[this->func(item->hash, new_power)]->push_back(item);
        }
    }

    for (std::list<Arr*> *list : *this->data) {
        delete list;
    }
    delete(this->data);

    this->data = new_data;
    this->power = new_power;
}

template<class Arr, typename Key>
std::size_t HashTable<Arr, Key>::func(std::size_t hash, std::size_t power) {
    std::size_t key = abs(hash % power);
    return key;
}

#endif  // SRC_LIBS_HASHTABLE_HPP_