#include <iostream>
#include <string>
#include <algorithm>


using namespace std;

/*bool isPalindrom(string s) {
	for (int i = 0; i < s.length() / 2; i++) {
		if (s[i] != s[s.length() - i - 1]) return false;
	}
	return true;
}*/

string maxStr(string s1, string s2, string s3)
{
	if (s1.length() > s2.length() || s1.length() > s3.length()) return s1;
	else if (s2.length() > s3.length()) return s2;
	else return s3;
}

string palindrom(string s, int l, int r) {
	if (l > r) return "";
	if (s[l] == s[r]) {
		if (r - l < 3) return s.substr(l, r - l + 1);
		return s[l] + palindrom(s, l + 1, r - 1) + s[r];
	}
	else {
		return maxStr(palindrom(s, l, r - 1), palindrom(s, l + 1, r - 1), palindrom(s, l + 1, r));
	}
}

int main() {
	string s;
	cin >> s;
	cout << palindrom(s, 0, s.length() - 1) << endl;

	system("pause");
	return 0;
}