#include <iostream>
#include <ctime>

using namespace std;

float f(float x, float y) {
	return x*x + y*y;
}

int main() {
	srand(time(0));
	const float xBot = 0.5, xTop = 1;
	const float yBot = 0, yTop = 2 * xTop - 1;
	const int iterations = 10000;
	float yCheckTop, yCheckBot;
	float xCurr, yCurr;
	float sum = 0;
	float res;


	yCheckBot = 0;
	for (int i = 0; i < iterations; i++) {
		xCurr = xBot + (xTop - xBot) * (float(rand()) / RAND_MAX);
		yCurr = yBot + (yTop - yBot) * (float(rand()) / RAND_MAX);

		yCheckTop = 2 * xCurr - 1;

		if ((yCurr > yCheckBot) && (yCurr < yCheckTop))
			sum += f(xCurr, yCurr); 
	}

	res = sum * (xTop - xBot) * (yTop - yBot) / iterations;

	cout << res << endl;

	system("pause");
	return 0;
}