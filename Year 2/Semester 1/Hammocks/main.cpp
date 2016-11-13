#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Graph {
	class Node {
	public: vector<unsigned int> connections;
			vector<unsigned int> paths;
	};
	vector<Node> nodes;
	vector<unsigned int> hammock;

public: Graph() {
	unsigned int quantity;
	cout << "Enter quantity of nodes: ";
	cin >> quantity;
	Node tmpNode;
	for (unsigned i = 0; i < quantity; i++) nodes.push_back(tmpNode);
	cout << "Enter edges:\n";
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
	}
}

		void print() {
			cout << "Graph:\n";
			for (unsigned int i = 0; i < nodes.size(); i++) {
				cout << "Node " << i << ": ";
				for (unsigned int j = 0; j < nodes[i].connections.size(); j++)	cout << nodes[i].connections[j] << ' ';
				cout << endl;
			}
		}

		void makePath() {
			for (unsigned int i = 0; i < nodes.size(); i++) addNodeToPath(i, i);
		}

		void findHammock() {
			for (unsigned int i = 0; i < nodes.size(); i++)
				for (unsigned int j = 0; j < nodes[i].paths.size(); j++) {
					if (isHammock(i, nodes[i].paths[j])) {
						cout << "Hammock: ";
						for (unsigned int t = 0; t < hammock.size(); t++) cout << hammock[t] << ' ';
						cout << nodes[i].paths[j] << endl;
					}
					hammock.clear();
				}
		}

private: void addNodeToPath(unsigned int &begin, unsigned int &cur) {
	for (unsigned int i = 0; i < nodes[cur].connections.size(); i++) {
		if (begin != nodes[cur].connections[i] && find(nodes[begin].paths.begin(), nodes[begin].paths.end(), nodes[cur].connections[i]) == nodes[begin].paths.end()) {
			nodes[begin].paths.push_back(nodes[cur].connections[i]);
			addNodeToPath(begin, nodes[cur].connections[i]);
		}
	}
}

		 bool isHammock(unsigned int &begin, unsigned int &end) {
			 vector<unsigned int> path;
			 if (beginEnd(begin, end, path) && inside()) return true;
			 return false;
		 }

		 bool beginEnd(unsigned int &cur, unsigned int &end, vector<unsigned int> path) {
			 if (cur != end) {
				 if (nodes[cur].connections.size()) {
					 if (find(path.begin(), path.end(), cur) == path.end()) {
						 if (find(hammock.begin(), hammock.end(), cur) == hammock.end()) hammock.push_back(cur);
						 path.push_back(cur);
						 for (unsigned int i = 0; i < nodes[cur].connections.size(); i++) if (!beginEnd(nodes[cur].connections[i], end, path)) return false;
					 }
					 else if (find(nodes[end].paths.begin(), nodes[end].paths.end(), cur) == nodes[end].paths.end() && find(nodes[cur].paths.begin(), nodes[cur].paths.end(), end) != nodes[cur].paths.end()) return true;
					 else return false;
				 }
				 else return false;
			 }
			 return true;
		 }

		 bool inside() {
			 for (unsigned int i = 0; i < nodes.size(); i++)
				 if (find(hammock.begin(), hammock.end(), i) == hammock.end())
					 for (unsigned int j = 0; j < nodes[i].connections.size(); j++)
						 if (hammock.size() && find(hammock.begin() + 1, hammock.end(), nodes[i].connections[j]) != hammock.end()) return false;
			 return true;
		 }
};

int main() {
	Graph myGraph;
	//	myGraph.print();
	myGraph.makePath();
	myGraph.findHammock();
	system("pause");
	return 0;
}