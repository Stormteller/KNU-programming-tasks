#pragma once
#include "barrier.h"

class graph {
public:
	//Parameters for threads
	struct parameters {
		int rowNum;	//Amount of rows in matrix = Amount of vertexes
		graph* gr;	//Graph

		HANDLE threadInitFinished;	//Event for thread init finishing

		barrier* threadBarrier;	//Barrier

		parameters(graph* g, int barMaxN) {
			this->threadBarrier = new barrier(barMaxN);
			this->gr = g;
			this->threadInitFinished = CreateEvent(NULL, TRUE, FALSE, NULL);
		}
	};

	int** matrix;	//Adjacency matrix
	int vertsAmount;	//Amount of vertexes

	graph(int** matr, int verts);

	DWORD WINAPI floyd(parameters* p);	//Floyd-Warshall algo for every thread

	static DWORD WINAPI floydWrapper(CONST LPVOID args); //Wrapper for multi-threading

	void multiThreadFloyd();	//Floyd-Warshall algo with multi-threading

	void printMatrix();	//Print adjacency matrix

	void simpleFloyd();	//Floyd-Warshall algo without multi-threading

};