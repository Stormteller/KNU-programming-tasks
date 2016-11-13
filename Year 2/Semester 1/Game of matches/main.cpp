#include <iostream>

using namespace std;

int main() {
	int n, k;
	cin >> n >> k;
	if (k >= n - 1) cout << n - 1 << endl;
	else cout << ((k >= abs(n % 5 - 1)) ? abs(n % 5 - 1) : 0) << endl;
	system("pause");
	return 0;
}
