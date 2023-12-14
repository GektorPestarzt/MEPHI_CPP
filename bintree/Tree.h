#pragma once
#include <iostream>
#include <queue>

using namespace std;

template<class T>
class Tree {
public:
	Tree(T _data, Tree* _left = nullptr, Tree* _right = nullptr, Tree* _parent = nullptr);
	~Tree();

	Tree* GetLeft();
	Tree* GetRight();
	Tree* GetParent();

	void Insert(const T& _data, Tree** root);
	static Tree* Find(const T& _data, Tree* root);
	bool IsFind(const T& _data);
	
	static void Where(Tree** newTree, Tree* root, bool (*Check)(T));
	static void Map(Tree** newTree, Tree* root, bool (*Transf)(T));

	static Tree* Concat(Tree* _first, Tree* _second);

	T& Get();
	int Count(Tree* root);

	Tree* TreeMin();
	Tree* TreeSuccessor();
	Tree* TreeDelete(const T& data, Tree** root);

	static Tree* Balance(Tree* tr);
	static int Height(Tree* root);

	void Print();

private:
	void PrintA(Tree* root, int space = 0);
	static void InsertA(const  T& _data, Tree** root, Tree* parent = nullptr);
	static Tree* TreeMinA(Tree* item);
	static Tree* TreeSuccessorA(Tree* item);

	static Tree* RightRotation(Tree* root);
	static Tree* LeftRotation(Tree* root);
	static Tree* bLeftRotation(Tree* root);
	static Tree* bRightRotation(Tree* root);

	static int Factor(Tree* root);

private:
	T data;
	Tree* left;
	Tree* right;
	Tree* parent;
};


template<class T>
Tree<T>::Tree(T _data, Tree* _left, Tree* _right, Tree* _parent) : data(_data), left(_left), right(_right), parent(_parent) {}

template<class T>
Tree<T>::~Tree() {
	if (this == nullptr) return;
	this->left->~Tree();
	this->right->~Tree();
}

template<class T>
Tree<T>* Tree<T>::GetLeft() {
	return this->left;
}

template<class T>
Tree<T>* Tree<T>::GetRight() {
	return this->right;
}

template<class T>
Tree<T>* Tree<T>::GetParent() {
	return this->parent;
}

template<class T>
void Tree<T>::InsertA(const  T& _data, Tree** root, Tree* parent) {
	if (*root == nullptr)
	{
		*root = new Tree(_data, nullptr, nullptr, parent);
		return;
	}

	if (_data > (*root)->data) InsertA(_data, &(*root)->right, *root);
	else InsertA(_data, &(*root)->left, *root);

	*root = Balance(*root);
}

template<class T>
void Tree<T>::Insert(const T& _data, Tree** root) {
	InsertA(_data, root);
}

template<class T>
Tree<T>* Tree<T>::Find(const T& _data, Tree* root) {
	if (root == nullptr) return nullptr;

	if (root->data == _data) return root;

	if (_data > root->data) return Find(_data, root->right);
	else return Find(_data, root->left);
}

template<class T>
bool Tree<T>::IsFind(const T& _data) {
	if (Find(_data, this)) return true;
	else return false;
}

template<class T>
void Tree<T>::Where(Tree** newTree, Tree* root, bool (*Check)(T)) {
	if (root == nullptr) return;

	if (Check(root->data)) Insert(root->data, newTree);

	Where(newTree, root->left, Check);
	Where(newTree, root->right, Check);
}

template<class T>
void Tree<T>::Map(Tree** newTree, Tree* root, bool (*Transf)(T)) {
	if (root == nullptr) return;

	Insert(Transf(root->data), newTree);

	Map(newTree, root->left, Transf);
	Map(newTree, root->right, Transf);
}

template<class T>
Tree<T>* Tree<T>::Concat(Tree* _first, Tree* _second) {
	Tree* newTree = nullptr;
	std::queue<Tree*> q;

	q.push(_first);
	q.push(_second);

	Tree* tmp;
	while (!q.empty())
	{
		tmp = q.front();
		q.pop();

		if (tmp == nullptr) continue;
		_first->Insert(tmp->data, &newTree);

		q.push(tmp->left);
		q.push(tmp->right);
	}

	return newTree;
}

template<class T>
T& Tree<T>::Get() {
	return this->data;
}

template<class T>
int Tree<T>::Count(Tree* root) {
	if (root == nullptr) return 0;

	int l = Count(root->left);
	int r = Count(root->right);

	return l + r + 1;
}

template<class T>
Tree<T>* Tree<T>::TreeMinA(Tree* item)
{
	while (item->left != nullptr) item = item->left;
	return item;
}

template<class T>
Tree<T>* Tree<T>::TreeMin() {
	return TreeMinA(this);
}

template<class T>
Tree<T>* Tree<T>::TreeSuccessorA(Tree* item) {
	if (item->right != nullptr)
		return item->right->TreeMin();

	Tree* p = item->parent;
	while (p != nullptr && item == p->right)
	{
		item = p;
		p = p->parent;
	}

	return p;
}

template<class T>
Tree<T>* Tree<T>::TreeSuccessor() {
	return TreeSuccessorA(this);
}

template<class T>
Tree<T>* Tree<T>::TreeDelete(const T& data, Tree** root) {
	Tree* item = (*root)->Find(data, *root);

	if (item->left == nullptr && item->right == nullptr)
	{
		if (item == *root)
		{
			delete(*root);
			*root = nullptr;
			return nullptr;
		}

		Tree* _prnt = item->parent;

		if (_prnt->right == item) _prnt->right = nullptr;
		else _prnt->left = nullptr;

		delete(item);
		
		for (; _prnt != nullptr; _prnt = _prnt->parent)
		{
			_prnt->right = Balance(_prnt->right);
			_prnt->left = Balance(_prnt->left);
		}
		*root = Balance(*root);
		return _prnt;
	}

	if (item->left == nullptr || item->right == nullptr)
	{
		if (item == *root)
		{
			if (item->left != nullptr) *root = item->left;
			else *root = item->right;

			delete(item);

			(*root)->parent = nullptr;

			return nullptr;
		}

		Tree* _prnt = item->parent;
		Tree* _chld = nullptr;

		if (item->left != nullptr) _chld = item->left;
		else _chld = item->right;

		_chld->parent = _prnt;

		if (_prnt->left == item) _prnt->left = _chld;
		else _prnt->right = _chld;

		delete(item);
		
		for (; _chld != nullptr; _chld = _chld->parent)
		{
			_chld->right = Balance(_chld->right);
			_chld->left = Balance(_chld->left);
		}
		*root = Balance(*root);
		return _prnt;
	}

	Tree* _fin = item->TreeSuccessor();
	Tree* x = nullptr;

	if (_fin->left != nullptr) x = _fin->left;
	else x = _fin->right;

	if (x != nullptr) x->parent = _fin->parent;

	if (_fin->parent == nullptr) *root = x;
	else
	{
		if (_fin->parent->left == _fin)	_fin->parent->left = x;
		else _fin->parent->right = x;
	}

	if (_fin != item)
	{
		item->data = move(_fin->data);
	}

	Tree* _blnc = _fin->parent;
	delete(_fin);

	for (; _blnc != nullptr; _blnc = _blnc->parent)
	{
		_blnc->right = Balance(_blnc->right);
		_blnc->left = Balance(_blnc->left);
	}
	*root = Balance(*root);
	return item;
}

template<class T>
void Tree<T>::PrintA(Tree* root, int space) {
	if (!root) return;

	enum { COUNT = 2 };
	space += COUNT;

	PrintA(root->right, space);
	for (int i = COUNT; i < space; ++i) cout << "  ";

	cout << root->data << endl;
	PrintA(root->left, space);
}

template<class T>
void Tree<T>::Print() { PrintA(this); }

template<class T>
int Tree<T>::Height(Tree* root) {
	if (root == nullptr) return -1;

	int lheight = Height(root->left);
	int rheight = Height(root->right);

	if (lheight > rheight) return (lheight + 1);
	else return (rheight + 1);
}

template<class T>
Tree<T>* Tree<T>::RightRotation(Tree* root) {
	Tree* l = root->left;
	root->left = l->right;
	l->right = root;

	l->parent = root->parent;
	root->parent = l;
	if(root->left != nullptr) root->left->parent = root;

	return l;
}

template<class T>
Tree<T>* Tree<T>::LeftRotation(Tree* root) {
	Tree* r = root->right;
	root->right = r->left;
	r->left = root;

	r->parent = root->parent;
	root->parent = r;
	if (root->right != nullptr) root->right->parent = root;

	return r;
}

template<class T>
Tree<T>* Tree<T>::bLeftRotation(Tree* root) {
	root->right = RightRotation(root->right);
	root = LeftRotation(root);

	return root;
}

template<class T>
Tree<T>* Tree<T>::bRightRotation(Tree* root) {
	root->left = LeftRotation(root->left);
	root = RightRotation(root);

	return root;
}

template<class T>
int Tree<T>::Factor(Tree* root) {
	if (root == nullptr) return -1;
	return Height(root->left) - Height(root->right);
}

template<class T>
Tree<T>* Tree<T>::Balance(Tree* tr) {
	if (Factor(tr) < -1)
	{
		if (Factor(tr->right) <= 0)
			tr = LeftRotation(tr);

		else
			tr = bLeftRotation(tr);
	}
	if (Factor(tr) > 1)
	{
		if (Factor(tr->left) >= 0)
			tr = RightRotation(tr);

		else
			tr = bRightRotation(tr);
	}
	return tr;
}