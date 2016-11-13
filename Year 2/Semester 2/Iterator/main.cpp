#include <iostream>

using namespace std;

template <typename T>
class IIterator {
public:
	virtual void first() = 0;
	virtual void next() = 0;
	virtual T get() = 0;
	virtual bool isDone() = 0;
};

template<typename U>
class Node
{
	U _elem;
public:
	Node<U> * _next = NULL;

	Node(U data) :_elem(data) {};

	U data() {
		return _elem;
	}
};


template <typename T>
class List
{
public:
	template<typename U> friend class ListIterator;


	List() {
		headNode = NULL;
		tailNode = NULL;
	};

	virtual Node<T>* head() {
		return headNode;
	};

	virtual Node<T>* tail() {
		return tailNode;
	}

	virtual void pushTail(T elem) {
		Node<T> * newElem = new Node<T>(elem);
		if (!headNode) {
			headNode = newElem;
			tailNode = newElem;
			return;
		}
		tailNode->_next = newElem;
		tailNode = newElem;
	};

	virtual void pushHead(T elem) {
		Node<T> * newElem = new Node<T>(elem);
		if (!headNode) {
			headNode = newElem;
			tailNode = newElem;
			return;
		}
		newElem->_next = headNode;
		headNode = newElem;
	};

	virtual void popTail() {
		Node<T> * curr = headNode;
		Node<T> * prev = NULL;
		if (headNode) {
			while (curr && curr->_next) {
				prev = curr;
				curr = curr->_next;
			}
			if (tailNode == headNode) {
				headNode = NULL;
			}
			delete curr;
			tailNode = prev;
			prev->_next = NULL;
		}
		else {
			throw underflow_error("Empty");
		}
	};

	virtual void popHead() {
		if (headNode) {
			Node<T> * toDel = headNode;
			if (!headNode->_next) {
				tailNode = NULL;
			}
			headNode = headNode->_next;
			delete toDel;
		}
		else {
			throw underflow_error("Empty");
		}
	};

	bool isEmpty() {
		return headNode?true:false;
	}

	virtual void show() {
		Node<T> * curr = headNode;
		while (curr) {
			cout << curr->data() << ' ';
		}
		cout << endl;
	};

	ListIterator<T>* createIterator();
protected:
	Node<T> * headNode;
	Node<T> * tailNode;

};


template <typename T>
class ListIterator : public IIterator<T>
{
	List<T>* list;
	Node<T> * curr;
	bool done;
public:
	friend class List<T>;
	ListIterator(List<T>* l) {
		list = l;
		curr = l->head();
		done = false;
	}

	void first() {
		curr = list->head();
	};

	T get() {
		return curr->data();
	};

	void next() {
		if (curr->_next) {
			curr = curr->_next;
		}
		else {
			done = true;
		}
	};

	bool isDone() {
		return done;
	}
};

template <typename T>
ListIterator<T>* List<T>::createIterator() {
	return new ListIterator<T>(this);
};

int main() {
	List<int> l;
	l.pushHead(5);
	l.pushHead(10);
	l.pushHead(15);
	l.pushHead(20);
	ListIterator<int> *itl = l.createIterator();
	for (itl->first(); !itl->isDone(); itl->next())
		cout << itl->get() << endl;
	system("pause");
	return 0;
}