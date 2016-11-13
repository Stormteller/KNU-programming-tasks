#include <iostream>

using namespace std;


int A[100001];


int bin_search(int n, int k)
{
	int l = 1;
	int r = n;
	while (l <= r)
	{
		int m = l + (r - l) / 2;
		if (A[m-1] == k) return m;
		else if (A[m-1]>k) r = m - 1;
		else if (A[m-1] < k) l = m + 1;
	}
	return -1;
}

int main()
{
	int n;
	cin >> n;

	int l = 1;
	int r = n;
	int B[100001];
	for (int i = 0; i < n; i++)
	{
		cin >> A[i];
	}
	
	int k;
	cin >> k;
	for (int i = 0; i < k; i++)
	{
		cin >> B[i];
	}
	for (int i = 0; i < k; i++)
	{
		cout << bin_search(n, B[i]) << " ";
	}
	
	system("pause");
	return 0;
}