#include <iostream>

using namespace std;

int main()
{
	char s[1000];
	cin >> s;
	int cur = 0;
	int prev = 0;
	int len = strlen(s);
	char c = s[0];
	for (int i = 0; i < len; i++)
	{
		char p = c;
		c = s[i + 1];
		if ((s[i] != 'I') && (s[i] != 'V') && (s[i] != 'X') && (s[i] != 'L') && (s[i] != 'C') &&(s[i] != 'D') && (s[i] != 'M')) return 1;
	}
	int res = 0;
	int temp = 0;
	for (int i = 0; i < len; i++)
	{
		prev = cur;
		if (s[i] == 'I') cur = 1;
		if (s[i] == 'V') cur = 5;
		if (s[i] == 'X') cur = 10;
		if (s[i] == 'L') cur = 50;
		if (s[i] == 'C') cur = 100;
		if (s[i] == 'D') cur = 500;
		if (s[i] == 'M') cur = 1000;
		if (prev < cur) temp = -2 * prev;
		else temp = 0;
		res += temp + cur;
	}
	cout << res << endl;
	system("pause");
	return 0;
}