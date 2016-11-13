#include "Stack.h"
#include <iostream>


template <typename T> Stack<T>::Stack()
{
	head = NULL;
}

template <typename T> bool Stack<T>::empty()
{
	if(head == NULL) return 1;
	else return 0;
}

template <typename T> void Stack<T>::push(int &data)
{
	elem<T> *temp = new elem<T>(data);
	temp->next = head;
	head = temp;
}

template <typename T> void Stack<T>::pop()
{
	elem<T> * temp = head;
	head = head ->next;
	delete temp;
}

template <typename T> void Stack<T>::show()
{
elem<T> *temp = head;
    while(temp!=NULL)
    {
        std::cout << "Data: "<< temp->data << std::endl;
        temp=temp->next;
    }
}

template <typename T> void Stack<T>::clearAll()
{
 elem<T> *temp;
    while(head!=NULL)
    {
        temp=head;
        head=head->next;
        delete temp;
    }
}