#include <iostream>

using namespace std;

template <class T>
class DynamicArray
{
private:
	T* array;
	int size = 0;
	int capacity = 0;

public:
	DynamicArray() : array(new T[1]), size(1) {}
	DynamicArray(int size) : size(size), array(new T[size]) {}
	DynamicArray(T* items, int size, int _capacity) : array(items), size(size), capacity(_capacity) {}
	~DynamicArray()
	{
		delete[] array;
	}

public:
	T& Get(int index)
	{
		if (index < 0)
			throw exception("Negative index");

		if (index >= this->capacity)
			throw exception("Index is out of range");

		if (this->array == nullptr)
			throw exception("Nullptr");

		return this->array[index];
	}

	int GetSize()
	{
		return this->size;
	}

	int GetCapacity()
	{
		return this->capacity;
	}

	void SetCapacity(int capacity)
	{
		if (capacity < 0)
			throw exception("Negative length");

		if (capacity > this->size)
			throw exception("Length can't be less than size");

		this->capacity = capacity;
	}

	void Set(int index, T value)
	{
		if (index < 0)
			throw exception("Negative index");

		if (index >= this->size)
			throw exception("Index is out of range");

	
		this->array[index] = value;
	}

	void Resize(int newSize)
	{
		if (newSize <= 0)
			throw exception("Negative or zero size");

		T* newArray = new T[newSize];

		for (int i = 0; i < newSize || i < this->capacity; i++)
			newArray[i] = this->array[i];

		this->array = newArray;
		this->size = newSize;
		if (newSize < this->capacity)
			this->capacity = newSize;
	}

	T& operator[](int index)
	{
		return this->array[index];
	}
};

//HEHE
