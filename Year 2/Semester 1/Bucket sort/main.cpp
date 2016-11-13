#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <time.h>

using namespace std;

int iterations = 0;

int getLength(int src) {
	int ans = 0;
	do {
		ans++;
		src /= 10;
	} while ( src > 0 );
	return ans - 1;
}

int getDigit(int src, int pos) {
	int ans = int(src / pow(10, pos)) % 10;
	return ans;
}

void bucketSort(vector<int> &data) {
	iterations = 0;
	int maxPos = -1;
	for (int i = 0; i < data.size(); i++) {
		int pos = getLength(data[i]);
		if (pos > maxPos) maxPos = pos;
	}

	for (int i = 0; i <= maxPos; i++) {

		vector<vector<int>> buckets(10);

		for (int j = 0; j < data.size(); j++) {
			int bucketNumber = getDigit(data[j], i);
			buckets[bucketNumber].push_back(data[j]);
			iterations++;
		}

		for (int j = 0; j < 10; j++) {
			int bucketLen = buckets[j].size();
			for (int k = 0; k < bucketLen; k++) {
				cout << buckets[j][k] << ' ';
			}
			cout << '0' << endl;
		}
		cout << "____________" << endl;


		data.resize(0);
		for (int j = 0; j < 10; j++) {
			int bucketLen = buckets[j].size();
			for (int k = 0; k < bucketLen; k++) {
				data.push_back(buckets[j][k]);
				iterations++;
			}
		}
	}

	for (int i = 0; i < data.size(); i++) {
		cout << data[i] << " ";
	}
	cout << endl;
	cout << "Iterations: " << iterations << endl;
}

int main() {
	vector<int> data = { 18, 15, 35, 5, 79, 25, 98, 74 };
	vector<int> arr1;
	/*ifstream fin("input.txt");
	int dat;
	while (fin >> dat) {
		arr1.push_back(dat);
	}
	/*srand(time(NULL));
	for (int i = 0; i < 50; i++) {
		data.push_back(rand() % 100);
	}*/
	
	for (int i = 0; i < data.size(); i++) {
		cout << data[i] << " ";
	}
	cout << endl;

	bucketSort(data);
	//bucketSort(arr1);

	system("Pause");
	return 0;
}