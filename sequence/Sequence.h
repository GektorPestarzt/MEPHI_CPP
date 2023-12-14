template <class T>
class Sequence
{
public:
	virtual T& Get(int) = 0;
	virtual int GetLength() = 0;
	virtual void Push(T) = 0;
	virtual void Set(int, T) = 0;
	virtual void Pop(int) = 0;
};

//HEHE
