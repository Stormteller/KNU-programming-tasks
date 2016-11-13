#include <iostream>
#include <fstream>
#include <iostream>
#include "function.h"

using namespace std;

int main() {
	ifstream fin("input.txt");	//input file
	function func(fin);
	vector<double> startX;	//Set start point
	int data;
	int n;
	cout << "Enter number of coordinates:\n";
	cin >> n;
	cout << "Start point coords:\n";
	for (int i = 0; i < n; i++) {
		cin >> data;
		startX.push_back(data);
	} 
	cout << endl;
	vector<double> ans = func.gradientDescent(startX);
	cout << "Value: " << -func.value(ans) << endl;	// Because used -F(x)
	cout << "Point: ";
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << ' ';
	system("pause");
	return 0;
}