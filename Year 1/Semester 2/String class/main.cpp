#include <iostream>
#include "myString.h"
using namespace std;

int main()
{
	myString s1("aa");
	myString s2;
	cin >> s2;
	myString s3 = s1 + "sosu";
	system("pause");
	return 0;
}