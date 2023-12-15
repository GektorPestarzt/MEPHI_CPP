#ifndef SRC_DYNAMICARRAY_HPP_
#define SRC_DYNAMICARRAY_HPP_

#include <iostream>

template <class T>
class DynamicArray {
public:
    DynamicArray(std::size_t capacity);
    DynamicArray(T* array, std::size_t size, std::size_t capacity);
	DynamicArray(const DynamicArray& x);
    ~DynamicArray();

	T& get(std::size_t index) noexcept;
    T* get_ptr(std::size_t index) const noexcept; // ???????????

	std::size_t size() const noexcept;
	std::size_t capacity() const noexcept;

	void set_capacity(std::size_t capacity) noexcept;
    void set_size(std::size_t size) noexcept;
	void set(const T& value, std::size_t index) noexcept;

	void resize(std::size_t new_capacity) noexcept;

private:
	T* array_;
	std::size_t size_ = 0;
	std::size_t capacity_ = 0;
};


template <class T>
DynamicArray<T>::DynamicArray(std::size_t capacity)
	: array_(new T[capacity]), size_(0), capacity_(capacity) {}

template <class T>
DynamicArray<T>::DynamicArray(T* array, std::size_t size, std::size_t capacity)
	: array_(new T[capacity]), size_(size), capacity_(capacity) {
	std::copy(array, array + size, array_);
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray& x)
	: DynamicArray(x.array_, x.size_, x.capacity_) {}

template <class T>
DynamicArray<T>::~DynamicArray() { delete[] array_; }

template <class T>
T& DynamicArray<T>::get(std::size_t index) noexcept { return array_[index]; }

template <class T>
T* DynamicArray<T>::get_ptr(std::size_t index) const noexcept { return array_ + index; }

template <class T>
std::size_t DynamicArray<T>::size() const noexcept { return size_; }

template <class T>
std::size_t DynamicArray<T>::capacity() const noexcept { return capacity_; }

template <class T>
void DynamicArray<T>::set_capacity(std::size_t capacity) noexcept { capacity_ = capacity; }

template <class T>
void DynamicArray<T>::set_size(std::size_t size) noexcept { size_ = size; }

template <class T>
void DynamicArray<T>::set(const T& value, std::size_t index) noexcept { array_[index] = value; }

template <class T>
void DynamicArray<T>::resize(std::size_t new_capacity) noexcept {
	auto new_array = new T[new_capacity];

	for (std::size_t i = 0; i < new_capacity && i < size_; i++)
		new_array[i] = array_[i];

	delete[] array_;
	array_ = new_array;
	capacity_ = new_capacity;
	if (new_capacity < size_) size_ = new_capacity;
}

#endif  // SRC_DYNAMICARRAY_HPP_
