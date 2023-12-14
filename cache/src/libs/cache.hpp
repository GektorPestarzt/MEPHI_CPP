#ifndef SRC_LIBS_CACHE_HPP_
#define SRC_LIBS_CACHE_HPP_

#include "hashtable.hpp"
#include <queue>

#define MAX_ITEMS 20

template<class Arr, typename Key>
class Cache {
public:
    Cache();
    ~Cache();

    Arr *get_item(const Key& word);
    bool push_item(Arr *item);

private:
    HashTable<Arr, Key> *hashtable;
    std::queue<Arr *> *queue;
};


template<class Arr, typename Key>
Cache<Arr, Key>::Cache() {
    this->hashtable = new HashTable<Arr, Key>();
    this->queue = new std::queue<Arr *>();
}

template<class Arr, typename Key>
Cache<Arr, Key>::~Cache() {
    delete this->hashtable;
    delete this->queue;
}

template<class Arr, typename Key>
Arr *Cache<Arr, Key>::get_item(const Key& word) {
    Arr *item_to_return = this->hashtable->get_item(word);
    return item_to_return;
}

template<class Arr, typename Key>
bool Cache<Arr, Key>::push_item(Arr *item) {
    bool status = this->hashtable->push_item(item);

    if (!status) {
        if (this->queue->size() == MAX_ITEMS) {
            Arr *old_item = this->queue->front();
            this->hashtable->erase(old_item->data);
            queue->pop();
        }

        queue->push(item);
    }

    return status;
}

#endif  // SRC_LIBS_CACHE_HPP_