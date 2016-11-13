#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool isOp(char op){
	return op == '+' || op == '-'|| op == '*' || op == '/';
};

int priority(char op){
	return  op == '+' || op == '-' ? 1 :
			op == '*' || op == '/' || op == '%' ? 2 :
			-1;
};

string avoidUnary(string s) {
	if(s[0] == '-' || s[0] == '+') {
			s.insert(s.begin(), '0');
	}
	for(int i = 1; i < s.size(); i++)
	{
		if(s[i-1] == '(' && (s[i] == '-' || s[i] == '+')){
			s.insert(s.begin() + i, '0');
		}
	}
	return s;
};

string getPolNotation(string inputStr){
	vector<char> signs;
	string resStr;
	for(int i = 0; i < inputStr.length(); i++)
	{
		char tempSymb = inputStr[i];
		if(isdigit(tempSymb)) {
			resStr.push_back(tempSymb);
			if(isOp(inputStr[i+1]) || (inputStr[i+1] == '\0')) resStr.push_back(' ');
		}
		else {
			if(tempSymb == '('){
				signs.push_back(tempSymb);
			}
			else {
				if(tempSymb == ')') {
					char curr = signs.back();
					while(curr != '(') {
						resStr.push_back(curr);
						signs.pop_back();
						curr = signs.back();
					};
					signs.pop_back();
				}
				else {
					if(isOp(tempSymb)){
						if(!signs.empty()){
							while(!signs.empty() && (priority(tempSymb) <= priority(signs.back())))
							{
								resStr.push_back(signs.back());
								resStr.push_back(' ');
								signs.pop_back();
							}
							signs.push_back(tempSymb);
						}
						else {
							signs.push_back(tempSymb);
						}
					}

				}
			}
		}
	}
	while(!signs.empty()){
		resStr.push_back(signs.back());
		signs.pop_back();
	}
	return resStr;
};




int main()
{
	string inputStr;
	cin >> inputStr;
	//string resStr = getPolNotation(inputStr);
	string resStr = avoidUnary(inputStr);
	cout << resStr << endl;
	system("pause");
	return 0;
}