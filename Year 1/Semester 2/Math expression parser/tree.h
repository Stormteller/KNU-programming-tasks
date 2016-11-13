#pragma once

template<class T>
struct Node
{
	T data;
	Node* left, right;
};

template<class T>
class Tree{
	private:
		Node<T> *root;
	public:
		Tree();
		~Tree();
		void add(T);
		void print();
		void remove();
};

template<class T>
Tree<T>::Tree(){
	root = NULL;
}

template<class T>
Tree<T>::~Tree(){

}





