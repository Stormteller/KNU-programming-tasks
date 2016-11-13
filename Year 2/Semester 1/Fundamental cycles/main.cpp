#include <stack>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class graph {
	int vNum, eNum;
	vector<vector<int>> matrixGr;

	vector<vector<int>> MST;
	vector<pair<int, int>> notInMst;

	void addMST(int beg, int end, int len = 100);
	void removeMST(int beg, int end);

	void mst();

public:
	graph(vector<vector<int>> matrix, int vertNum, int edgesNum);
	~graph();

	void getFundamentalCycles();

	void printMatrix();
};

void replace(int what, int with, vector<int> &arr) {
	for (unsigned int i = 0; i < arr.size(); i++)
		if (arr[i] == what)
			arr[i] = with;
}

graph::graph(vector<vector<int>> matrix, int vertNum, int edgesNum) {
	matrixGr = matrix;
	vNum = vertNum;
	eNum = edgesNum;
}
graph::~graph() {
	matrixGr.~vector();
}

void graph::addMST(int beg, int end, int len) {
	if (MST[beg][end]) return;
	MST[beg][end] = len;
	MST[end][beg] = len;
}
void graph::removeMST(int beg, int end) {
	if (MST[beg][end]) {
		MST[beg][end] = 0;
		MST[end][beg] = 0;
	}
}

void graph::printMatrix() {
	for (int i = 0; i < vNum; i++) {
		for (int j = 0; j < vNum; j++) {
			cout << matrixGr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void graph::mst() {
	MST.assign(vNum, vector<int>(vNum, 0));

	const int INF = 1000000;

	vector<int> subtrees(vNum);
	for (int i = 0; i < vNum; subtrees[i] = i++);

	vector<vector<int>> matrix = matrixGr;

	for (int e = 0; e < eNum; e++) {
		int min = INF, minBeg, minEnd;

		for (int i = 0; i < vNum; i++) {
			for (int j = i + 1; j < vNum; j++) {
				if (matrix[i][j] && matrix[i][j] < min) {
					min = matrix[i][j];
					minBeg = i; minEnd = j;
				}
			}
		}
		matrix[minBeg][minEnd] = 0;

		if (subtrees[minBeg] != subtrees[minEnd]) {
			replace(subtrees[minEnd], subtrees[minBeg], subtrees);
			MST[minBeg][minEnd] = min;
			MST[minEnd][minBeg] = min;
		}
		else {
			notInMst.push_back(pair<int, int>(minBeg, minEnd));
		}
	}
}

void findCycle(int start, vector<vector<int>> matrix) {
	int vNum = matrix.size();
	vector<int> colors(vNum, 0);
	vector<int> parents(vNum, -1);

	stack<int> vStack;
	vStack.push(start);

	bool foundCycle = false;

	while (!vStack.empty() && !foundCycle) {

		int cur = vStack.top(); vStack.pop();
		colors[cur] = 2;

		for (int i = 0; i < vNum; i++) {
			if (matrix[cur][i] && colors[i] != 2 && parents[cur] != i) {
				if (colors[i] == 1) {
					parents[i] = cur;
					start = i;
					foundCycle = true;
					break;
				}

				else if (colors[i] == 0) {
					parents[i] = cur;
					colors[i] = 1;
					vStack.push(i);
				}
			}
		}
	}

	int cur = start;
	while (parents[cur] != -1) {
		cout << cur << " ";
		cur = parents[cur];
	}
	cout << cur << endl;
}

void graph::getFundamentalCycles() {
	mst();

	for (unsigned i = 0; i < notInMst.size(); i++) {
		int beg = notInMst[i].first;
		int end = notInMst[i].second;

		addMST(beg, end);
		findCycle(beg, MST);
		removeMST(beg, end);
	}
}

int main() {
	ifstream fin("input.txt");
	int vertsNum, edgesNum;
	fin >> vertsNum >> edgesNum;
	vector<vector<int>> matrix;

	matrix.assign(vertsNum, vector<int>(vertsNum, 0));

	vector<int> edges(edgesNum, -1);

	for (int i = 0; i < 2 * edgesNum; i++) {
		int e, v, len;
		fin >> e >> v >> len;
		if (edges[e] == -1) {
			edges[e] = v;
		}
		else {
			matrix[v][edges[e]] = len;
			matrix[edges[e]][v] = len;
		}
	}

	graph gr(matrix, vertsNum, edgesNum);
	gr.printMatrix();
	gr.getFundamentalCycles();

	system("pause");
	return 0;
}