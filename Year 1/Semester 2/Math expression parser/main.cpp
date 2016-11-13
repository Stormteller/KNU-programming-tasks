#include <iostream>
#include <vector>
#include <string>
#include "polNotation.h"
using namespace std;

struct Node{
	string data;
	Node *left, *right;
	Node(string str){
		data = str;
		left = NULL;
		right = NULL;
	};
	Node(){
		left = NULL;
		right = NULL;
	};
};

void addNode(Node *&tree, vector<string> s, int &i){
	if(!tree){
		tree = new Node(s[i--]);
		if((isNumber(tree->data) || isVariable(tree->data))) return;
		if((!tree->right)) addNode(tree->right, s, i);
		if((!tree->left)) addNode(tree->left, s, i);
		return;
	}
};

string calc(Node *&tree){
	if(!tree) return "";
	if(isNumber(tree->data)) return tree->data;
	if(isOp(tree->data)){
		if(tree->data == "+") return to_string(stoi(calc(tree->left)) +  stoi(calc(tree->right)));
		if(tree->data == "*") return to_string(stoi(calc(tree->left)) *  stoi(calc(tree->right)));
		if(tree->data == "-") return to_string(stoi(calc(tree->left)) -  stoi(calc(tree->right)));
		if(tree->data == "/") return to_string(stoi(calc(tree->left)) /  stoi(calc(tree->right)));
	}
};

Node* simplification(Node *&tree){
	if(!tree) return NULL;
	if(isNumber(tree->data) || isVariable(tree->data)) return tree;
	if(isOp(tree->data)){
		if(tree->data == "+") {
			if(isOp(tree->left->data)) simplification(tree->left);
			if(isOp(tree->right->data)) simplification(tree->right);
			if(isNumber(tree->left->data) && isNumber(tree->right->data)){
				tree->data = to_string(stoi(simplification(tree->left)->data) + stoi(simplification(tree->right)->data));
				delete tree->left;
				delete tree->right;
				tree->left = NULL;
				tree->right = NULL;
				return tree;
			}
			if(tree->left->data == "0") {delete tree->left; tree->left = NULL;}
			if(tree->right->data == "0") {delete tree->right; tree->right = NULL;}
		}
		if(tree->data == "-") {
			if(isOp(tree->left->data)) simplification(tree->left);
			if(isOp(tree->right->data)) simplification(tree->right);
			if(isNumber(tree->left->data) && isNumber(tree->right->data)){
				tree->data = to_string(stoi(simplification(tree->left)->data) - stoi(simplification(tree->right)->data));
				delete tree->left;
				delete tree->right;
				tree->left = NULL;
				tree->right = NULL;
				return tree;
			}
			if(isVariable(tree->left->data) && isVariable(tree->right->data) && (tree->right->data == tree->left->data)){
				tree->data = "0";
				delete tree->left;
				delete tree->right;
				tree->left = NULL;
				tree->right = NULL;
				return tree;
			}
			if(tree->left->data == "0") {delete tree->left; tree->left = NULL;}
			if(tree->right->data == "0") {delete tree->right; tree->right = NULL;}
		}
		if(tree->data == "*") {
			if(isOp(tree->left->data)) simplification(tree->left);
			if(isOp(tree->right->data)) simplification(tree->right);
			if(isNumber(tree->left->data) && isNumber(tree->right->data)){
				tree->data = to_string(stoi(simplification(tree->left)->data) * stoi(simplification(tree->right)->data));
				delete tree->left;
				delete tree->right;
				tree->left = NULL;
				tree->right = NULL;
				return tree;
			}
			if((tree->left->data == "0") || (tree->right->data == "0")) {
				delete tree->left;
				tree->left = NULL;
				delete tree->right; 
				tree->right = NULL;
				tree->data = "0";
				return tree;
			}
			if(tree->right->data == "1") {delete tree->right; tree->right = NULL;}
			if(tree->left->data == "1") {delete tree->left; tree->left = NULL;}
		}
		if(tree->data == "/") {
			if(isOp(tree->left->data)) simplification(tree->left);
			if(isOp(tree->right->data)) simplification(tree->right);
			if(tree->right->data == "0") {cout << "ERROR. DIVISION BY 0\n"; return NULL;}
			if(tree->left->data == "0") {
				delete tree->left;
				tree->left = NULL;
				delete tree->right; 
				tree->right = NULL;
				tree->data = "0";
				return tree;
			}
			if(isNumber(tree->left->data) && isNumber(tree->right->data)){
				tree->data = to_string(stoi(simplification(tree->left)->data) / stoi(simplification(tree->right)->data));
				delete tree->left;
				delete tree->right;
				tree->left = NULL;
				tree->right = NULL;
				return tree;
			}
			if(tree->right->data == "1") {delete tree->right; tree->right = NULL;}
		}
	}
};

void writeExpression(Node * tree, string &str, bool brackets){
	
	if(tree->left)
		if(isOp(tree->left->data) && isOp(tree->data)  && (priority(tree->data) > priority(tree->left->data))) writeExpression(tree->left, str, true);
		else writeExpression(tree->left, str, false);
	
	
		str.append(tree->data);
	

	if(tree->right)
		if(isOp(tree->right->data) && isOp(tree->data)  && (priority(tree->data) > priority(tree->right->data))) writeExpression(tree->right, str, true);
		else  writeExpression(tree->right, str, false);
	
	if(brackets) {
		str.insert(0,"(");
		str.push_back(')');
	}
};

//отнимание переменных в разных ветках

int main(){
	Node *Tree = NULL;
	string s = "";
	cin >> s;
	cout << getPolNotation(avoidUnary(s)) << endl;
	vector<string> polNot = strToArray(getPolNotation(avoidUnary(s)),' ');
	int len = polNot.size()-1;
	addNode(Tree, polNot, len);
	simplification(Tree);
	//cout << calc(Tree) <<endl;
	string str = "";
	writeExpression(Tree, str, false);
	cout << str << endl;
	system("pause");
	return 0;
};