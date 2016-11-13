#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>


using namespace std;




bool _checkAcycle(vector< vector<int> > graph, int vert, vector<int> &color, int &cycleVert);

bool checkAcycle(vector< vector<int> > graph, int numVerts);

int maxChildLen(vector< vector<int> > &graph, int vert, vector<int> maxLengthes);

void maxWayLen(vector< vector<int> > &graph, int vert, vector<int> &maxLengthes);

int findMaxWayLenInTree(vector< vector<int> > &graph, int numVerts);



int main() {
	const int NMAX = 100;
	char left, right;
	int iterator = 1;
	int numVerts = 0;
	vector< vector<int> > graph(NMAX);
	map<char, int> mapVert;
	ifstream fin("input.txt");

	while (fin >> left >> right) {
		if (!mapVert[left]) mapVert[left] = iterator++;
		if (!mapVert[right]) mapVert[right] = iterator++;
		graph[mapVert[left]].push_back(mapVert[right]);
	}
	numVerts = mapVert.size();


	if(checkAcycle(graph, numVerts) &&  (findMaxWayLenInTree(graph, numVerts) == numVerts - 1)) {
		cout << "YES" << endl;
	}
	else {
		cout << "NO" << endl;
	}


	system("pause");
	return 0;
}


bool _checkAcycle(vector< vector<int> > graph, int vert, vector<int> &color, int &cycleVert) {
	color[vert] = 1;
	for (int i = 0; i < graph[vert].size(); i++) {
		int to = graph[vert][i];
		if (color[to] == 0) {
			if (_checkAcycle(graph, to, color, cycleVert)) return true;
		}
		else {
			if (color[to] == 1) {
				cycleVert = to;
				return true;
			}
		}
	}
	color[vert] = 2;
	return false;
}

bool checkAcycle(vector< vector<int> > graph, int numVerts) {
	vector<int> color(graph.size(), 0);
	int cycleVert = -1;

	for (int i = 1; i <= numVerts; i++) {
		_checkAcycle(graph, i, color, cycleVert);
	}

	if (cycleVert != -1) return false;
	else return true;
}

int maxChildLen(vector< vector<int> > &graph, int vert, vector<int> maxLengthes) {
	int currMax = -1;
	for (int i = 0; i < graph[vert].size(); i++) {
		int to = graph[vert][i];
		if (maxLengthes[to - 1] == -1) maxWayLen(graph, to, maxLengthes);
		if (maxLengthes[to - 1] > currMax) currMax = maxLengthes[to - 1];
	}
	return currMax;
}

void maxWayLen(vector< vector<int> > &graph, int vert, vector<int> &maxLengthes) {
	if (graph[vert].empty()) {
		maxLengthes[vert - 1] = 0;
	}
	else {
		if (maxLengthes[vert - 1] == -1) {
			maxLengthes[vert - 1] = maxChildLen(graph, vert, maxLengthes) + 1;
		}
	}

}

int findMaxWayLenInTree(vector< vector<int> > &graph, int numVerts) {
	vector<int> maxLengthes(numVerts, -1);
	for (int i = 1; i <= numVerts; i++) {
		maxWayLen(graph, i, maxLengthes);
	}
	return *max_element(begin(maxLengthes), end(maxLengthes));
}