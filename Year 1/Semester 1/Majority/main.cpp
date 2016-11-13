#include <iostream>

using namespace std;
 
int* majority(int ar[], int N)
{
	int confidence = 0; 
	int* candidate = NULL; 
	for (int i = 0; i<N; i++) {
		if (confidence == 0) {
			candidate = ar + i;
			confidence++;
		}

		else if (*candidate == ar[i])
			confidence++;
		else
			confidence--;
	}

	return confidence > 0 ? candidate : NULL;
}

int main()
{
	int n;
	cin >> n;
	int A[100001];
	for (int i = 0; i < n; i++)
		cin >> A[i];
	int* found = majority(A, n);
	if (found != NULL){
	int counter = 0;
	for (int i = 0; i < n; i++)
		if (*found == A[i]) counter++;
	if (counter>(n / 2)) cout << "1" << endl;
	else cout << "0" << endl;
	}
	else cout << "0" << endl;
	system("pause");
	return 0;
}