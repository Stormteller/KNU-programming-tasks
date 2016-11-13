#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

using namespace std;

class CalculateExpr {
	static bool isOper(char c) {
		return c == '+' || c == '-' || c == '*' || c == '/';
	}

	static int prior(char c) {
		if (c == '*' || c == '/') return 2;
		if (c == '+' || c == '-') return 1;
		return 0;
	}

	static bool validExpr(string s) {
		if (s[0] == '*' || s[0] == '/') return false;
		if (isOper(s[s.length() - 1])) return false;
		int balance = 0;
		for (int i = 0; i < s.length(); i++) {
			if (isOper(s[i]) && isOper(s[i - 1])) return false;
			if (s[i] == '(') balance++;
			if (s[i] == ')') balance--;
			if (balance < 0) return false;
		}
		if (balance != 0) return false;
		return true;
	}

	static string avoidUnary(string s) {
		string resStr = s;
		if (prior(s[0]) == 1) resStr = '0' + resStr;
		for (int i = 1; i < s.length(); i++) {
			if (prior(s[i]) == 1 && s[i-1] == '(') {
				resStr = resStr.substr(0, i+1) + '0' + resStr.substr(i+1);
			}
		}
		return resStr;
	}

	static int calculate(string s) {
		int balance = 0;
		for (int i = s.length() - 1; i >= 0; i--) {
			if (s[i] == ')') balance--;
			if (s[i] == '(') balance++;
			if (s[i] == '+' && balance == 0) return calculate(s.substr(0, i)) + calculate(s.substr(i + 1));
			if (s[i] == '-' && balance == 0) return calculate(s.substr(0, i)) - calculate(s.substr(i + 1));
		}
		balance = 0;
		for (int i = s.length() - 1; i >= 0; i--) {
			if (s[i] == ')') balance--;
			if (s[i] == '(') balance++;
			if (s[i] == '*' && balance == 0) return calculate(s.substr(0, i)) * calculate(s.substr(i + 1));
			if (s[i] == '/' && balance == 0) return calculate(s.substr(0, i)) / calculate(s.substr(i + 1));
		}
		bool isNum = true;
		for (int i = 0; i < s.length(); i++) {
			if (!isdigit(s[i])) isNum = false;
		}
		if (isNum) 
			return stoi(s);
		if (s[0] == 'a' && s[1] == 'b' && s[2] == 's')
			return abs(calculate(s.substr(4, s.length() - 5)));
	}

public:
	static int calc(string s) {
		if (validExpr) {
			s = avoidUnary(s);
			return calculate(s);
		}
		else {
			throw exception("Syntax expr error");
		}
	}
};

class Program {
	vector<string> commands;
	map<char, int> variables;
	map<int, int> tracks;
	enum operatorType { SAVE, GO, IF, GET, PUT, FINISH, ERR };
	int currCommand;
public:
	Program() {
		currCommand = 0;
	}

	void addCommand(string s) {
		string trackSrt = "";
		int i = 0;
		bool haveTrack = false;
		for (; i < s.length(); i++) {
			if (s[i] == '#') {
				tracks[stoi(s.substr(0, i))] = commands.size();
				haveTrack = true;
				break;
			}
		}
		if(haveTrack) commands.push_back(s.substr(i + 1));
		else commands.push_back(s);
	}

	operatorType commandType(string s) {
		if (s[1] == ':' && s[2] == '=') return SAVE;
		if (s[0] == 'g' && s[1] == 'o') return GO;
		if (s[0] == 'i' && s[1] == 'f') return IF;
		if (s[0] == 'g' && s[1] == 'e' && s[2] == 't') return GET;
		if (s[0] == 'p' && s[1] == 'u' && s[2] == 't') return PUT;
		if (s == "finish") return FINISH;
		return ERR;
	}

	int execCommand(string s) {
		switch (commandType(s))	{
		case SAVE: return save(s);
		case GO: return go(s);
		case IF: return condition(s);
		case GET: return get(s);
		case PUT: return put(s);
		case FINISH: return finish();
		case ERR: throw exception("Syntax error"); return 2;
		default:
			throw exception("Unknown error");
			return 2;
		}
	}

	bool validExpr(string s) {
		for (int i = 0; i < s.length(); i++) {
			if (s[i] >= '0' && s[i] <= '9') { continue; }
			else {
				if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z')) { continue; }
				else {
					if (s[i] == '*' || s[i] == '/' || s[i] == '+' || s[i] == '-') { continue; }
					else {
						if (s[i] == '(' || s[i] == ')') { continue; }
						else {
							return false;
						}
					}
				}
			}
		}
		return true;
	}

	bool compare(string left, string right, string sign) {
		if (sign == ">") {
			if (CalculateExpr::calc(replaceVarsWithVals(left)) > CalculateExpr::calc(replaceVarsWithVals(right))) return true;
			else return false;
		}
		else {
			if (sign == "<") {
				if (CalculateExpr::calc(replaceVarsWithVals(left)) < CalculateExpr::calc(replaceVarsWithVals(right))) return true;
				else return false;
			}
			else {
				if (sign == ">=") {
					if (CalculateExpr::calc(replaceVarsWithVals(left)) >= CalculateExpr::calc(replaceVarsWithVals(right))) return true;
					else return false;
				}
				else {
					if (sign == "<=") {
						if (CalculateExpr::calc(replaceVarsWithVals(left)) <= CalculateExpr::calc(replaceVarsWithVals(right))) return true;
						else return false;
					}
					else {
						if (sign == "=") {
							if (CalculateExpr::calc(replaceVarsWithVals(left)) == CalculateExpr::calc(replaceVarsWithVals(right))) return true;
							else return false;
						}
						else {
							if (sign == "!=") {
								if (CalculateExpr::calc(replaceVarsWithVals(left)) != CalculateExpr::calc(replaceVarsWithVals(right))) return true;
								else return false;
							}
							else {
								throw exception("Syntax error");
							}
						}
					}
				}
			}
		}
	}

	string replaceVarsWithVals(string s) {
		string resStr = s;
		for (int i = 0; i < resStr.length(); i++) {
			if ((resStr[i] >= 'A' && resStr[i] <= 'Z') || (resStr[i] >= 'a' && resStr[i] <= 'z')) {
				if (resStr[i] == 'a' && resStr[i + 1] == 'b' && resStr[i + 2] == 's') {
					i += 2;
					continue;
				}
				else {
					if (variables.count(resStr[i])) {
						resStr.replace(i, 1, to_string(variables[resStr[i]]));
					}
					else {
						throw exception("No variable exist");
					}
				}
			}
		}
		return resStr;
	}

	int save(string s) {
		string rightExpr = s.substr(3);
		int rightRes = 0;
		if (validExpr(rightExpr)) {
			rightExpr = replaceVarsWithVals(rightExpr);
			rightRes = CalculateExpr::calc(rightExpr);
			variables[s[0]] = rightRes;
		}
		else {
			throw exception("Syntax expr error");
		}
		return 1;
	}

	int go(string s) {
		int trackNum = stoi(s.substr(2));
		if (tracks.count(trackNum)) {
			currCommand = tracks[trackNum] - 1; // -1 ??
		} else { throw exception("Unknown track");}
		return 1;
	}

	int condition(string s) {
		int i = 0;
		for (; i < s.length(); i++) {
			if (s[i] == ')') break;
		}
		string argStr = s.substr(3, i-3);
		string oper = s.substr(i+1);
		string argLeft;
		string argRight;
		string sign;
		i = 0;
		for (; i < argStr.length(); i++) {
			if (argStr[i] == '>' || argStr[i] == '<' || argStr[i] == '=' || argStr[i] == '!') {
				argLeft = argStr.substr(0, i);
				sign = argStr[i];
				break;
			}
		}
		i++;
		if (argStr[i] == '>' || argStr[i] == '<' || argStr[i] == '=' || argStr[i] == '!') sign += argStr[i];
		i++;
		argRight = argStr.substr(i);

		if (compare(argLeft, argRight, sign)) {
			if (oper != "") {
				return execCommand(oper);
			}
		}
		return 1;
	}

	int get(string s) {
		int data;
		string argStr = s.substr(4, s.length() - 5);
		if (argStr.length() == 1 && ((argStr[0] >= 'A' && argStr[0] <= 'Z') || (argStr[0] >= 'a' && argStr[0] <= 'z'))) {
			cin >> data;
			variables[argStr[0]] = data;
		}
		else {
			throw exception("Syntax expr error");
		}

		return 1;
	}

	int put(string s) {
		int data;
		string argStr = s.substr(4, s.length() - 5);
		if (argStr[0] == '$') cout << s.substr(1) << endl;
		else {
			cout << CalculateExpr::calc(replaceVarsWithVals(argStr)) << endl;
		}

		return 1;
	}

	int finish() {
		cout << "Program finished" << endl;
		return 0;
	}

	void execProgram() {
		for (; currCommand < commands.size(); currCommand++) {
			if (!execCommand(commands[currCommand])) break;
		}
	}
};

string trim(string s) {
	string resStr = "";
	for (int i = 0; i < s.length(); i++) {
		if (s[i] != ' ') resStr += s[i];
	}
	return resStr;
}

int main() {
	ifstream fin("input.txt");
	string s;
	Program newProg;
	while (getline(fin, s)) {
		if(s != "") newProg.addCommand(trim(s));
	}
	newProg.execProgram();
	system("pause");
	return 0;
}