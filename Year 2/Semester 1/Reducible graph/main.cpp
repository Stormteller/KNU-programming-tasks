#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Graph {
	struct Node {
		bool used = false;
		vector<unsigned int> connections;
	};
	vector<Node> nodes;

	int quantityParents(int curr);

public: 
	Graph(ifstream&);
	void print();
	bool reducible();
};

int Graph::quantityParents(int curr)
{
	int quantity = 0;
	for (int i = 0; i < nodes.size(); i++)
		if (find(nodes[i].connections.begin(), nodes[i].connections.end(), curr) != nodes[i].connections.end()) quantity++;
	return quantity;
}

Graph::Graph(ifstream& fin)
{
	unsigned int quantity;
	//cin >> quantity;
	fin >> quantity;
	nodes.resize(quantity);
	/*Node tmpNode;
	for (unsigned i = 0; i < quantity; i++) nodes.push_back(tmpNode);
	string tmpString;
	getline(cin, tmpString);
	getline(cin, tmpString);
	while (tmpString != ".") {
		unsigned int begin;
		string val;
		for (unsigned i = 0; i < tmpString.size(); i++)
			if (tmpString[i] >= '0' && tmpString[i] <= '9') val += tmpString[i];
			else { begin = stoi(val); val = ""; }
			nodes[begin].connections.push_back(stoi(val));
			getline(cin, tmpString);
	}*/
	int v1, v2;
	while (fin >> v1 >> v2) {
		nodes[v1].connections.push_back(v2);
	}
}

void Graph::print()
{
	cout << "Graph:\n";
	for (unsigned int i = 0; i < nodes.size(); i++) {
		cout << "Node " << i << ": ";
		for (unsigned int j = 0; j < nodes[i].connections.size(); j++)	cout << nodes[i].connections[j] << ' ';
		cout << endl;
	}
}

bool Graph::reducible()
{
	while (nodes.size() > 1) {
		bool stop = true;
		int i = 0;
		for (; i < nodes.size() && nodes[i].connections.size() == 0; i++);
		while (i < nodes.size()) {
			int t = 0;
			while (t < nodes[i].connections.size()) {
				if (quantityParents(nodes[i].connections[t]) == 1) {
					for (int q = 0; q < nodes[nodes[i].connections[t]].connections.size(); q++) {
						if (find(nodes[i].connections.begin(), nodes[i].connections.end(), nodes[nodes[i].connections[t]].connections[q]) == nodes[i].connections.end())

							nodes[i].connections.push_back(nodes[nodes[i].connections[t]].connections[q]);
						nodes[nodes[i].connections[t]].connections.erase(nodes[nodes[i].connections[t]].connections.begin() + q);
					}
					stop = false;
					nodes[i].used = true;
					nodes[nodes[i].connections[t]].used = true;
					nodes[i].connections.erase(nodes[i].connections.begin() + t);
				}
				else t++;
			}
			i++;
		}
		if (stop) {
			for (int t = 0; t < nodes.size(); t++) {
				if (nodes[t].connections.size())
					return false;
				if (!nodes[t].used)
					return false;
			}
			return true;
		}
	}
}


int main() {
	ifstream fin("input.txt");
	Graph myGraph(fin);
	//myGraph.print();
	if (myGraph.reducible()) cout << "Reducible\n";
	else cout << "Not reducible\n";
	system("pause");
	return 0;
}