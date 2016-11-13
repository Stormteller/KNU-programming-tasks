#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>


using namespace std;

int main(){
	string s;
	int n;
	scanf("%d\n", &n);
	getline(cin,s);
	bool low = false, big = false, num = false, err = false;
	if (s.length() < n) cout << "NO";
	else {
		int i = 0;
		while (i < s.length()){
			if (s[i] >= 'a' && s[i] <= 'z') low = true;
			else if (s[i] >= 'A' && s[i] <= 'Z') big = true;
			else if (s[i] >= '0' && s[i] <= '9') num = true;
			else {err = true; break; }
			i++;
		}
		if (low && num && big && !err) cout << "YES";
		else cout << "NO";
	}
	system("pause");
	return 0;
}