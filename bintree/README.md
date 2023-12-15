# Binary Tree C++

Реализация класса двоичного дерева поиска на языке C++

# Methods

## Tree(T _data, Tree* _left = nullptr, Tree* _right = nullptr, Tree* _parent = nullptr);

Конструктор создания верщины дерева.
Может принимать двух своих потомков и родителя.

## Tree* GetLeft();

Возвращает указатель на левого потомка данной вершины.

## Tree* GetRight();

Возвращает указатель на правого потомка данной вершины.

## Tree* GetParent();

Возвращает указатель на родителя данной вершины.

## void Insert(const T& _data, Tree** root);

Создаёт новую вершину, вставляя её в дерево, не нарушая условий двоичного дерева поиска.
После балансирует дерево.

## static Tree* Find(const T& _data, Tree* root);

Ищет в текущем дереве вершину с _data.
Если вершина есть, возвращает ссылку на неё, иначе возвращает nullptr.

## bool IsFind(const T& _data);

Ищет в текущем дереве вершину с _data.
Если вершина есть, возвращает true, иначе возвращает false.
 
## static void Where(Tree** newTree, Tree* root, bool (*Check)(T));



## static void Map(Tree** newTree, Tree* root, bool (*Transf)(T));

Создаёт новое дерево, которое копируется с исходного.
К каждой вершине применяется функция Transf.

## static Tree* Concat(Tree* _first, Tree* _second);

Объеденяет два дерева не нарушая условий двоичного дерева поиска и балансировки.

## T& Get();



## int Count(Tree* root);

## Tree* TreeMin();
## Tree* TreeSuccessor();
## Tree* TreeDelete(const T& data, Tree** root);

## static Tree* Balance(Tree* tr);
## static int Height(Tree* root);
