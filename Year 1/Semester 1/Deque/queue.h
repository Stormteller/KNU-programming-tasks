#pragma once
template <class T>
 
struct Node  {
    T data;
    Node *prev, *next;
};
 
template <class T>class List
{
private:
    Node <T> *pHead, *pTail;
    int count;
public:
    List();//+
    ~List();//+
    void AddHead(T);//+
    void AddTail(T);//+
    void Insert(T, int);//+
    void Print();//+
    int GetSize();//+
    void DelHead();//+
    void DelTail();//+
    void DelPos(int);
    void DelAll();//+
	Node<T>* Find(T); //+
	Node<T>* Head(); //+
	Node<T>* Tail(); //+
};
 
template <class T>
List<T>::List()
{
    pHead = pTail = NULL;
    count = 0;
}

template <class T>
Node<T> * List<T>::Head(){
	return pHead;
}

template <class T>
Node<T> * List<T>::Tail(){
	return pTail;
}
 
template <class T>
void List<T>::AddHead(T value)
{
    Node<T> *temp = new Node<T>;
    temp->data = value;
    temp->prev = NULL;
    temp->next = NULL;
 
    if(pHead!=NULL)
    {
        temp->next = pHead;
        pHead->prev = temp;
        pHead = temp;
    }
    else
    {
        pHead = pTail = temp;
    }
    count++;
}
 
template <class T>
void List<T>::AddTail(T value)
{
    Node<T> *temp = new Node<T>;
    temp->data = value;
    temp->next = NULL;
    temp->prev = NULL;
 
    if(pTail!=NULL)
    {
        temp->prev = pTail;
        pTail->next = temp;
        pTail = temp;
    }
    else
    {
        pTail = pHead = temp;
    }
    count++;
}

template <class T>
Node<T>* List<T>::Find(T value){
	Node<T>* target = pHead;
	while(target)
	{
		if (target->data == value) return target;
		target = target->next;
	}
	return NULL;
}

template <class T>
void List<T>::Insert(T value, int position)
{
    if(position>0 && position<=count)
    {
        if(position == 1)
        {
            AddHead(value);
            return;
        }
        else if(position == count)
        {
            Node<T> *temp = new Node<T>;
            temp->data = value;
            temp->next = NULL;
            temp->prev = NULL;
 
            temp->prev = pTail->prev;
            temp->next = pTail;
            temp->prev->next = temp;
            pTail->prev = temp;
            count++;
            //AddTail(value);
            return;
        }
        int i = 1;
 
        Node<T> *target = pHead;
        Node<T> *temp = new Node<T>;
        temp->data = value;
        temp->next = NULL;
        temp->prev = NULL;
 
        while(i<position)
        {
            target = target->next;
            i++;
        }
        target->prev->next = temp;
        temp->prev = target->prev;
        temp->next = target;
        
        count++;
    }
    else
    {
        cout<<"Error position.\n\tInsert fail!\n";
    }
}
 
template <class T>
void List<T>::Print()
{
    Node<T> *temp = pHead;
    while(temp!=NULL)
    {
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}
 
template <class T>
int List<T>::GetSize()
{
    return count;
}
 
template <class T>
void List<T>::DelHead()
{
    if(pHead!=NULL)
    {
        if(pHead==pTail)  {
            delete pHead;
            pHead = pTail = NULL;
            count = 0;
        }
        else
        {
            Node<T> *temp = pHead;
            pHead = pHead->next;
            pHead->prev = NULL;
            delete temp;
            count--;
        }
    }
    else
    {
        cout<<"\nDelete head fail\n";
    }
}
 
template <class T>
void List<T>::DelTail()
{
    if(pTail!=NULL)
    {
        if(pTail == pHead)
        {
            delete pTail;
            pHead = pTail = NULL;
            count = 0;
        }
        else
        {
            Node<T> *temp = pTail;
            pTail = pTail->prev;
            pTail->next = NULL;
            delete temp;
            count--;
        }
    }
    else
    {
        cout<<"Delete tail fail\n";
    }
}
 
template <class T>
void List<T>::DelPos(int pos)
{
    if(pos>0 && pos<=count)
    {
        if(pos == 1)
        {
            Node<T> *temp = pHead;
            pHead = pHead->next;
            delete temp;
        }
        else
        {
            if(pos == 1 && count == 1)
            {
                delete pHead;
                pHead = pTail = NULL;
            }
            else
            {
                if(pos == count)
                {
                    Node<T> *temp = pTail->prev;
                    temp->next = NULL;
                    delete pTail;
                    pTail = temp;
                    count--;
                    return;
                }
                int i = 1;
                Node<T> *target = pHead;
                while(i<pos)
                {
                    target = target->next;
                    i++;
                }
                Node<T> *prev = target->prev;
                prev->next = target->next;
                target->next->prev = prev;
                delete target;
            }
        }
        count--;
    }
    else
    {
        cout<<"Position error.\ndelete fail\n";
    }
}
 
template <class T>
List<T>::~List()
{
    while(pHead!=NULL)
    {
        Node <T> *temp = pHead;
        pHead = pHead->next;
        delete temp;
    }
    pHead = pTail = NULL;
    count = 0;
}
 
template <class T>
class queue:private List <T> {
public:
    void Pop()  {
        List::DelHead();
    }
    void Push(const T &value)  {
        List::AddTail(value);
    }
    void Print()  {
        List::Print();
    }
    bool IsEmpty()  {
        return List::GetSize == 0;
    }
    int GetSize()  {
        return List::GetSize();
    }
};

template <class T>
class TwoSidesQueue:private List <T> {
public:
    void PopHead()  {
        List::DelHead();
    }
	void PopTail()  {
        List::DelTail();
    }
    void PushHead(const T &value)  {
        List::AddHead(value);
    }
	void PushTail(const T &value)  {
        List::AddTail(value);
    }
    void Print()  {
        List::Print();
    }
    bool IsEmpty()  {
        return List::GetSize == 0;
    }
    int GetSize()  {
        return List::GetSize();
    }
};