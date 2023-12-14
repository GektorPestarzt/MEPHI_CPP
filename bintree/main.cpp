#include <iostream>
#include "Tree.h"

class Gosha
{
public:
	int mark;

	Gosha(int data) : mark(data) {}

	bool operator== (const Gosha &a) const { return this->mark == a.mark; }
	bool operator> (const Gosha &a) const { return this->mark > a.mark; }
	bool operator>= (const Gosha &a) const { return this->mark >= a.mark; }
	bool operator< (const Gosha &a) const { return this->mark < a.mark; }
	bool operator<= (const Gosha &a) const { return this->mark <= a.mark; }

}; 

Gosha MapF(Gosha& a) {
	return Gosha(a.mark*19);
}

bool WhereF(Gosha& a) {
	return a.mark > 600;
}

int main()
{
	Tree<Gosha>* tr = nullptr;

	/*
	for (int i = 0; i < 100; i++)
	{
		Gosha a = Gosha(rand() % 500);

		Tree<Gosha>::Insert(a, &tr);
	}

	cout << tr->IsFind(-2) << endl;
	cout << Tree<Gosha>::Find(1, tr) << endl;
	*/

	/*
	Tree<Gosha>::Insert(10, &tr);
	Tree<Gosha>::Insert(12, &tr);
	Tree<Gosha>::Insert(5, &tr);
	Tree<Gosha>::Insert(3, &tr);
	Tree<Gosha>::Insert(6, &tr);
	*/

	tr->Insert(15, &tr);
	tr->Insert(16, &tr);
	tr->Insert(5, &tr);
	tr->Insert(3, &tr);
	tr->Insert(12, &tr);
	tr->Insert(20, &tr);
	tr->Insert(10, &tr);
	tr->Insert(13, &tr);
	tr->Insert(18, &tr);
	tr->Insert(23, &tr);

	cout << tr->TreeDelete(tr->GetRight()->Get(), &tr)->Get().mark << endl;

	cout << tr->GetRight()->Get().mark << endl;

	return 0;
}
