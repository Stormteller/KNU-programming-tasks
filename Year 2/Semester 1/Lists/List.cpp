#include "List.h"
#include <iostream>

Node::Node(int data) {
	this->data = data;
	this->next = nullptr;
};

Node::Node() {};

Node::~Node() {};

List::List() {
	this->head = nullptr;
	this->len = 0;
};

List::List(int* array, int length) {
	for (int i = length - 1; i >= 0; i--) {
		Node* newNode = new Node(array[i]);
		this->addHead(newNode);
		this->len++;
	}
};

List::~List() {
	Node *toDel;
	while (this->head) {
		toDel = this->head;
		this->head = this->head->next;
		delete toDel;
	}
};

int List::length() {
	return this->len;
};

void List::addHead(int data) {
	Node* newNode = new Node(data);
	addHead(newNode);
};

void List::addHead(Node* node) {
	node->next = this->head;
	this->head = node;
	this->len++;
};

void List::addTail(Node* node) {
	if (!this->head) { 
		this->head = node; 
		this->len++;
		return; 
	}
	
	Node* currNode = this->head;
	while (currNode->next) currNode = currNode->next;
	currNode->next = node;
	this->len++;
};

void List::addTail(int data) {
	Node* newNode = new Node(data);
	addTail(newNode);
};

void List::addIndex(int index, int data) {
	if (index > this->len)  this->addTail(data);
	if (index == 0) { this->addHead(data); return; }

	Node* newNode = new Node(data);

	Node* curr = this->head;
	for (int i = 0; i < index-1; i++) curr = curr->next;
	Node * temp = curr->next;
	curr->next = newNode;
	newNode->next = temp;
	this->len++;
};
/*
Node* List::find(int data) {
	Node* currNode = this->head;
	while (currNode && currNode->data != data) {
		currNode = currNode->next;
	}
	return currNode;
};*/

void List::delHead() {
	if (!this->head) return;

	Node* toDel = this->head;
	this->head = this->head->next;
	delete toDel;
	this->len--;
};

void List::delTail() {
	if (!this->head) return;

	Node* currNode = this->head;
	while (currNode->next->next) currNode = currNode->next;
	delete currNode->next;
	currNode->next = nullptr;
	this->len--;
};

void List::delValue(int data) {
	Node* currNode = this->head;
	while (currNode->next && currNode->next->data != data) {
		currNode = currNode->next;
	}
	Node* toDel = currNode->next;
	currNode->next = currNode->next->next;
	delete toDel;
	this->len--;
};

void List::delIndex(int index) {
	if (index > this->len) return;
	if (index == 1) { this->delHead(); return; }

	Node* curr = this->head;
	for (int i = 0; i < index-2; i++) curr = curr->next;
	Node * toDel = curr->next;
	curr->next = curr->next->next;
	delete toDel;

	this->len--;
};

Node* List::extract(Node* node) {
	if (!node) return nullptr;

	if (node == this->head) {
		this->head = this->head->next;
	}
	else {
		Node* prev = this->head;
		while (prev->next != node) {
			prev = prev->next;
		}
		prev->next = node->next;
	}
	this->len--;
	return node;
}

void List::sliceList(int n, List& greaterList, List& smallerList) {
	Node* currNode = this->head;
	Node* nextNode;
	while (currNode) {
		nextNode = currNode->next;
		if (currNode->data > n) 
			greaterList.addHead(extract(currNode)); 
		else 
			smallerList.addHead(extract(currNode));
		currNode = nextNode;
	}
};

void List::print() {
	Node* currNode = this->head;
	while (currNode) {
		std::cout << currNode << " " << currNode->data << "\n";
		currNode = currNode->next;
	}
	std::cout << "____________________________\n";
	std::cout << std::endl;
}