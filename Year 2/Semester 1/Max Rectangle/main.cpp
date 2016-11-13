#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void printMatrix(vector<vector<int>> matrix, int rowSize, int colSize) {
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < colSize; j++) {
			cout << matrix.at(i).at(j) << " ";
		}
		cout << endl;
	}
}
void findMaxRectangle(vector<vector<int>> matrix, int rowSize, int colSize) {
	int topLeftX, topLeftY, bottomRightX, bottomRightY;
	int topLeftXMax = 0, topLeftYMax = 0, bottomRightXMax = 0, bottomRightYMax = 0;
	int maxSum = -INFINITY;

	for (topLeftX = 0; topLeftX < colSize; topLeftX++) {
		for (topLeftY = 0; topLeftY < rowSize; topLeftY++) {
			for (bottomRightX = topLeftX + 1; bottomRightX < colSize; bottomRightX++) {
				for (bottomRightY = topLeftY + 1; bottomRightY < rowSize; bottomRightY++) {
					int currSum =
						matrix[topLeftY][topLeftX] +
						matrix[bottomRightY][topLeftX] +
						matrix[topLeftY][bottomRightX] +
						matrix[bottomRightY][bottomRightX];
					if (currSum > maxSum) {
						topLeftXMax = topLeftX;
						topLeftYMax = topLeftY;
						bottomRightXMax =bottomRightX;
						bottomRightYMax = bottomRightY;
						maxSum = currSum;
					}
				}
			}
		}
	}

	cout << maxSum << endl;
	cout << "(" << topLeftYMax << "," << topLeftXMax << ") (" << bottomRightYMax << "," << bottomRightXMax << ")" << endl;

}

int main() {
	int rowSize, colSize;
	vector<vector<int>> matrix;
	ifstream fin("input.txt");
	fin >> rowSize >> colSize;

	for (int i = 0; i < rowSize; i++) {
		vector<int> currRow;
		for (int j = 0; j < colSize; j++) {
			int data; 
			fin >> data;
			currRow.push_back(data);
		}
		matrix.push_back(currRow);
	}

	printMatrix(matrix, rowSize, colSize);

	findMaxRectangle(matrix, rowSize, colSize);
	system("pause");
	return 0;
};