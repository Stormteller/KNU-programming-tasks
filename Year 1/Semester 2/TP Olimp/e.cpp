#include <iostream>
#include <string>
#include <cmath>

using namespace std;

string s;

struct node
{
	char type;
	double key;
	node* left;
	node* right;
};

bool isConst(int l, int r)
{
	int po = 0;
	for (int i = l; i <= r; i++)
	{
		if (s[i] == '.')
			po++; else
			if (s[i] < '0' || s[i] > '9')
				return false;
	}
	if (po <= 1)
		return 1; else
		return 0;
}

double strToNum(int l, int r)
{
	double res = 0;
	int i;
	for (i = l; i <= r && s[i] != '.'; i++)
		res = res * 10 + (s[i] - '0');
	double d = 1.0;
	for (i++; i <= r; i++)
		d /= 10.0, res = res + d * (s[i] - '0');
	return res;
}

int find(int l, int r, char sgn)
{
	int bal = 0;
	if (sgn == '^')
		for (int i = l; i <= r; i++)
		{
			if (s[i] == '(')
				bal++;
			if (s[i] == ')')
				bal--;
			if (sgn == s[i] && bal == 0)
				return i;
		}
	else
		for (int i = r; i >= l; i--)
		{
			if (s[i] == '(')
				bal++;
			if (s[i] == ')')
				bal--;
			if (sgn == s[i] && bal == 0)
				return i;
		}
	return -1;
}

void build(node*& tree, int l, int r)
{
	if (isConst(l, r))
	{
		tree = new node;
		tree->key = strToNum(l, r);
		tree->type = 'C';
		tree->left = tree->right = 0;
		return;
	}
	if (l == r && s[l] == 'x')
	{
		tree = new node;
		tree->type = 'x';
		tree->left = tree->right = 0;
		return;
	}

	while (s[l] == '(' && s[r] == ')')
	{
		int bal(1);
		bool canDel(true);
		for (int i = l + 1; i < r; ++i)
		{
			if (s[i] == '(') bal++;
			if (s[i] == ')') bal--;
			if (bal == 0)
			{
				canDel = false;
				break;
			}
		}
		if (canDel)
			l++, r--;
		else
			break;
	}

	int pos = find(l, r, '+');
	if (pos >= 0)
	{
		tree = new node;
		tree->type = '+';
		build(tree->left, l, pos - 1);
		build(tree->right, pos + 1, r);
	}
	else
	{
		pos = find(l, r, '-');
		if (pos >= 0)
		{
			tree = new node;
			tree->type = '-';
			build(tree->left, l, pos - 1);
			build(tree->right, pos + 1, r);
		}
		else
		{
			pos = find(l, r, '*');
			if (pos >= 0)
			{
				tree = new node;
				tree->type = '*';
				build(tree->left, l, pos - 1);
				build(tree->right, pos + 1, r);
			}
			else
			{
				pos = find(l, r, '/');
				if (pos >= 0)
				{
					tree = new node;
					tree->type = '/';
					build(tree->left, l, pos - 1);
					build(tree->right, pos + 1, r);
				}
				else
				{
					pos = find(l, r, '^');
					if (pos >= 0)
					{
						tree = new node;
						tree->type = '^';
						build(tree->left, l, pos - 1);
						build(tree->right, pos + 1, r);
					}
					else
					{
						if (s[l] == 'c')
						{
							tree = new node;
							tree->type = 'c';
							build(tree->left, l + 4, r - 1);
							tree->right = 0;
						}
						else
							if (s[l + 1] == 'i')
							{
								tree = new node;
								tree->type = 's';
								build(tree->left, l + 4, r - 1);
								tree->right = 0;
							}
							else
							{
								tree = new node;
								tree->type = 'q';
								build(tree->left, l + 5, r - 1);
								tree->right = 0;
							}
					}
				}
			}
		}
	}
}

double calc(node* tree, double x)
{
	if (tree->type == 'C')
		return tree->key;
	if (tree->type == 'x')
		return x;
	double L = calc(tree->left, x);
	if (tree->type == 's')
		return sin(L);
	if (tree->type == 'c')
		return cos(L);
	if (tree->type == 'q')
		return sqrt(L);
	double R = calc(tree->right, x);
	if (tree->type == '+')
		return L + R;
	if (tree->type == '-')
		return L - R;
	if (tree->type == '*')
		return L * R;
	if (tree->type == '/')
		return L / R;
	if (tree->type == '^')
		return pow(L, R);
}

double trapezoid(node *tree, double a, double b, int n)
{
	double h, i, value = 0;
	h = (b - a) / n;

	for (i = a; i<b - h / 2; i += h)
		value += fabs(h*(fabs(calc(tree,i)) + fabs(calc(tree,i + h))) / 2);

	return value;
}

double simpson(node* tree, double a, double b, int n)
{

	double h, i, value = 0;

	h = (b - a) / n;

	for (i = a; i<b - h / 2; i += h)
		value += h*(fabs(calc(tree, i)) + 4 * fabs(calc(tree, i + h / 2)) + fabs(calc(tree, i + h))) / 6;

	return value;
}

node* tree;
double a, b;

int main()
{
	cin >> a >> b;
	if (a > b)
		swap(a, b);
	cin >> s;
	build(tree, 0, s.length() - 1);
	//double res = simpson(tree, a, b, 500000);
	cout << trapezoid(tree, a, b, 800000) << endl;
	return 0;
}
