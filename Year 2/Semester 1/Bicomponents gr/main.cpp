#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

vector<bool> used;
vector<int> order, component;

void dfsGr(int vert, vector<vector<int>> gr) {
	used[vert] = true;
	for (int i = 0; i < gr[vert].size(); i++) {
		if (!used[gr[vert][i]]) {
			dfsGr(gr[vert][i], gr);
		}
	}
	order.push_back(vert);
}

void dfsTransGr(int vert, vector<vector<int>> gr) {
	used[vert] = true;
	component.push_back(vert);
	for (int i = 0; i < gr[vert].size(); i++) {
		if (!used[gr[vert][i]]) {
			dfsTransGr(gr[vert][i], gr);
		}
	}
}

int main() {
	ifstream fin("input.txt");
	int vert1, vert2;
	int verts, edges;
	fin >> verts >> edges;
	vector<vector<int>> allComponents;
	vector<vector<int>> gr(verts), transGr(verts);
	for (int i = 0; i < edges; i++) {
		fin >> vert1 >> vert2;
		gr[vert1].push_back(vert2);
		transGr[vert2].push_back(vert1);
	}
	used.assign(verts, false);
	for (int i = 0; i < verts; i++) {
		if (!used[i]) dfsGr(i, gr);
	}
	used.assign(verts, false);
	for (int i = 0; i < verts; i++) {
		int v = order[verts - 1 - i];
		if (!used[v]) {
			dfsTransGr(v, transGr);
			allComponents.push_back(component);
			for (int j = 0; j < component.size(); j++) {
				cout << component[j] << ' ';
			}
			cout << endl;
			component.clear();
		}
	}
	system("pause");
	return 0;
}