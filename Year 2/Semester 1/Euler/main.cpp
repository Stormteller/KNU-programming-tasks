#include <fstream>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int NMAX = 100;


void eulerCicle(vector<vector<int>>& graph, int vertNum, int startVert, vector<int>& cicle) {
	int i = 1;
	while (i <= vertNum + 1 && !graph[startVert][i]) i++;
	if (i < vertNum + 1) {
		cicle.push_back(graph[startVert][i]);
		cout << "(" << startVert << " " << i << ") " << graph[startVert][i] << '\n';
		graph[startVert][i] = 0;
		graph[i][startVert] = 0;
		eulerCicle(graph, vertNum, i, cicle);
	}
	
}


int main() {
	ifstream fin("input.txt");
	int edge, vert;
	int vertNum = 0;
	vector<vector<int>> graph (NMAX, vector<int>(NMAX , 0));
	vector<int> cicle;
	map<int, int> edgeMap;
	while (fin >> edge >> vert) {
		if (!edgeMap[edge]) { edgeMap[edge] = vert; }
		else {
			graph[vert][edgeMap[edge]] = edge;
			graph[edgeMap[edge]][vert] = edge;
			edgeMap.erase(edgeMap.find(edge));
		}
		vertNum++;
	}
	vertNum /= 2;

	eulerCicle(graph, vertNum, 1, cicle);


	system("pause");
	return 0;
}