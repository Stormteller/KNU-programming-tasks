#include <iostream>
#include <string>
using namespace std;

struct node {
	node* left;
	node* right;
	int data;
	node(int k){
		left = right = NULL;
		data = k;
	}
};

int priority(char c){
	return (c == '+' || c == '-') ? 1 : (c == '*' || c == '/') ? 2 : -1;
}



void buildTree(node*& tree, string& s, int l, int r){
	
	if (l != r) {
		if (s[0] == '(' && s[s.length() - 1] == ')') l++, r--;
		int balance = 0;
		for (int i = l; i < r; i++) {
			char c = s[i];
			if (c == '(') balance++;
			if (c == ')') balance--;
			if (priority(c) == 1 && balance == 0) {
				buildTree(tree->left, s, l, i - 1);
			}
		}
	}
}

int main(){

	system("pause");
	return 0;
}