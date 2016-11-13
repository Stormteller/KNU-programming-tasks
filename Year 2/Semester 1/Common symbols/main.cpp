#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

string commonSymbols(string s1, string s2) {
	unordered_map<char, int> subMap;
	string res = "";
	for (int i = 0; i < s1.length(); i++) {
		if (!subMap[s1[i]]) subMap[s1[i]] = 1;
		else subMap[s1[i]] += 1;
	}
	for (int i = 0; i < s2.length(); i++) {
		if (subMap[s2[i]]) { 
			subMap[s2[i]] -= 1; 
			res += s2[i];
		}
	}
	return res;
}

int main() {
	string s1, s2;
	cin >> s1 >> s2;
	cout << commonSymbols(s1, s2) << endl;
	system("pause");
	return 0;
}