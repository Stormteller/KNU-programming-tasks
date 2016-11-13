#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int decomp(long long n, int m)
{
	int res = 0;
	while (n % m == 0)
	{
		n /= m;
		res++;
	}
	return res;
}

int main()
{
	long long a, b;
	cout << "Input a and b" << endl;
	cin >> a;
	cin >> b;
	float res = (float)(a) / b;
	a = abs(a);
	b = abs(b);
	if (b != 0) {
		string mantiss="";
		string out="";
		while (a >= b) a = a - b;
		for (int i = 0; i < max(decomp(b, 2), decomp(b, 5)); i++)
		{
			a = a * 10;
			if (a < b)
			{
				out += 48;
				continue;
			}
			int temp = (int)(a / b);
			a -= b * temp;
		    out += temp + 48;
		}
		long long remainder = a;
		do
		{
			a = a * 10;
			if (a < b)
			{
				mantiss += '0';
				continue;
			}
			int temp = (int)(a / b);
			a -= b * temp;
			mantiss += (char)(temp + 48);
		} while (remainder != a);
		if (mantiss == "0")
		{
			cout << "No period. a/b = " << res << endl;
		}
		else
		{
			cout << "a/b = " << (int)res << "." << out;
			cout << "(" << mantiss << ")" << endl;
		}
	}
	else cout << "Error. Division by 0" << endl;

	system("pause");
	return 0;
}