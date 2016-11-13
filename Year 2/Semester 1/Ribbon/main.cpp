#include <iostream>
#include <string>

using namespace std;

struct tree
{
	char ribType;
	tree* left;
	tree* right;
	tree()
	{
		left = nullptr;
		right = nullptr;
	}
	tree(char rib)
	{
		ribType = rib;
		left = nullptr;
		right = nullptr;
	}
};

void addLeaf (tree* root, char bendType)
{
	if (root->left) addLeaf(root->left, bendType);
	if (root->right) addLeaf(root->right, bendType);
	else
	{
		if (bendType == 'F')
		{
			tree* leftSon = new tree('K');
			tree* rightSon = new tree('O');
			root->left = leftSon;
			root->right = rightSon;
		}
		if (bendType == 'B')
		{
			tree* leftSon = new tree('O');
			tree* rightSon = new tree('K');
			root->left = leftSon;
			root->right = rightSon;
		}
	}
}

void fill_line(tree* root, string &outputLine)
{
	if (root==NULL) return;
	if (root->left) fill_line(root->left, outputLine);
	outputLine += root->ribType;
	if (root->right) fill_line(root->right, outputLine);
}

string RibTypesSeq (string bendTypes)
{
	string myOutputLine;
	tree* myRoot = new tree;
	if (bendTypes[0] == 'F') myRoot->ribType = 'O';
	if (bendTypes[0] == 'B') myRoot->ribType = 'K';
	for (int i = 1; i < bendTypes.length(); i++)
	{
		if (bendTypes[i] == 'F') addLeaf(myRoot, 'F');
		if (bendTypes[i] == 'B') addLeaf(myRoot, 'B');
	}
	fill_line(myRoot, myOutputLine);
	return myOutputLine;
}

void BendTypesSeq (tree* root, string ribTypes)
{
	int rootRibIndex = ribTypes.length()/2;
	root->ribType = ribTypes[rootRibIndex];
	if (ribTypes.length() == 3)
	{
		root->ribType = ribTypes[1];
		tree* myLeft = new tree(ribTypes[0]);
		tree* myRight = new tree(ribTypes[2]);
		root->left = myLeft;
		root->right = myRight;
	}
	else
	{
		tree* myLeft = new tree;
		tree* myRight = new tree;
		root->left = myLeft;
		root->right = myRight;
		BendTypesSeq(root->left, ribTypes.substr(0, rootRibIndex));
		BendTypesSeq(root->right, ribTypes.substr(rootRibIndex+1, ribTypes.length()-1));
	}
}

void checkTree (tree* root)
{
	if (root->left && root->right)
	{
		if (root->left->ribType != root->right->ribType)
		{
			checkTree(root->left);
			checkTree(root->right);
		}
		else cout << "Such string is not exist!";
	}
	else return;
}

void restoreTree (tree* root, string &bendTypes)
{
	if (root->ribType == 'K') bendTypes += 'B';
	if (root->ribType == 'O') bendTypes += 'F';
	if (root->left && root->right)
	{
		if (root->left->ribType != root->right->ribType)
		{
			restoreTree(root->right, bendTypes);
		}
		else cout << "Such string is not exist!";
	}
	else return;
}

string bendTypes(string ribTypes)
{
	if (ribTypes.length()%2 != 1) 
	{
		cout << "error" << endl;
		system ("pause");
		exit(0);
	}
	string linel;
	tree* root = new tree;
	BendTypesSeq (root, ribTypes);
	checkTree(root);
	restoreTree(root, linel);
	return linel;
}


int main ()
{
	string myBendTypes;
	string myRibTypes;

	cout << "Enter the sequence of bend types :" << endl;
	cin >> myBendTypes;
	cout << RibTypesSeq(myBendTypes) << endl;

	cout << "Enter the sequence of rib types :" << endl;
	cin >> myRibTypes;
	cout << bendTypes(myRibTypes) << endl;
	
	system ("pause");
}