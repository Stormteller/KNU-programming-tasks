#pragma once
template <typename T>
class elem{
public:
	T data;
	elem<T> *next;
	elem(T &a):data(a) {};
};

template <typename T>
class Stack
{
private:
	elem<T> * head;
public:
	/*void clearAll();
	Stack();
	bool empty();
	void push(int&);
	void pop();
	void show();*/
Stack()
{
	head = NULL;
}

bool empty()
{
	if(head == NULL) return 1;
	else return 0;
}

void push(int &data)
{
	elem<T> *temp = new elem<T>(data);
	temp->next = head;
	head = temp;
}

void pop()
{
	elem<T> * temp = head;
	head = head ->next;
	delete temp;
}

void show()
{
elem<T> *temp = head;
    while(temp!=NULL)
    {
        std::cout << "Data: "<< temp->data << std::endl;
        temp=temp->next;
    }
}

void clearAll()
{
 elem<T> *temp;
    while(head!=NULL)
    {
        temp=head;
        head=head->next;
        delete temp;
    }
}
};