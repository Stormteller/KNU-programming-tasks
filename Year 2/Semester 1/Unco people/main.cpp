#include <iostream>
#include <fstream>
#include <vector>
//#include "gtest/gtest.h"

using namespace std;

const int NMAX = 100;

bool canDraw(int graph[NMAX][NMAX], int n, int vert, int *colors, int color) {
	bool can = true;
	for (int i = 0; i < n; i++) {
		if (graph[vert][i]) {
			if(colors[i] == color) {
				can = false; 
				break;
			}
		}
	}	
	return can;
}

void colorVert(int *colors, int vert, int color) {
	colors[vert] = color;
}


bool _checkTwoToneColoring(int graph[NMAX][NMAX], int n, int vert, int *colors) {
	bool stillCanDraw = true;
	vector<int> vertsToVisit;
	int currColor = colors[vert];
	//if (canDraw(graph, n, vert, colors, currColor)) {

	currColor == 1 ? currColor = 2 : currColor = 1;
	for (int i = 0; i < n; i++) {
		if (graph[vert][i] && colors[i] == 0) {
			if (!canDraw(graph, n, i, colors, currColor)) {
				stillCanDraw = false;
				break;
			}
			else {
				colorVert(colors, i, currColor);
				vertsToVisit.push_back(i);
			}
		}
	}
	if (stillCanDraw) {
		for (int i = 0; i < vertsToVisit.size(); i++) {
			stillCanDraw = _checkTwoToneColoring(graph, n, vertsToVisit[i], colors);
		}
	}

	//}
	/*else {
		stillCanDraw = false;
	}*/
	return stillCanDraw;
}

bool checkTwoToneColoring(int graph[NMAX][NMAX], int n) {
	int colors[NMAX] = { 0 };
	bool res = true;
	for (int i = 0; i < n; i++) {
		if (colors[i] == 0) {
			colorVert(colors, i, 1);
			res = res && _checkTwoToneColoring(graph, n, i, colors);

		}
	}
	return res;
}
/*
TEST(test4toto, test4toto1) {
	ifstream fin("input.txt");
	int graph[NMAX][NMAX];
	int n;
	fin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fin >> graph[i][j];
		}
	}

	EXPECT_TRUE(checkTwoToneColoring(graph, n));
}
*/

int main(int argc, char **argv) {
	
	ifstream fin("input.txt");
	int graph[NMAX][NMAX];
	int n;
	fin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fin >> graph[i][j];
		}
	}

	if (checkTwoToneColoring(graph, n)) {
		cout << "YES" << endl;
	} 
	else {
		cout << "NO" << endl;
	}
	

	system("pause");
	return 0;
	/*::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();*/
}