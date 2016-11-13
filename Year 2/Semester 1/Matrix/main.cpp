#include <iostream>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

struct elem {
	int col, row, data;

	elem(int row, int col, int data) {
		this->col = col;
		this->row = row;
		this->data = data;
	};
};


void printMatrix(list <list<elem>> matrix, int n, int m) {
	vector<vector<int>> full (n, vector<int>(m, 0));
	
	for (list<list<elem>>::iterator i = matrix.begin(); i != matrix.end(); i++) {
		for (list<elem>::iterator j = i->begin(); j != i->end(); j++) {
			full[j->row][j->col] = j->data;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << full[i][j] << " ";
		}
		cout << endl;
	}
};

elem findMax(list <list<elem>> matrix) {
	elem* max = new elem(0, 0, 0);

	for (list<list<elem>>::iterator i = matrix.begin(); i != matrix.end(); i++) {
		for (list<elem>::iterator j = i->begin(); j != i->end(); j++) {
			if (j->data > max->data) {
				*max = *j;
			}
		}
	}

	return *max;
}

void deleteMax(list <list<elem>>& matrix, int& n, int& m) {
	elem max = findMax(matrix);

	for (list<list<elem>>::iterator i = matrix.begin(); i != matrix.end();) {
		for (list<elem>::iterator j = i->begin(); j != i->end();) {
			if (j->col == max.col || j->row == max.row) {
				list<elem>::iterator toDel = j;
				j++;
				i->erase(toDel);
			}
			else {
				if (j->col > max.col) j->col--;
				if (j->row > max.row) j->row--;
				j++;
			}
		}
		if (i->empty()) {
			list<list<elem>>::iterator toDel = i;
			i++;
			matrix.erase(toDel);
		}
		else i++;
	}
	n--;
	m--;
};

int main() {
	list <list<elem>> matrix;
	int n, m;
	ifstream fin("input.txt");

	fin >> n >> m;
	for (int i = 0; i < n; i++) {
		list<elem> currRow;
		int bufData;
		for (int j = 0; j < m; j++) {
			fin >> bufData;
			if (bufData) currRow.push_back(elem(i, j, bufData));
		}
		//if (!currRow.empty()) {
			matrix.push_back(currRow);
		/*} else {
		}*/
	}

	printMatrix(matrix, n, m);

	deleteMax(matrix, n, m);

	cout << "\n_____________________\n";

	printMatrix(matrix, n, m);

	system("pause");
	return 0;
};