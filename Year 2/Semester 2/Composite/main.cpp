#include <iostream>
#include <string>

using namespace std;

class IExpression {
public:
	virtual double calc() = 0;
};

class Constant : public IExpression {
	int value;

public:
	Constant(int data) {
		value = data;
	}

	double calc() {
		return value;
	}
};

class Plus : public IExpression {
	IExpression* left;
	IExpression* right;

public:
	Plus(IExpression* l, IExpression* r) {
		left = l;
		right = r;
	}

	double calc() {
		return left->calc() + right->calc();
	}
};

class Minus : public IExpression {
	IExpression* left;
	IExpression* right;

public:
	Minus(IExpression* l, IExpression* r) {
		left = l;
		right = r;
	}

	double calc() {
		return left->calc() - right->calc();
	}
};

class Multiply : public IExpression {
	IExpression* left;
	IExpression* right;

public:
	Multiply(IExpression* l, IExpression* r) {
		left = l;
		right = r;
	}

	double calc() {
		return left->calc() * right->calc();
	}
};

class Divide : public IExpression {
	IExpression* left;
	IExpression* right;

public:
	Divide(IExpression* l, IExpression* r) {
		left = l;
		right = r;
	}

	double calc() {
		return left->calc() / right->calc();
	}
};

int prior(char c) {
	if (c == '+' || c == '-') return 1;
	if (c == '*' || c == '/') return 2;
	return 0;
}

IExpression* parseExpr(string s) {
	int balance = 0;
	for (int i = s.length() - 1; i >= 0; i--) {
		if (prior(s[i]) == 1 && balance == 0) {
			if (s[i] == '+') return new Plus(parseExpr(s.substr(0, i)), parseExpr(s.substr(i + 1, s.length() - i - 1)));
			if (s[i] == '-') return new Minus(parseExpr(s.substr(0, i)), parseExpr(s.substr(i + 1, s.length() - i - 1)));
		}
		if (s[i] == '(') balance++;
		if (s[i] == ')') balance--;
	}
	balance = 0;
	for (int i = s.length() - 1; i >= 0; i--) {
		if (prior(s[i]) == 2 && balance == 0) {
			if (s[i] == '*') return new Multiply(parseExpr(s.substr(0, i)), parseExpr(s.substr(i + 1, s.length() - i - 1)));
			if (s[i] == '/') return new Divide(parseExpr(s.substr(0, i)), parseExpr(s.substr(i + 1, s.length() - i - 1)));
		}
		if (s[i] == '(') balance++;
		if (s[i] == ')') balance--;
	}
	if (s[0] == '(' && s[s.length() - 1] == ')') return parseExpr(s.substr(1, s.length() - 2));
	return new Constant(stoi(s));
}


int main() {
	string s;
	cin >> s;
	cout << parseExpr(s)->calc() << endl;
	system("pause");
	return 0;
}