#include "binLong.h"

using namespace std;

int main() {
	//cout << bl.numToStr() << '\n';
	binLong res = binLong("+10000") + binLong("-1");
	res.print();
	system("pause");
	return 0;
}