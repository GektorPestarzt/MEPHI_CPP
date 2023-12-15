#ifndef SRC_LIBS_ARRAYSEQUENCE_HPP_
#define SRC_LIBS_ARRAYSEQUENCE_HPP_

#include <iostream>

#include "DynamicArray.hpp"
#include "Sequence.hpp"

#define MIN_CAPACITY 10

template <class T>
class ArraySequence: public Sequence<T> {
public:
	ArraySequence();
	ArraySequence(T* array, std::size_t size);
    ArraySequence(const ArraySequence& x);
    ~ArraySequence();

    using iterator = T*;

    iterator begin() noexcept;
    iterator end() noexcept;

	std::size_t size() const noexcept override;
    bool empty() const noexcept override;

    T& get(std::size_t index) noexcept override;
    T& back() noexcept override;
    T& front() noexcept override;

	void push_back(const T& x) noexcept override;
	void pop_back() noexcept override;

    void append(const T& x) noexcept override;
    void prepend(const T& x) noexcept;

	void insert(const T& x, std::size_t index) noexcept override;
    void erase(std::size_t index) noexcept override;

    void swap(iterator first, iterator second) noexcept;
    void swap(std::size_t first, std::size_t second) noexcept;

	T& operator[](std::size_t index);

private:
    std::size_t min_capacity(std::size_t capacity);

private:
	DynamicArray<T> data;
};


template <class T>
ArraySequence<T>::ArraySequence()
    : data(DynamicArray<T>(MIN_CAPACITY)) {}

template <class T>
ArraySequence<T>::ArraySequence(T* array, std::size_t size)
    : data(DynamicArray<T>(array, size, min_capacity(size * 2))) {}

template <class T>
ArraySequence<T>::ArraySequence(const ArraySequence& x)
    : data(DynamicArray<T>(x.data)) {}

template <class T>
ArraySequence<T>::~ArraySequence() {}

template <class T>
T* ArraySequence<T>::begin() noexcept { return data.get_ptr(0); }

template <class T>
T* ArraySequence<T>::end() noexcept { return data.get_ptr(data.size()); }

template <class T>
std::size_t ArraySequence<T>::size() const noexcept { return data.size(); }

template <class T>
bool ArraySequence<T>::empty() const noexcept { return data.size() == 0; }

template <class T>
T& ArraySequence<T>::get(std::size_t index) noexcept { return data.get(index); }

template <class T>
T& ArraySequence<T>::back() noexcept { return data.get(data.size() - 1); }

template <class T>
T& ArraySequence<T>::front() noexcept { return data.get(0); }

template <class T>
void ArraySequence<T>::push_back(const T& x) noexcept {
    std::size_t size = data.size();
    std::size_t capacity = data.capacity();

    if (size + 1 == capacity)
        data.resize(capacity * 2);

    data.set(x, size);
    data.set_size(size + 1);
}

template <class T>
void ArraySequence<T>::pop_back() noexcept {
    std::size_t size = data.size();
    std::size_t capacity = data.capacity();

    data.set_size(size - 1);

    if (size * 3 < capacity && capacity > MIN_CAPACITY)
        data.resize(this->min_capacity(capacity / 2));
}

template <class T>
void ArraySequence<T>::append(const T& x) noexcept { push_back(x); }

template <class T>
void ArraySequence<T>::prepend(const T& x) noexcept {
    std::size_t size = data.size();
    std::size_t capacity = data.capacity();

    if (size + 1 == capacity)
        data.resize(capacity * 2);

    if (!empty()) {
        for (std::size_t i = size - 1; i > 0; --i)
            data.set(data.get(i), i + 1);
    }

    data.set(data.get(0), 1);
    data.set(x, 0);
    data.set_size(++size);
}

template <class T>
void ArraySequence<T>::insert(const T& x, std::size_t index) noexcept {
    std::size_t size = data.size();
    std::size_t capacity = data.capacity();

    if (size + 1 == capacity)
        data.resize(capacity * 2);

    if (!empty()) {
        for (std::size_t i = size - 1; i >= index; --i) {
            data.set(data.get(i), i + 1);
            if (i == 0) break;
        }
    }

    data.set(x, index);
    data.set_size(++size);
}

template <class T>
void ArraySequence<T>::erase(std::size_t index) noexcept {
    std::size_t size = data.size();
    std::size_t capacity = data.capacity();

    for (std::size_t i = index + 1; i <= size; ++i)
        data.set(data.get(i), i - 1);

    data.set_size(size - 1);

    if (size * 3 < capacity && capacity > MIN_CAPACITY)
        data.resize(this->min_capacity(capacity / 2));
}

template <class T>
void ArraySequence<T>::swap(iterator first, iterator second) noexcept {
    T buffer = (*first)->data;
    (*first)->data = (*second)->data;
    (*second)->data = buffer;
}

template <class T>
void ArraySequence<T>::swap(std::size_t first, std::size_t second) noexcept {
    T buffer = data.get(first);
    data.set(data.get(second), first);
    data.set(buffer, second);
}

template <class T>
std::size_t ArraySequence<T>::min_capacity(std::size_t capacity) {
    return capacity < MIN_CAPACITY ? MIN_CAPACITY : capacity;
}

template <class T>
T& ArraySequence<T>::operator[](std::size_t index) { return data->get(index); }

#endif  // SRC_LIBS_ARRAYSEQUENCE_HPP_