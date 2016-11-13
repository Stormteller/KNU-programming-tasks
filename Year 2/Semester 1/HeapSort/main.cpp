#include <iostream>
#include <fstream>

using namespace std;

const int MAXLEN = 1000;

void swap(int& a, int& b){
	int temp = a;
	a = b;
	b = temp;
}

void heapify(int sortArray[], int curr, int len) {
	int addElem = sortArray[curr];
	
	while (curr <= len / 2) {
		int child = 2 * curr;
		if (child < len && sortArray[child] < sortArray[child + 1]) child++;
		if (addElem >= sortArray[child]) break;
		else {
			swap(sortArray[curr], sortArray[child]);
			curr = child;
		}
	}
	if (curr > 0) heapify(sortArray, curr - 1, len);
}

void heapSort(int sortArray[], int len) {
	//for (int i = len / 2; i >= 0; i--) 
		heapify(sortArray, len / 2, len-1);

	for (int i = len - 1; i > 0; i--) {
		swap(sortArray[0], sortArray[i]);
		heapify(sortArray, 0, i-1);
	}
}



int main() {
	ifstream fin("input.txt");
	int sortArray[MAXLEN] = { 0 };
	int length = 0;
	while (fin >> sortArray[length++]);
	length--;

	heapSort(sortArray, length);

	for (int i = 0; i < length; i++) {
		cout << sortArray[i] << ' ';
	}
	cout << endl;

	system("pause");
	return 0;
}