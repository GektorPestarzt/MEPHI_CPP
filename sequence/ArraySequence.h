#include <iostream>
#include "DynamicArray.h"
#include "Sequence.h"

using namespace std;

template <class T>
class ArraySequence: public Sequence<T>
{
private:
	DynamicArray<T>* data;

public:
	ArraySequence() : data(nullptr) {}
	ArraySequence(T* items, int length) : data(new DynamicArray<T>(items, 2 * length, length)) {}
	~ArraySequence() {}

public:
	T& Get(int index) override
	{
		return this->data->Get(index);
	}

	int GetLength() override
	{
		return this->data->GetCapacity();
	}

	void Push(T item) override
	{
		if (this->data->GetSize() == this->data->GetCapacity())
			this->data->Resize(this->data->GetSize() * 2);

		this->data->Set(this->data->GetCapacity(), item);
		this->data->SetCapacity(this->data->GetCapacity() + 1);
	}

	void Set(int index, T item) override
	{
		this->data->Set(index, item);
	}

	void Pop(int index) override
	{
		for (int i = index; i < this->data->GetCapacity() - 1; i++)
			this->data->Set(i, this->data->Get(i + 1));

		this->data->SetCapacity(this->data->GetCapacity() - 1);

		if (this->data->GetCapacity() * 3 < this->data->GetSize())
			this->data->Resize(this->data->GetSize() / 2);
	}

	T& operator[](int index)
	{
		return (*this->data)[index];
	}
};

//HEHE
