#include "queue.h"

Node::Node(int data) {
	prev = nullptr;
	next = nullptr;
	this->data = data;
};

Node::~Node() {};

Queue::Queue() {
	head = nullptr;
	tail = nullptr;
	len = 0;
};

Queue::~Queue() {
	while (!empty()) {
		pop();
	}
};

int Queue::length() {
	return this->len;
};

bool Queue::empty() {
	return !(bool)this->len;
};

Node* Queue::at(int index) {
	if (index <= this->len) {
		Node* curr = this->head;
		for (int i = 0; i < index; i++) curr = curr->next;

		return curr;
	}
	else return nullptr;
};

void Queue::push(Node* node) {
	if (this->len == 0) this->head = node;
	else {
		node->prev = this->tail;
		this->tail->next = node;
	}
	this->tail = node;
	this->len++;
};


void Queue::push(int data) {
	Node* newNode = new Node(data);
	push(newNode);
};

void Queue::pop() {
	if (empty()) return;
	Node* toDel = this->head;
	if(this->head->next)
		this->head = this->head->next;

	this->len--;
	delete toDel;
};

int Queue::back() {
	return this->tail->data;
};

int Queue::front() {
	return this->head->data;
};

void Queue::print() {
	Node* curr = this->head;
	while (curr) {
		std::cout << curr->data << " ";
		curr = curr->next;
	}
	std::cout << std::endl;
};

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
};


/*void Queue::_qSort(int left, int right, int average) {
	int l = left, r = right;
	Node* leftNode = at(l);
	Node* rightNode = at(r);
	
	do
	{
		while (leftNode->data < average && l < r) {
			l++;
			leftNode = leftNode->next;
		}
		while (rightNode->data > average && l < r) {
			r--;
			rightNode = rightNode->prev;
		}
		if (l <= r)
		{
			swap(leftNode->data, rightNode->data);
			l++;
			leftNode = leftNode->next;
			r--;
			rightNode = rightNode->prev;
		}
	} while (l < r);
	if (left < r) _qSort(left, r, average);
	if (l < right) _qSort(l, right, average);
};*/


void Queue::qSort(int left, int right) {
	/*Node* currNode = this->head;
	int sum = 0;
	while (currNode) {
		sum += currNode->data;
		currNode = currNode->next;
	}
	int aver = sum / this->len;

	_qSort(left, right, aver);
	*/
	
	int l = left, r = right;
	Node* leftNode = at(l);
	Node* rightNode = at(r);
	int average = at(l + (r - l) / 2)->data;
	do
	{
		while (leftNode->data < average) {
			l++;
			leftNode = leftNode->next;
		}
		while (rightNode->data > average) {
			r--;
			rightNode = rightNode->prev;
		}
		if (l <= r)
		{
			swap(leftNode->data, rightNode->data);
			l++;
			leftNode = leftNode->next;
			r--;
			rightNode = rightNode->prev;
		}
	} while (l < r);
	if (left < r) qSort(left, r);
	if (l < right) qSort(l, right);


};

void Queue::insSort() {
	Node* iNode = this->head;
	while (iNode) {
		Node* jNode = iNode;
		while (jNode->prev && jNode->data < jNode->prev->data) {
			swap(jNode->data, jNode->prev->data);
			jNode = jNode->prev;
		}
		iNode = iNode->next;
	}
};


