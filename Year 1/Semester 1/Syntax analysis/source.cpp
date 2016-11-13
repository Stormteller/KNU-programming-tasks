#include <iostream>
#include <string>

using namespace std;

/*
enum suma { DIG, SGN, SUM, INT };


bool for_sum(char* s, suma type, int l, int r)
{
	if (type == SUM)
	{
		if (for_sum(s, INT, l, r)) return true;
		for (int i = l; i < r; i++)
			if (for_sum(s, INT, l, i - 1) && for_sum(s, SGN, i, i) && for_sum(s, INT, i + 1, r)) return true;
		return false;
	}
	if (type == INT)
	{
	//	if (readExp(s, DIG, l, r)) return true;
		for (int i = l; i < r; i++)
			if (for_sum(s, DIG, i, i)) return false;
		return true;
	}
	if (type == DIG)
	{
		if (l == r && s[l] >= '0' && s[l] <= '9') return true;
		return false;
	}
	if (type == SGN)
	{
		if (l == r && (s[l] == '+' || s[l] == '-')) return true;
		return false;
	}
}*/

/*
enum var_dec {INDEX_VAR,IDENT,LIST,IND_EXP,INDEX,SIGN};

bool var_with_index(char *s, var_dec type, int l, int r)
{
	if (type == INDEX_VAR)
	{
		if (var_with_index(s, IDENT, l, r)) return true;
		else
			for (int i = 0; i < r; i++)
				if (var_with_index(s, IDENT, l, i) && var_with_index(s, LIST, i + 1, r)) return true;
		return false;
	}
	if (type == LIST)
	{
		if (var_with_index(s, IND_EXP, l, r)) return true;
		for (int i = l; i < r; i++)
		{
			if (var_with_index(s, IND_EXP, i + 2, r) && (s[i] == ' ') && (s[i + 1] == ',')) return true;
		}
		return false;
	} */

enum int_ex { INT_EXP, TERM, SIGN, FACT, VAR, INT, DIG};

bool int_expression(char *s, int_ex type, int l, int r)
{
	if (type == INT_EXP)
	{
		if (int_expression(s, TERM, l, r)) return true;
		for (int i = l; i < r; i++)
			if (int_expression(s, TERM, l, i - 1) && (int_expression(s, SIGN, i, i) && int_expression(s, INT_EXP, i + 1, r))) return true;
		return false;
	}
	if (type == TERM)
	{
		if (int_expression(s, FACT, l, r)) return true;
		for (int i = l; i < r; i++)
		{
			if ((s[i] == '*') && (s[i + 1] == '*')) return false;
			if ((int_expression(s, FACT, l, i-1) && (s[i] == '*') && (int_expression(s, TERM, i + 1, r)))) return true;
		}  
		return false;
	}
	if (type == FACT)
	{
		if (int_expression(s, VAR, l, r) || int_expression(s, INT, l, r) || ( int_expression(s, INT_EXP, l+1, r-1) && (s[l] == '(') && (s[r] == ')'))) return true;
		return false;
	}
	if (type == VAR)
	{
		if ((l == r) && (s[l] >= 'a') && (s[l] <= 'z')) return true;
		return false;
	}
	if (type == SIGN)
	{
		if ((l == r) && ((s[l] == '+') || (s[l] == '-'))) return true;
		return false;
	}
	if (type == INT)
	{
		//	if (readExp(s, DIG, l, r)) return true;
		for (int i = l; i < r; i++)
			if (!int_expression(s, DIG, i, i)) return false;
		return true;
	}
	if (type == DIG)
	{
		if ((l == r) && (s[l] >= '0') && (s[l] <= '9')) return true;
		return false;
	}
}




int main()
{
	cout << "Input string for check" << endl;
	char s[10000];
	cin >> s;
	if (int_expression(s, INT_EXP, 0,strlen(s)-1)) cout << "This is integer expression" << endl;
	else cout << "This is NOT integer expression" << endl;
	system("pause");
	return 0;
}