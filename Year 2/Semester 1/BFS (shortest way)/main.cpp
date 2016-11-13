#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

const int NMAX = 100;

vector<int> BFS_shortest_way(vector<vector<int>> graph, int vertNum, int startVert) {
	queue<int> queueVerts;
	queueVerts.push(startVert);
	vector<bool> used(vertNum + 1);
	vector<int> lengthes(vertNum + 1), parents(vertNum + 1);
	used[startVert] = true;
	parents[startVert] = -1;
	while (!queueVerts.empty()) {
		int v = queueVerts.front();
		queueVerts.pop();
		for (int i = 0; i < graph[v].size(); ++i) {
			int to = graph[v][i];
			if (!used[to]) {
				used[to] = true;
				queueVerts.push(to);
				lengthes[to] = lengthes[v] + 1;
				parents[to] = v;
			}
		}
	}
	return parents;
}


int main() {
	ifstream fin("input.txt");
	int edge, vert;
	int startVert, finishVert;
	int vertNum = 0;
	vector<vector<int>> graph(NMAX);
	unordered_map<int, int> edgeMap(NMAX);
	vector<int> parents;
	fin >> vertNum;
	fin >> startVert >> finishVert;
	while (fin >> edge >> vert) {
		if (!edgeMap[edge]) { edgeMap[edge] = vert; }
		else {
			graph[vert].push_back(edgeMap[edge]);
			graph[edgeMap[edge]].push_back(vert);
			edgeMap.erase(edgeMap.find(edge));
		}
	}
	
	parents = BFS_shortest_way(graph, vertNum, startVert);
	
	vector<int> path;
	for (int vert = finishVert; vert != -1; vert = parents[vert])
		path.push_back(vert);
	reverse(path.begin(), path.end());
	for (int i = 0; i < path.size(); ++i)
		cout << path[i] << " ";
	cout << endl;

	system("pause");
	return 0;
}