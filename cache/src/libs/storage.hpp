#ifndef SRC_LIBS_STORAGE_HPP_
#define SRC_LIBS_STORAGE_HPP_

#include <vector>

#include "cache.hpp"

template<class Arr, typename Key>
class Storage {
public:
    Storage();
    ~Storage();

    bool push_item(Arr *item);
    Arr *get_item(const Key& key);

    void print();

private:
    Arr *find_item_in_vector(const Key& key);

private:
    std::vector<Arr *> *data;
    Cache<Arr, Key> *cache_;
};


template<class Arr, typename Key>
Storage<Arr, Key>::Storage() {
    this->data = new std::vector<Arr *>();
    this->cache_ = new Cache<Arr, Key>();
}

template<class Arr, typename Key>
Storage<Arr, Key>::~Storage() {
    delete this->cache_;
    for (Arr *item : *(this->data)) delete item;
    delete this->data;
}

template<class Arr, typename Key>
bool Storage<Arr, Key>::push_item(Arr *item) {
    bool status = !(find_item_in_vector(item->data));
    
    if (status) this->data->push_back(item);
    return !status;
}

template<class Arr, typename Key>
Arr *Storage<Arr, Key>::get_item(const Key& key) {
    Arr *item_to_return = this->cache_->get_item(key);
    if (!item_to_return) {
        item_to_return = this->find_item_in_vector(key);
        this->cache_->push_item(item_to_return);
    }

    return item_to_return;
}

template<class Arr, typename Key>
void Storage<Arr, Key>::print() {
    for (Arr *item : *(this->data)) {
        item->print();
    }
}

template<class Arr, typename Key>
Arr *Storage<Arr, Key>::find_item_in_vector(const Key& key) {
    Arr *item_to_return = nullptr;
    
    for (Arr *item : *(this->data)) {
        if (item->data == key) {
            item_to_return = item;
            break;
        }
    }

    return item_to_return;
}

#endif  // SRC_LIBS_STORAGE_HPP_