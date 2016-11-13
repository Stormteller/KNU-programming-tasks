#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <algorithm>
#include <map>

using namespace std;



struct node {
	node* left; 
	node* right;
	char data;
	int weight;

	node(int weight, char data) {
		this->left = NULL;
		this->right = NULL;
		this->data = data;
		this->weight = weight;
	}

	node(int weight, node* left, node* right) {
		this->left = left;
		this->right = right;
		this->data = '\0';
		this->weight = weight;
	}
	/*
	node(const node*& Node) {
		this->left = Node->left;
		this->right = Node->right;
		this->data = Node->data;
		this->weight = Node->weight;
	}

	node* operator=(const node*& Node) {
		return new node(Node);
	}*/
};



map<char, int> getFrequency(string str) {
	map<char, int> charMap;
	for (int i = 0; i < str.length(); i++) {
		if (!charMap[str[i]]) charMap[str[i]] = 1;
		else charMap[str[i]]++;
	}
	return charMap;
}

class priorQCmp
{
public:
	bool operator() (node* lhs, node* rhs) const
	{
		return (lhs->weight > rhs->weight);
	}
};

node* HuffmanTree(string str) {
	map<char, int> charMap = getFrequency(str);
	string resSrt = "";
	priority_queue<node*, vector<node*>, priorQCmp> priorNodesQ;
	for (auto i = charMap.begin(); i != charMap.end(); i++) {
		priorNodesQ.push(new node(i->second, i->first));
	}
	while (priorNodesQ.size() > 1) {
		node* node1 = priorNodesQ.top();
		priorNodesQ.pop();
		node* node2 = priorNodesQ.top();
		priorNodesQ.pop();
		node* newNode = new node(node1->weight + node2->weight, node1, node2);
		priorNodesQ.push(newNode);
	}
	return priorNodesQ.top();
}

void getCodeMap(node* tree, map<char, string>& map, string currCodeStr) {
	if (tree->data != '\0') {
		map[tree->data] = currCodeStr;
	}
	else {
		if (tree->left) getCodeMap(tree->left, map, currCodeStr + "0");
		if (tree->right) getCodeMap(tree->right, map, currCodeStr + "1");
	}
}

string HuffmanCode(string str, node* huffTree) {
	map<char, string> codeMap;
	string resStr = "";
	if (huffTree->data == '\0') getCodeMap(huffTree, codeMap, "");
	else codeMap[huffTree->data] = "0";
	for (int i = 0; i < str.length(); i++) {
		resStr += codeMap[str[i]];
	}
	return resStr;
}

string HuffmanDecode(string str, node* huffTree) {
	string resStr = "";
	node* currNode = huffTree;
	for (int i = 0; i <= str.length(); i++) {
		if (currNode->data != '\0') {
			resStr += currNode->data;
			currNode = huffTree;
		}
		if (str[i] == '0' && currNode->left) {
			currNode = currNode->left;
		}
		else if(str[i] == '1' && currNode->right) {
			currNode = currNode->right;
		}
	}
	return resStr;
}

int main() {
	ifstream fin("input.txt");
	string str;
	fin >> str;

	node* huffTree = HuffmanTree(str);
	string codedStr = HuffmanCode(str, huffTree);
	string decodedStr = HuffmanDecode(codedStr, huffTree);
	cout << str << '\n' << codedStr << '\n' << decodedStr << '\n';
	system("pause");
	return 0;
}
