#pragma once
#include <iostream>


struct Node {
	Node* prev;
	Node* next;
	int data;

	Node(int data);
	~Node();
};

class Queue {
private:
	Node* head;
	Node* tail;
	int len;
	void _qSort(int, int, int);

public:
	Queue();
	~Queue();

	bool empty();
	int length();

	void push(int);
	void push(Node*);
	void pop();
	Node* at(int);

	int back();
	int front();

	void print();

	void qSort(int, int);
	void insSort();

};