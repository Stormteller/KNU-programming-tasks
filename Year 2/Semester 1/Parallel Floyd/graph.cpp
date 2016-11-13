#include "graph.h"
#include <iostream>

graph::graph(int** matr, int verts) {
	matrix = matr;
	vertsAmount = verts;
}

//Floyd-Warshall algo for every thread
DWORD WINAPI graph::floyd(parameters* p) {
	int i = p->rowNum;
	SetEvent(p->threadInitFinished);	//Thrad init finished
	for (int k = 0; k < this->vertsAmount; k++) {
		for (int j = 0; j < this->vertsAmount; j++) {
			this->matrix[i][j] = min(this->matrix[i][j], this->matrix[i][k] + this->matrix[k][j]);	//Calc min way lenght
		}
		p->threadBarrier->finish();	//Came to barrier
	}
	return 0;
}

//static method for thread creating
DWORD WINAPI graph::floydWrapper(CONST LPVOID args) {
	parameters* params = (parameters*)args;
	graph *thisGraph = params->gr;	//Current graph
	thisGraph->floyd(params);	//floyd algo with current params
	return 0;
}

void graph::multiThreadFloyd() {
	parameters params(this, this->vertsAmount); //Creating parameters for thread

	HANDLE* hThreads = new HANDLE[this->vertsAmount];	//Threads

	for (int i = 0; i < this->vertsAmount; i++) {
		params.rowNum = i;	//Row for current thread
		ResetEvent(params.threadInitFinished);	//Start new initialization
		hThreads[i] = CreateThread(NULL, 0, &floydWrapper, &params, 0, NULL);	//Thread creating
		WaitForSingleObject(params.threadInitFinished, INFINITE);	//Wait until initialization complete
	}

	WaitForMultipleObjects(this->vertsAmount, hThreads, TRUE, INFINITE);	//Wait until all thread finish
	
	//Close threads
	for (int i = 0; i < this->vertsAmount; i++) {
		CloseHandle(hThreads[i]);	
	}
}

void graph::printMatrix() {
	for (int i = 0; i < this->vertsAmount; i++) {
		for (int j = 0; j < this->vertsAmount; j++)
			std::cout << matrix[i][j] << ' ';
		std::cout << '\n';
	}
}

//Classic Floyd-Warshall algo
void graph::simpleFloyd() {
	for (int k = 0; k < this->vertsAmount; k++)
		for (int i = 0; i < this->vertsAmount; i++)
			for (int j = 0; j < this->vertsAmount; j++)
				matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
}