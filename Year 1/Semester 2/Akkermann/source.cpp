#include <iostream>

using namespace std;

int Akkerman(int n, int x, int y)
{
	if (n == 0) return x + 1;
	else if ((y == 0) && (n == 1)) return x;
	else if ((y == 0) && (n == 2)) return 0;
	else if ((y == 0) && (n == 3)) return 1;
	else if ((y == 0) && (n >= 4)) return 2;
	else if (n != 0 && y != 0) return Akkerman(n - 1, Akkerman(n,x, y - 1),x);
}

int main()
{
	int n,x,y;
	cin >> n >> x >> y;
	cout << Akkerman(n, x, y) << endl;
	system("pause");
	return 0;
}