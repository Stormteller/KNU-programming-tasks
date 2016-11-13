#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 20;

vector<int> graph[MAXN];
bool used[MAXN] = { false };
int tin[MAXN], up[MAXN], edges, vertex, timer = 0;

void add_vert(int v1, int v2){
	graph[v1].push_back(v2);
	graph[v2].push_back(v1);
}


void dfs(int v, int p){
	used[v] = true;
	tin[v] = up[v] = timer++;
	for (int i = 0; i < graph[v].size(); i++){
		int to = graph[v][i];
		if (to == p) continue;
		if (used[to]){
			up[v] = min(up[v], tin[to]);
		}
		else {
			dfs(to, v);
			up[v] = min(up[v], up[to]);
			if (up[to] > tin[v]){
				cout << v << ' ' << to << endl;
			}
		}
	}
}

void find_bridges(){
	timer = 0;
	for (int i = 0; i < vertex; ++i)
		used[i] = false;
	for (int i = 1; i <= vertex; ++i)
		if (!used[i]) dfs(i, -1);
}

int main(){
	int v1,v2;
	ifstream fin("in.txt");
	fin >> edges;
	fin >> vertex;
	for (int i = 0; i < edges; i++){
		fin >> v1 >> v2;
		add_vert(v1,v2);
	}
	find_bridges();
	system("pause");
	return 0;
}