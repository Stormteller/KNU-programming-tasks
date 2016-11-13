#include <iostream>

using namespace std;

void bubble(int* a, int n)
{
	for (int i = n - 1; i >= 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (a[j] < a[j + 1])
			{
				int tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
		}
	}
}


int main()
{
	int n;
	int mas[100];
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> mas[i];
	bubble(mas, n);
	for (int i = 0; i < n; i++)
		cout << mas[i] << ' ';

	system("pause");
	return 0;
}