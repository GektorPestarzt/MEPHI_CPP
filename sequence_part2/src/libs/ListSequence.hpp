#ifndef SRC_LISTSEQUENCE_HPP_
#define SRC_LISTSEQUENCE_HPP_

#include <iostream>
#include <assert.h>

#include "LinkedList.hpp"
#include "Sequence.hpp"

using namespace std;

template <typename T>
class ListSequence : public Sequence<T> {
public:
	ListSequence();
	ListSequence(T* items, std::size_t size);
    ListSequence(ListSequence<T>* list);
    ~ListSequence();

    class iterator {
        node<T>* it;

        public:
            iterator(node<T>* it) : it(it) {}

            T& operator*() { return this->it->data; }

            bool operator==(const iterator &it_compare) noexcept {
                return this->it == it_compare.it;
            }

            bool operator!=(const iterator &it_compare) noexcept {
                return this->it != it_compare.it;
            }

            iterator operator++() noexcept {
                this->it = this->it->next;
                return *this;
            }
    };

    iterator begin() noexcept;
    iterator end() noexcept;

	std::size_t size() const noexcept override;

    bool empty() const noexcept override;

    void set_head(node<T> *head) noexcept;
    node<T>* get_head() const noexcept;

	T& get(std::size_t index) override;
    T& back() override;
    T& front() override;

	void push_back(const T& item) noexcept override;
	void pop_back() override ;

    void append(const T& item) noexcept override;
    void prepend(const T& item) noexcept override;

    void insert(const T& item, std::size_t index) override;
    void erase(std::size_t index) override;

    T& operator[](std::size_t index);

private:
	LinkedList<T>* data;
};


template <typename T>
ListSequence<T>::ListSequence() : data(new LinkedList<T>()) {}

template <typename T>
ListSequence<T>::ListSequence(T* items, std::size_t size) : data(new LinkedList<T>(items, size)) {}

template <typename T>
ListSequence<T>::ListSequence(ListSequence<T>* list) : data(new LinkedList<T>(list->data)) {}

template <typename T>
ListSequence<T>::~ListSequence() { delete data; }

template <typename T>
typename ListSequence<T>::iterator ListSequence<T>::begin() noexcept { return iterator(this->data->get_head()); }

template <typename T>
typename ListSequence<T>::iterator ListSequence<T>::end() noexcept { return iterator(this->data->get_tail()->next); }

template <typename T>
std::size_t ListSequence<T>::size() const noexcept { return this->data->get_size(); }

template <typename T>
bool ListSequence<T>::empty() const noexcept { return this->data->empty(); }

template <typename T>
void ListSequence<T>::set_head(node<T> *head) noexcept { this->data->set_head(head); }

template <typename T>
node<T>* ListSequence<T>::get_head() const noexcept { return this->data->get_head(); }

template <typename T>
T& ListSequence<T>::get(std::size_t index) {
    assert(index < this->data->get_size());

    return this->data->get(index);
}

template <typename T>
T& ListSequence<T>::back() {
    assert(!this->data->empty());

    return this->data->get(this->data->get_size() - 1);        
}

template <typename T>
T& ListSequence<T>::front() {
    assert(!this->data->empty());

    return this->data->get(0);
}

template <typename T>
void ListSequence<T>::push_back(const T& item) noexcept {
    this->data->insert(item, this->data->get_size());
}

template <typename T>
void ListSequence<T>::pop_back() {
    assert(!this->data->empty());

    this->data->pop(this->data->get_size() - 1);
}

template <typename T>
void ListSequence<T>::append(const T& item) noexcept { this->push_back(item); }

template <typename T>
void ListSequence<T>::prepend(const T& item) noexcept { this->data->insert(item, 0); }

template <typename T>
void ListSequence<T>::insert(const T& item, std::size_t index) {
    assert(index <= this->data->get_size());

    this->data->insert(item, index);
}

template <typename T>
void ListSequence<T>::erase(std::size_t index) {
    assert(index < this->data->get_size());

    this->data->pop(index);
}

template <typename T>
T& ListSequence<T>::operator[](std::size_t index) {
    assert(index < this->data->get_size());

    return this->data->get(index);
}

#endif  // SRC_LISTSEQUENCE_HPP_
