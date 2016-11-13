#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

bool isOp(char op) {
	return op == '+' || op == '-' || op == '*' || op == '/';
};

int priority(char op) {
	return  op == '+' || op == '-' ? 1 :
		op == '*' || op == '/' ? 2 :
		-1;
};

string avoidUnary(string s) {
	if (s[0] == '-' || s[0] == '+') {
		s.insert(s.begin(), '0');
	}
	for (int i = 1; i < s.size(); i++)
	{
		if (s[i - 1] == '(' && (s[i] == '-' || s[i] == '+')) {
			s.insert(s.begin() + i, '0');
		}
	}
	return s;
};

void calcExpr(vector<int>& nums, char op) {
	int r = nums.back();  nums.pop_back();
	int l = nums.back();  nums.pop_back();
	switch (op) {
		case '+':  nums.push_back(l + r);  break;
		case '-':  nums.push_back(l - r);  break;
		case '*':  nums.push_back(l * r);  break;
		case '/':  nums.push_back(l / r);  break;
	}
}

int getPolNotation(string& inputStr) {
	vector<int> nums;
	vector<char> signs;
	string resStr;
	for (int i = 0; i < inputStr.length(); i++)
	{
		char tempSymb = inputStr[i];
		if (isdigit(inputStr[i])) {
			string num = "";
			while (isdigit(inputStr[i])) {
				num.push_back(inputStr[i]);
				i++;
			}
			resStr.append(num);
			nums.push_back(atoi(num.c_str()));
			i--;
			if (isOp(inputStr[i + 1]) || (inputStr[i + 1] == '\0')) resStr.push_back(' ');
		}
		else {
			if (inputStr[i] == '(') {
				signs.push_back(inputStr[i]);
			}
			else {
				if (inputStr[i] == ')') {
					char curr = signs.back();
					while (curr != '(') {
						calcExpr(nums, curr);
						resStr.push_back(curr);
						signs.pop_back();
						curr = signs.back();
					};
					signs.pop_back();
				}
				else {
					if (isOp(inputStr[i])) {
						if (!signs.empty()) {
							while (!signs.empty() && (priority(inputStr[i]) <= priority(signs.back())))
							{
								calcExpr(nums, signs.back());
								resStr.push_back(signs.back());	
								resStr.push_back(' ');
								signs.pop_back();
							}
							signs.push_back(inputStr[i]);
						}
						else {
							signs.push_back(inputStr[i]);
						}
					}

				}
			}
		}
	}
	while (!signs.empty()) {
		calcExpr(nums, signs.back());
		resStr.push_back(signs.back());
		signs.pop_back();
	}
	inputStr = resStr;
	return nums.back();
};




int main()
{
	ifstream fin("input.txt");
	string inputStr;
	fin >> inputStr;
	string noUnary = avoidUnary(inputStr);
	getPolNotation(noUnary);
	cout << inputStr << endl << noUnary << endl << getPolNotation(avoidUnary(inputStr)) << endl;
	system("pause");
	return 0;
}