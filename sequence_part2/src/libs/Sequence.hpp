#ifndef SRC_SEQUENCE_HPP_
#define SRC_SEQUENCE_HPP_

#include <iostream>

template <class T>
class Sequence {
public:
	virtual std::size_t size() const noexcept = 0;
    virtual bool empty() const noexcept = 0;

    virtual T& front() = 0;
    virtual T& back() = 0;
    virtual T& get(std::size_t index) = 0;

	virtual void push_back(const T& x) noexcept = 0;
    virtual void pop_back() = 0;

	virtual void append(const T& x) noexcept = 0;
    virtual void prepend(const T& x) noexcept = 0;
    virtual void insert(const T& x, std::size_t index) = 0;
    virtual void erase(std::size_t index) = 0;

    virtual ~Sequence() {}
};

#endif  // SRC_SEQUENCE_HPP_
