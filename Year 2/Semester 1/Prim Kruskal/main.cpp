#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;


bool cmpForSort(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) {
	return a.first < b.first;
}

struct cmpForPriorityQ {
	bool operator()(const pair<int, pair<int, int>>& a, const pair<int, pair<int, int>>& b) const {
		return a.first > b.first;
	};
};


vector<pair<int, int>> Kruskal(vector<pair<int, pair<int, int>>> graph, int m, int n) {
	vector<pair<int, int>> res;
	sort(graph.begin(), graph.end(), cmpForSort);
	vector<int> tree(n);
	for (int i = 0; i < n; i++) {
		tree[i] = i;
	}
	for (int i = 0; i < m; i++) {
		int vert1 = graph[i].second.first;
		int vert2 = graph[i].second.second;
		int weight = graph[i].first;

		if (tree[vert1] != tree[vert2]) {
			res.push_back(pair<int, int>(vert1, vert2));
			int old_tree = tree[vert2];
			int new_tree = tree[vert1];
			for (int j = 0; j < n; j++)
				if (tree[j] == old_tree) {
					tree[j] = new_tree;
				}
		}
	}
	return res;
}

vector<pair <int, int>> Prim(vector<pair<int, pair<int, int>>> graph, int m, int n) {
	vector<bool> used(n);
	int INF = 10000000;
	vector<pair<int, int>> res;
	vector<int> minEdges(n, INF), endsOfMinEdges(n, -1);
	minEdges[0] = 0;
	for (int i = 0; i < n; ++i) {
		int vert = -1;
		for (int j = 0; j < n; ++j) {
			if (!used[j] && (vert == -1 || minEdges[j] < minEdges[vert])) {
				vert = j;
			}
		}
		if (minEdges[vert] == INF) {
			cout << "No MST!";
			return res;
		}

		used[vert] = true;
		if (endsOfMinEdges[vert] != -1)
			res.push_back(pair<int, int>(vert, endsOfMinEdges[vert]));

		for (int j = 0; j < m; j++) {
			if (graph[j].second.first == vert && graph[j].first < minEdges[graph[j].second.second]) {
				minEdges[graph[j].second.second] = graph[j].first;
				endsOfMinEdges[graph[j].second.second] = vert;
			}
		}
	}

	return res;
}

int main() {
	vector<pair<int, pair<int, int>>> graph;
	int m, n;
	ifstream fin("input.txt");
	fin >> m >> n;
	int v1, v2, w;
	for (int i = 0; i < m; i++) {
		fin >> v1 >> v2 >> w;
		pair<int, pair<int, int>> edge1(w, pair<int, int>(v1, v2));
		graph.push_back(edge1);
	}
	for (int i = 0; i < graph.size(); i++) 
		cout << graph[i].first << ' ' << graph[i].second.first << ' ' << graph[i].second.second << '\n';
	vector<pair<int, int>> kruskalRes = Kruskal(graph, m, n);
	vector<pair<int, int>> primlRes = Prim(graph, m, n);
	for (int i = 0; i < primlRes.size(); i++)
		cout << primlRes[i].first << ' ' << primlRes[i].second << '\n';
	
	

	system("pause");
	return 0;
}