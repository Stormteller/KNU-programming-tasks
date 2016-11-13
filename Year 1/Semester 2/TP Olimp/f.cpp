#include <iostream>
#include <cmath>
using namespace std;

const int val[10] = { 16, 22, 4, 17, 19, 24, 20, 8, 14, 15 };

int main(){
	short n, p1;
	unsigned long long p2, h;
	unsigned long long a[10] = {}, step[10] = {};
	cin >> n;
	cin >> p1;
	cin >> p2;
	cin >> h;
	step[0] = 1;
	step[1] = p1;
	for (int i = 2; i < n; ++i)
		step[i] = step[i - 1] * step[1];
	for (int a1 = 0; a1 < 10; ++a1){
		a[0] = (val[a1] * step[0]) % p2;
		if (n > 1)
			for (int a2 = 0; a2 < 10; ++a2){
				a[1] = (a[0] + val[a2] * step[1]) % p2;
				if (n > 2)
					for (int a3 = 0; a3 < 10; ++a3){
						a[2] = (a[1] + val[a3] * step[2]) % p2;
						if (n > 3)
							for (int a4 = 0; a4 < 10; ++a4){
								a[3] = (a[2] + val[a4] * step[3]) % p2;
								if (n > 4)
									for (int a5 = 0; a5 < 10; ++a5){
										a[4] = (a[3] + val[a5] * step[4]) % p2;
										if (n > 5)
											for (int a6 = 0; a6 < 10; ++a6){
												a[5] = (a[4] + val[a6] * step[5]) % p2;
												if (n>6)
													for (int a7 = 0; a7<10; ++a7)
													{
														a[6] = (a[5] + val[a7] * step[6]) % p2;
														if (n>7)
															for (int a8 = 0; a8<10; ++a8)
															{
																a[7] = (a[6] + val[a8] * step[7]) % p2;
																if (a[7] == h)
																	cout << (char)(val[a1] + 'a') << (char)(val[a2] + 'a') << (char)(val[a3] + 'a') << (char)(val[a4] + 'a') <<
																	(char)(val[a5] + 'a') << (char)(val[a6] + 'a') << (char)(val[a7] + 'a') << (char)(val[a8] + 'a') << endl;
															}
														else
															if (a[6] == h)
																cout << (char)(val[a1] + 'a') << (char)(val[a2] + 'a') << (char)(val[a3] + 'a') << (char)(val[a4] + 'a') <<
																(char)(val[a5] + 'a') << (char)(val[a6] + 'a') << (char)(val[a7] + 'a') << endl;
													}
												else
													if (a[5] == h)
														cout << (char)(val[a1] + 'a') << (char)(val[a2] + 'a') << (char)(val[a3] + 'a') << (char)(val[a4] + 'a') <<
														(char)(val[a5] + 'a') << (char)(val[a6] + 'a') << endl;
											}
										else
											if (a[4] == h)
												cout << (char)(val[a1] + 'a') << (char)(val[a2] + 'a') << (char)(val[a3] + 'a') << (char)(val[a4] + 'a') <<
												(char)(val[a5] + 'a') << endl;
									}
								else
									if (a[3] == h)
										cout << (char)(val[a1] + 'a') << (char)(val[a2] + 'a') << (char)(val[a3] + 'a') << (char)(val[a4] + 'a') << endl;
							}
						else
							if (a[2] == h)
								cout << (char)(val[a1] + 'a') << (char)(val[a2] + 'a') << (char)(val[a3] + 'a') << endl;
					}
				else
					if (a[1] == h)
						cout << (char)(val[a1] + 'a') << (char)(val[a2] + 'a') << endl;
			}
		else
			if (a[0] == h)
				cout << (char)(val[a1] + 'a') << endl;
	}
	return 0;
}