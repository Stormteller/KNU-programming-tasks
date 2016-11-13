#pragma once

struct Node {
	int data;
	Node* next;

	Node(int);
	Node();
	~Node();
};

class List {
private: 
	Node* head;
	int len;
	Node* extract(Node*);

public:
	List(int*, int);
	List();
	~List();
	int length();

	void addHead(int);
	void addHead(Node*);
	void addTail(int);
	void addTail(Node*);
	void addIndex(int, int);
	void delTail();
	void delHead();
	void delValue(int);
	void delIndex(int);

	void sliceList(int, List&, List&);
	//Node* find(int);

	void print();
};