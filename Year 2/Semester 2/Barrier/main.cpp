#include "barrier.h"
#include "graph.h"
#include <fstream>
#include <iostream>
#include <time.h>

using namespace std;


INT main() {
	const int INF = 100000;
	ifstream fin("input.txt");
	int n, a;
	fin >> n;
	int** matrix = new int*[n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new int[n];
		for (int j = 0; j < n; j++) {
			fin >> a;
			if (a == 0) a = INF;
			matrix[i][j] = a;
		}
	}
	graph gr(matrix, n);
	//gr.printMatrix();
	clock_t time;
	time = clock();
	gr.multiThreadFloyd();
	//gr.simpleFloyd();
	time = clock() - time;
	cout << "Time: " << (double)time / CLOCKS_PER_SEC << endl;
	gr.printMatrix();
	system("pause");
	return 0;
}