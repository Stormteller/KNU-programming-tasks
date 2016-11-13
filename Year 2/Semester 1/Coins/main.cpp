#include <iostream>
using namespace std;

void solve(int N, int M, int S, int K, int L)
{
	int *order = new int[N + M];
	int orig = 0;
	int curr_pos = S - 1;
	for (int i = 0; i < N + M; i++)
		order[i] = false;
	while (K--) //check what positions will change
	{
		order[curr_pos] ^= true;
		curr_pos += S;
		if (curr_pos >= N + M) curr_pos -= N + M;
	}
	for (int i = 0; i < N + M; i++)
		if (order[i]) orig++;
	if (abs(N - L) > orig || abs(N - L) % 2 != orig % 2)
		cout << "There are no such order" << endl;
	else {
		int count = 0, n = N, ups = 0, ds = 0;
		for (int i = 0; i < N + M; i++) {
			if (order[i]) {
				if (n >= L) {
					order[i] = 3; //3 == upside
					n--;
					ds++;
				}
				else if (n < L) {
					order[i] = 2; //2 == downside
					n++;
					ups++;
				}
			}
		}
		for (int i = 0; i < N + M; i++) {
			if (!order[i] && M - ds) {
				order[i] = 3; 
				ds++;
			}
			else if (!order[i] && N - ups) {
				order[i] = 2; 
				ups++;
			}
		}
		for (int i = 0; i < N + M; i++)
			cout << order[i] << " ";
		cout << endl;
	}
}

int main()
{
	int N, M, S, K, L;
	cout << "Enter values: upside coins, downside coins, "
		<< "step, moves, final upside coins number" << endl;
	cin >> N >> M >> S >> K >> L;
	if (abs(N - L) > K || L > (N + M))
		cout << "There are no such order" << endl;
	else solve(N, M, S, K, L);
	system("pause");
}