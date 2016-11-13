#include <cstdlib>
#include <cmath>
#include <limits>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class cubicSpline {
	struct splineSegment {
		double fx;
		double x; 
		double b;  
		double d; 
		double c;  
	};

	int numberOfSegments;
	vector<splineSegment> splines;

public:
	cubicSpline();
	~cubicSpline();

	void buildSpline(vector<double> x, vector<double> fx);

	double f(double x);
};

cubicSpline::cubicSpline() {}

cubicSpline::~cubicSpline() {
	splines.~vector();
}

void cubicSpline::buildSpline(vector<double> x, vector<double> fx) {
	numberOfSegments = x.size();

	splines.assign(numberOfSegments, splineSegment());
	for (auto i = 0; i < numberOfSegments; i++) {
		splines.at(i).x = x.at(i);
		splines.at(i).fx = fx.at(i);
	}

	splines.at(0).c = 0;


	vector<double> P(numberOfSegments, 0), Q(numberOfSegments, 0);

	double dX_i, dX_i1, A, B, C, S;
	for (int i = 1; i < numberOfSegments - 1; i++) {
		dX_i = x[i] - x[i - 1];
		dX_i1 = x[i + 1] - x[i]; 

		A = dX_i;
		B = 2 * (dX_i + dX_i1);
		C = dX_i1;

		S = 6 * ((fx[i + 1] - fx[i]) / dX_i1 - (fx[i] - fx[i - 1]) / dX_i);

		P[i] = -C / (A * P[i - 1] + B);
		Q[i] = (S - A * Q[i - 1]) / (A * P[i - 1] + B);
	}

	splines.back().c = (S - A * Q[numberOfSegments - 2]) / (B + A * P[numberOfSegments - 2]);

	for (auto i = numberOfSegments - 2; i > 0; i--) {
		splines[i].c = P[i] * splines[i + 1].c + Q[i];
	}

	for (auto i = numberOfSegments - 1; i > 0; i--) {
		double dX_i = x[i] - x[i - 1];

		splines[i].d = (splines[i].c - splines[i - 1].c) / dX_i;
		splines[i].b = dX_i * (2 * splines[i].c + splines[i - 1].c) / 6 + (fx[i] - fx[i - 1]) / dX_i;
	}
}

double cubicSpline::f(double x) {
	splineSegment *input_point;

	if (x <= splines.front().x) {
		input_point = &splines.front();
	}

	else if (x >= splines.back().x) {
		input_point = &splines.back();
	}
	else {
		int hi = splines.size() - 1;
		int lo = 0;
		while (hi - lo > 1) {
			int m = (hi + lo) / 2;
			if (x <= splines.at(m).x)
				hi = m;
			else
				lo = m;
		}

		input_point = &splines.at(hi);
	}

	double dx = x - input_point->x;

	double spline_value = input_point->fx + (input_point->b +
		(input_point->c / 2 + input_point->d * dx / 6) * dx) * dx;

	return spline_value;
}

int main() {
	ifstream fin("input.txt");

	cubicSpline mySpline;

	vector<double> xValues, fxValues;


	int numberOfValues;
	fin >> numberOfValues;
	double x, y;

	for (auto i = 0; i < numberOfValues; i++) {
		fin >> x >> y;

		xValues.push_back(x);
		fxValues.push_back(y);
	}

	mySpline.buildSpline(xValues, fxValues);

	cout << mySpline.f(2.5) << '\n';

	system("pause");
	return 0;
}