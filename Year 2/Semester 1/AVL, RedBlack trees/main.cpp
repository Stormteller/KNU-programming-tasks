#include <iostream>
#include <fstream>

using namespace std;

struct Node
{
	int key;
	unsigned char height;
	Node* left;
	Node* right;
	Node(int k) {
		key = k;
		left = right = NULL;
		height = 1;
	}
};

unsigned char height(Node* p)
{
	return p ? p->height : 0;
}

int bfactor(Node* p)
{
	return height(p->right) - height(p->left);
}

void fix_height(Node* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl>hr ? hl : hr) + 1;
}

Node* rotate_right(Node* p)
{
	Node* q = p->left;
	p->left = q->right;
	q->right = p;
	fix_height(p);
	fix_height(q);
	return q;
}

Node* rotate_left(Node* q)
{
	Node* p = q->right;
	q->right = p->left;
	p->left = q;
	fix_height(q);
	fix_height(p);
	return p;
}

Node* balance(Node* p)
{
	fix_height(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotate_right(p->right);
		return rotate_left(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotate_left(p->left);
		return rotate_right(p);
	}
	return p;
}

Node* insert(Node*& p, int k)
{
	if (!p) return new Node(k);
	if (k<p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}

Node* findmin(Node* p)
{
	return p->left ? findmin(p->left) : p;
}

Node* removemin(Node* p)
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

Node* remove(Node* p, int k)
{
	if (!p) return 0;
	if (k < p->key)
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else
	{
		Node* q = p->left;
		Node* r = p->right;
		delete p;
		if (!r) return q;
		Node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

void print_tree(Node *p, int level)
{
	if (p)
	{
		print_tree(p->left, level + 1);
		for (int i = 0; i< level; i++) cout << "   ";
		cout << p->key << endl;
		print_tree(p->right, level + 1);
	}
}

int main() {

	system("pause");
	return 0;
}