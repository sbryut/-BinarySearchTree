#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H
#include <iostream>
#include <stack>
#include <queue>
#include <vector>

template <class T>
class BinarySearchTree
{
public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree<T>& other) = delete;
	BinarySearchTree(BinarySearchTree<T>&& other) noexcept;
	BinarySearchTree <T>& operator= (const BinarySearchTree <T>& other) = delete;
	BinarySearchTree <T>& operator= (BinarySearchTree <T>&& other) noexcept;
	~BinarySearchTree();

	// 1.1 Функция поиска по ключу в бинарном дереве поиска
	bool iterativeSearch(const T& key) const;
	// 2 Вставка нового элемента в дерево: true, если элемент добавлен;
	// false, если элемент уже был
	bool insert(const T& key);
	// 3.1 Удаление элемента из дерева, не нарушающее порядка элементов
	// true, если элемент удален; false, если элемента не было
	bool deleteKey(const T& key);
	// 4.1 Печать строкового изображения дерева в выходной поток out,
	// использовать скобки, чтобы показать структуру дерева
	void print(std::ostream& out) const;
	// 5.1 Определение количества узлов дерева
	int getCount() const;
	// 6.1 Определение высоты дерева
	int getHeight() const;
	// 7 Инфиксный обход дерева (итеративный)
	void iterativeInorderWalk() const;
	// 8.1 Инфиксный обход дерева (рекурсивный)
	void inorderWalk() const;
	// 9 Обход двоичного дерева по уровням (в ширину).
	void walkByLevels() const;
	// 10 Являются ли два дерева похожими
	bool isSimilar(const BinarySearchTree<T>& other) const;
	// 11 Есть одинаковые ключи в двух деревьях поиска
	bool isIdenticalKey(const BinarySearchTree<T>& other) const;
private:
	template <class T>
	struct Node {
		T key_; // значение ключа, содержащееся в узле
		Node<T>* left_; // указатель на левое поддерево
		Node<T>* right_; // указатель на правое поддерево
		Node<T>* p_; // указатель на родителя 

		Node(T key, Node* left = nullptr, Node* right = nullptr, Node* p = nullptr) :
			key_(key), left_(left), right_(right), p_(p)
		{ }
		~Node()
		{
			delete left_;
			delete right_;
		}
};

	Node<T>* root_; // Указатель на корневой узел

	// 1.2 Функция поиска адреса узла по ключу в бинарном дереве поиска
	Node<T>* iterativeSearchNode(const T& key) const;
	// 4.2 Рекурсивная функция для вывода изображения дерева в выходной поток
	void printNode(std::ostream& out, Node<T>* root) const;
	// 5.2 Рекурсивная функция определения количества узлов дерева
	int getCount(const Node<T>* node) const;
	// 6.2 Рекурсивная функция определения высоты дерева
	int getHeight(const Node<T>* node) const;
	// 8.2 Рекурсивная функция для инфиксного обхода узлов дерева.
	void inorderWalk(Node<T>* node) const;
	//swap
	void swap(BinarySearchTree<T>& other) noexcept;
	//deleteNode
	bool deleteNode(Node<T>* node, const T& key);
	bool isSimilarHelper(const Node<T>* nodeFirst, const Node<T>* nodeSecond) const;
	void inorderTraversal(const Node<T>* node, std::vector<T>& keys) const;
};

template <class T>
BinarySearchTree<T>::BinarySearchTree() : root_(nullptr) {}

template <class T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& other) noexcept :
	root_(other.root_)
{
	other.root_ = nullptr;
}

template <class T>
BinarySearchTree <T>& BinarySearchTree<T>::operator= (BinarySearchTree <T>&& other) noexcept
{
	if (this != &other) swap(other);
	return *this;
}

template <class T>
void BinarySearchTree<T>::swap(BinarySearchTree<T>& other) noexcept
{
	std::swap(root_, other.root_);
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{
	delete root_;
}

template <class T>
bool BinarySearchTree<T>::iterativeSearch(const T& key) const
{
	return iterativeSearchNode(key) != nullptr;
}

template <class T>
BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::iterativeSearchNode(const T& key) const
{
	Node<T>* helper = this->root_;
	while (helper != nullptr)
	{
		if (helper == nullptr) break;
		if (key < helper->key_) helper = helper->left_;
		else if (key > helper->key_) helper = helper->right_;
		else return helper;
	}
	return helper;
}

template <class T>
bool BinarySearchTree<T>::insert(const T& key) 
{
	Node<T>* newNode = new Node<T>(key);
	if (root_ == nullptr)
	{
		root_ = newNode;
		return true;
	}

	Node<T>* helper = root_;
	Node<T>* parent = nullptr;
	while (helper != nullptr)
	{
		parent = helper;
		if (key < helper->key_) helper = helper->left_;
		else if (key > helper->key_) helper = helper->right_;
		else return false;
	}
	newNode->p_ = parent;
	if (key < parent->key_) parent->left_ = newNode;
	else parent->right_ = newNode;
	return true;
}

template <class T>
bool BinarySearchTree<T>::deleteKey(const T& key)
{
	return deleteNode(root_, key);
}
template <class T>
bool BinarySearchTree<T>::deleteNode(Node<T>* node, const T& key)
{
	Node<T>* nodeToDelete = iterativeSearchNode(key); 
	if (nodeToDelete == nullptr) return false;

	Node<T>*current = node;
	Node<T>* parent = nullptr;

	while (current != nullptr && current->key_ != key)
	{
		parent = current;
		if (key < current->key_) current = current->left_;
		else if (key > current->key_) current = current->right_;
	}

	if (current == nullptr) return false;

	//дочерних элементов у ключа нет
	if (current->left_ == nullptr && current->right_ == nullptr)
	{
		if (current != node) {
			if (parent->left_ == current) parent->left_ = nullptr;
			else parent->right_ = nullptr;
		}
		else node = nullptr;
		delete current;
	}

	//удаляемый узел имеет двух потомков
	else if (current->left_ && current->right_)
	{
		//чтобы найти неупорядоченный узел-преемник
		Node<T>* minNode = current->right_;
		while (minNode->left_ != nullptr)
			minNode = minNode->left_;
		T value = minNode->key_;//сохраняем значение
		deleteNode(root_, minNode->key_);//рекурсивно удаляем преемника
		current->key_ = value;//копируем значение преемника в текущий узел
	}
	else //удаляемый узел имеет только одного потомка
	{
		Node<T>* child = (current->left_) ? current->left_ : current->right_;
		// если удаляемый узел не является корневым узлом, устанавливаем его родителя
		// своему потомку
		if (current != root_)
		{
			if (parent != nullptr)
			{
				if (current == parent->left_) parent->left_ = child;
				else parent->right_ = child;
			}
		}
		// если удаляемый узел является корневым узлом, то установить корень дочернему
		else root_ = child;
		delete current;
	}
	return true;
}

template<class T>
void BinarySearchTree<T>::print(std::ostream& out) const
{
	printNode(out, root_);
	std::cout << '\n';
}

template<class T>
void BinarySearchTree<T>::printNode(std::ostream& out, Node<T>* root) const
{
	if (root == nullptr) return;
	 
	out << "( ";
	out << root->key_ << ' ';
	printNode(out, root->left_);
	printNode(out, root->right_);
	out << ")";
}

template <class T>
int BinarySearchTree<T>::getCount() const
{
	return getCount(this->root_);
}

template <class T>
int BinarySearchTree<T>::getCount(const Node<T>* node) const
{
	if (!node) return 0;
	return (1 + getCount(node->left_) + getCount(node->right_));
}

template <class T>
int BinarySearchTree<T>::getHeight() const
{
	return getHeight(root_);
}

template <class T>
int BinarySearchTree<T>::getHeight(const Node<T>* node) const
{
	if (node == nullptr) return 0;
	return 1 + std::max(getHeight(node->left_), getHeight(node->right_));
}

template <class T>
void BinarySearchTree<T>::iterativeInorderWalk() const
{
	Node<T>* current = root_;
	std::stack<Node<T>*> stack; // Создаем стек для итеративного обхода

	
	while (!stack.empty() || current != nullptr) {
		if (current != nullptr) {
			stack.push(current); 
			current = current->left_; 
		}
		else {
			current = stack.top(); // Получаем следующий узел из стека
			stack.pop(); 
			std::cout << current->key_ << " "; 
			current = current->right_; 
		}
	}

	std::cout << '\n';
}

template <class T>
void BinarySearchTree<T>::inorderWalk() const
{
	inorderWalk(root_);
	std::cout << '\n';
}

template <class T>
void BinarySearchTree<T>::inorderWalk(Node<T>* node) const
{
	if (node)
	{
		inorderWalk(node->left_);
		std::cout << node->key_ << " ";
		inorderWalk(node->right_);
	}
}

template <class T>
void BinarySearchTree<T>::walkByLevels() const
{
	if (root_ == nullptr) return;
	std::queue<Node<T>*> queue; 
	queue.push(root_);

	while (!queue.empty()) {
		Node<T>* current = queue.front(); // Получаем первый узел из очереди
		queue.pop(); 

		std::cout << current->key_ << ' ';

		
		if (current->left_ != nullptr) {
			queue.push(current->left_);
		}
		
		if (current->right_ != nullptr) {
			queue.push(current->right_);
		}
	}

	std::cout << '\n';
}

template<class T>
bool BinarySearchTree<T>::isSimilar(const BinarySearchTree<T>& other) const
{
	return isSimilarHelper(root_, other.root_);
}

template<class T>
bool BinarySearchTree<T>::isSimilarHelper(const Node<T>* nodeFirst, const Node<T>* nodeSecond) const
{
	if (nodeFirst == nullptr && nodeSecond == nullptr) {
		return true; // Если оба узла пусты, они сходны
	}

	if (nodeFirst == nullptr || nodeSecond == nullptr) {
		return false; // Если один из узлов пуст, а другой нет, они не сходны
	}

	// Рекурсивно проверяем сходство левых и правых потомков
	return isSimilarHelper(nodeFirst->left_, nodeSecond->left_) &&
		isSimilarHelper(nodeFirst->right_, nodeSecond->right_);
}

template<class T>
bool BinarySearchTree<T>::isIdenticalKey(const BinarySearchTree<T>& other) const
{
	std::vector<T> thisInorderKeys; 
	std::vector<T> otherInorderKeys;
	inorderTraversal(root_, thisInorderKeys); 
	inorderTraversal(other.root_, otherInorderKeys); 

	return thisInorderKeys == otherInorderKeys; 
}

// Вспомогательная функция для инфикс. обхода дерева и сохранения ключей в векторе
template<class T>
void BinarySearchTree<T>::inorderTraversal(const Node<T>* node, std::vector<T>& keys) const
{
	if (node != nullptr) {
		inorderTraversal(node->left_, keys); // Рекурсивно обходим левое поддерево
		keys.push_back(node->key_); 
		inorderTraversal(node->right_, keys); // Рекурсивно обходим правое поддерево
	}
}













#endif