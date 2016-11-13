#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int gcd(int first, int second) {
	while (second != 0) {
		int temp = second;
		second = first % second;
		first = temp;
	}
	return first;
}
int gcd(vector<int> &nums) {
	int res = nums[0];

	for (int i = 1; i <  nums.size() && res != 1; i++) {
		res = gcd(res, nums[i]);
	}

	return res;
}

// a * xg + b * yg = gcd(a,b);

int extended_euclid(int a, int b, int &xg, int &yg) {
	if (a == 0) {
		xg = 0; 
		yg = 1;
		return b;
	}

	int xg_n, yg_n;

	int g = extended_euclid(b % a, a, xg_n, yg_n);

	xg = yg_n - (b / a) * xg_n;
	yg = xg_n;
	return g;
}


void calculate(vector<int> parameters, int freeParam, vector<int>& ans) {	
	int divisor = gcd(parameters);
	if (freeParam % divisor) cout << "No solution!" << endl;

	if (parameters.size() == 2) {
		int a = parameters[0];
		int b = parameters[1];

		int curX, nextX;
		int gcdiv = extended_euclid(a, b, curX, nextX);

		curX *= (freeParam / gcdiv);
		nextX *= (freeParam / gcdiv);

		ans.push_back(curX);
		ans.push_back(nextX);
		return;
	}
	int xi, t;
	int ai = parameters[0];
	int div = extended_euclid(ai, 1, xi, t);

	xi *= (freeParam / div);
	t *= (freeParam / div);

	ans.push_back(xi);

	vector<int> n_param;
	for (int i = 1; i < parameters.size(); i++) {
		n_param.push_back(parameters[i]);
	}
	calculate(n_param, t, ans);
}
int main() {
	ifstream fin("input.txt");
	vector<int> params;
	int freeparam;
	int a;
	while (fin >> a) {
		params.push_back(a);
	}
	freeparam = params.back();
	params.pop_back();
	
	vector<int> ans;

	calculate(params, freeparam, ans);

	for (int i = 0; i < ans.size(); i++) cout << ans[i] << " ";
	cout << endl;

	system("pause");
	return 0;
}