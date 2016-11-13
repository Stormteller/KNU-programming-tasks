#include <iostream>
#include <cmath>

using namespace std; 

const double PI = 3.141592653589793238463;

double cosine(double x, double EPS) {
	double prevSum = 0;
	double currSum = 1;
	double iterator = -x * x / 2;
	const int START_ELEM_COS = 4;
	for (int i = START_ELEM_COS; fabs(iterator) >= EPS; i += 2) {
		prevSum = currSum;
		currSum += iterator;
		iterator *= -((x * x) / (i * (i - 1)));
	}
	return currSum;
}

double sine(double x, double EPS) {
	const int START_ELEM_SINE = 5;
	double prevSum = 0;
	double currSum = x;
	double iterator = -x * x * x / 6;
	for (int i = START_ELEM_SINE; fabs(iterator) >= EPS; i += 2) {
		prevSum = currSum;
		currSum += iterator;
		iterator *= -((x * x) / (i * (i - 1)));
	}
	return currSum;
}

double calcCos(double x, double EPS) {
	bool minus = false;
	bool cosBool = true;
	double result;
	while (x + PI / 4 < EPS || x - PI / 4 > EPS) {
		if (x > 0) {
			x -= PI / 2;
			if (!cosBool) { 
				minus = !minus; 
			}
		}
		else {
			x += PI / 2;
			if (cosBool) { 
				minus = !minus; 
			}
		}
		cosBool = !cosBool;
		
	}

	cosBool ? result = cosine(x, EPS) : result = sine(x, EPS);
	if (minus) {
		result *= -1;
	}

	return result;

}

int main() {
	double arg;
	//cin >> arg;
	//cout << calcCos(arg, 0.0001) << '\n' << cos(arg) << '\n';
	cout << calcCos(PI / 5, 0.001) << '\n' << cos(PI / 5) << endl;

	cout << calcCos(PI / 4, 0.001) << '\n' << cos(PI / 4) << endl;

	cout << calcCos(PI, 0.001) << '\n' << cos(PI) << endl;

	cout << calcCos(15.0, 0.001) << '\n' << cos(15.0) << endl;

	cout << calcCos(100000, 0.001) << '\n' << cos(100000) << endl;

	cout << calcCos(10000, 0.00001) << '\n' << cos(10000) << endl;
	system("pause");
	return 0;
}