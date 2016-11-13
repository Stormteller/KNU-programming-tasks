#include "polNotation.h"
#include <vector>
#include <string>
/*
using namespace std;
*/
bool isOp(char op){
	return op == '+' || op == '-'|| op == '*' || op == '/';
}

bool isOp(std::string op){
	return (op[0] == '+' || op[0] == '-'|| op[0] == '*' || op[0] == '/') && (op.length() == 1);
}

bool isNumber(std::string str){
	int i = 0;
	if((str[0] == '-') && (str.length() > 1)) i = 1;
	for(; i < str.length(); i++)
	{
		if( ('0' > str[i]) || (str[i] > '9')) return false;
	}
	return true;
}

bool isVariable(char str){
	if( ('a' > tolower(str)) || (tolower(str) > 'z') ) return false;
	return true;
}

bool isVariable(std::string str){
	if( ('a' > tolower(str[0])) || (tolower(str[0]) > 'z') ) return false;
	return true;
}

int priority(char op){
	return  op == '+' || op == '-' ? 1 :
			op == '*' || op == '/' || op == '%' ? 2 :
			-1;
}

int priority(std::string op){
	return  op[0] == '+' || op[0] == '-' && op.length() == 1 ? 1 :
			op[0] == '*' || op[0] == '/' || op[0] == '%' && op.length() == 1 ? 2 :
			-1;
}

std::string avoidUnary(std::string s) {
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
}

std::vector<std::string> strToArray(std::string str,char c){
	std::string temp = "";
	int count = 0;
	std::vector<std::string> res;
	for(int i = 0; i < str.length(); i++)
	{

		if((str[i] != c)) temp.push_back(str[i]);
		else {
			res.push_back(temp);
			temp = "";
		}
		if(str[i+1] == '\0') res.push_back(temp);
	}
	return res;
}

std::string getPolNotation(std::string inputStr){
	std::vector<char> signs;
	std::string resStr;
	for(int i = 0; i < inputStr.length(); i++)
	{
		char tempSymb = inputStr[i];
		if(isdigit(tempSymb) || isVariable(tempSymb)) {
			resStr.push_back(tempSymb);
			if(isOp(inputStr[i+1]) || (inputStr[i+1] == '\0') || (inputStr[i+1] == ')')) resStr.push_back(' ');
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
						resStr.push_back(' ');
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
		if(signs.size() != 1)
		resStr.push_back(' ');
		signs.pop_back();
	}
	return resStr;
}


/*

int main()
{
	string inputStr;
	cin >> inputStr;
	//string resStr = getPolNotation(inputStr);
	string resStr = avoidUnary(inputStr);
	cout << resStr << endl;
	system("pause");
	return 0;
}*/