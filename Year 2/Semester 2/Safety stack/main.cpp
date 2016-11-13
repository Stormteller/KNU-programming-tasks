#include <iostream>

using namespace std;

template<typename T>
class Stack {
	template<typename T>
	struct Node {
		Node<T>* next;
		Node<T>* prev;
		T data;
		Node(T d) {
			next = NULL;
			prev = NULL;
			data = d;
		}
	};

	Node<T>* head;
	int capacity;
	int len;

public:
	Stack() {
		capacity = 0;
		len = 0;
		head = NULL;
	}

	Stack(T cap) {
		capacity = cap;
		len = 0;
		head = NULL;
	}

	void push(T data) {
		if (capacity && capacity == len) {
			throw overflow_error("Stack overflow");
		}
		else {
			Node<T>* newNode = new Node<T>(data);
			if (!head) {
				head = newNode;
			}
			else {
				head->next = newNode;
				newNode->prev = head;
				head = newNode;
			}
			len++;
		}
	}

	T pop() {
		if (len == 0) {
			throw underflow_error("Stack is empty");
		}
		else {
			T delData;
			if (!head->prev) {
				delData = head->data;
				delete head;
				head = NULL;
			}
			else {
				Node<T>* toDel = head;
				delData = toDel->data;
				head = head->prev;
				head->next = NULL;
				delete toDel;
			}
			len--;
			return delData;
		}
	}
};

int main() {
	Stack<int> stack(3);
	stack.push(5);
	stack.push(3);
	stack.push(2);
	cout << stack.pop() << stack.pop() << stack.pop();
	system("pause");
	return 0;
}