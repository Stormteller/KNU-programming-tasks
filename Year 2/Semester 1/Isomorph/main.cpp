#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Tree {
	class Node {
	public:	char val;
			int depth;
			int parentLine;
			Node* parent;
			vector<string> subtree;
			vector<Node*> sons;
	public: Node(int a, Node* parent) {
		val = a;
		this->parent = parent;
	}
	};
	class cortegCompare {
	public: int depth, parentLine;
			bool checked = false;
			vector<int> sonsParentLine;
	};
	Node* root = NULL;
	Node* subRoot = NULL;
	Node* findRoot = nullptr;
	string findExp;
	vector<cortegCompare*> findCorteg;
	vector<cortegCompare*> subCorteg;

public: void create(string exp) {
	add(exp, root, nullptr);
}

		string print() {
			string exp;
			show(exp, root);
			return exp;
		}

		void printSubtrees() {
			cout << "Subtrees: \n";
			showSub(root);
		}

		void createSubtree() {
			generateSubtree(root);
		}

		void isomorph(string expSearch) {
			findExp = expSearch;
			add(expSearch, findRoot, nullptr);
			Node* lift = findRoot;
			while (lift->sons.size()) lift = lift->sons[0];
			rotateSubtree(lift, nullptr);
			findRoot = lift;
			depthAndParentLine(findRoot, 0);
			buildCorteg(findRoot, findCorteg);
			findIsomorph(root);
		}

private:	void add(string exp, Node* &cur, Node* parent) {
	cur = new Node(exp[0], parent);
	exp.erase(exp.begin());

	int depth = 0;
	for (int i = 0; i < exp.size(); i++) {
		switch (exp[i])
		{
		case '(': depth++;
			break;
		case ')': depth--;
			if (depth == 0) {
				Node* tmp;
				add(string(exp.substr(1, i - 1)), tmp, cur);
				cur->sons.push_back(tmp);
				exp.erase(0, i + 1);
				i = -1;
			}
			break;
		default:
			break;
		}
	}
}

			void deleteTree(Node* cur) {
				for (int i = 0; i < cur->sons.size(); i++) {
					deleteTree(cur->sons[i]);
					delete cur->sons[i];
				}
			}

			void show(string &exp, Node* cur) {
				exp += cur->val;
				for (int i = 0; i < cur->sons.size(); i++) {
					exp += '(';
					show(exp, cur->sons[i]);
					exp += ')';
				}
			}


			void generateSub(Node* cur, vector<Node*> &sons, int i, string exp) {
				if (i < sons.size()) {
					string tmp = exp;
					for (int t = 0; t < sons[i]->subtree.size(); t++) {
						exp = tmp + '(' + sons[i]->subtree[t] + ')';
						generateSub(cur, sons, i + 1, exp);
					}
				}
				else cur->subtree.push_back(exp);
			}


			void generateSons(Node* cur, int i, vector<Node*> sons) {
				string exp;
				exp += cur->val;
				if (i < cur->sons.size()) {
					generateSons(cur, i + 1, sons);
					sons.push_back(cur->sons[i]);
					generateSons(cur, i + 1, sons);
				}
				else generateSub(cur, sons, 0, exp);
			}


			void showSub(Node* cur) {
				for (int i = 0; i < cur->sons.size(); i++) showSub(cur->sons[i]);
				for (int i = 0; i < cur->subtree.size(); i++) cout << cur->subtree[i] << endl;
			}

			void generateSubtree(Node* cur) {
				for (int i = 0; i < cur->sons.size(); i++) generateSubtree(cur->sons[i]);
				vector<Node*> tmp;
				generateSons(cur, 0, tmp);
			}

			void findIsomorph(Node* cur) {
				for (int i = 0; i < cur->sons.size(); i++) findIsomorph(cur->sons[i]);
				for (int i = 0; i < cur->subtree.size(); i++) {
					if (findExp.size() == cur->subtree[i].size()) {
						add(cur->subtree[i], subRoot, nullptr);
						modifiedSubtree(cur->subtree[i]);
						deleteCorteg(subCorteg);
						subCorteg.clear();
						deleteTree(subRoot);
						delete subRoot;
					}
				}
			}

			void depthAndParentLine(Node* cur, int depth) {
				cur->depth = depth;
				cur->parentLine = longestLine(cur, 0);
				for (int i = 0; i < cur->sons.size(); i++) depthAndParentLine(cur->sons[i], depth + 1);
			}

			int longestLine(Node* cur, int depth) {
				int maxLine = depth;
				for (int i = 0; i < cur->sons.size(); i++) {
					int line = longestLine(cur->sons[i], 1 + depth);
					if (maxLine < line) maxLine = line;
				}
				return maxLine;
			}

			void buildCorteg(Node* cur, vector<cortegCompare*> &subtreeToCorteg) {
				cortegCompare* tmp = new cortegCompare();
				tmp->depth = cur->depth;
				tmp->parentLine = cur->parentLine;
				for (int i = 0; i < cur->sons.size(); i++) {
					tmp->sonsParentLine.push_back(cur->sons[i]->parentLine);
					buildCorteg(cur->sons[i], subtreeToCorteg);
				}
				subtreeToCorteg.push_back(tmp);
			}

			void deleteCorteg(vector<cortegCompare*> &subtreeToCorteg) {
				for (int i = 0; i < subtreeToCorteg.size(); i++) delete subtreeToCorteg[i];
			}

			bool compareSubtree() {
				bool isEquel = false;
				for (int i = 0; i < findCorteg.size(); i++) {
					for (int t = 0; t < subCorteg.size(); t++)
						if (!subCorteg[t]->checked && compareCorteg(subCorteg[t], findCorteg[i])) {
							subCorteg[t]->checked = true;
							isEquel = true;
							break;
						}
					if (!isEquel) return false;
					isEquel = false;
				}
				return true;
			}

			bool compareCorteg(cortegCompare* a, cortegCompare* b) {
				if (a->depth == b->depth && a->parentLine == b->parentLine) return compareSonsParentLine(a->sonsParentLine, b->sonsParentLine);
				return false;
			}

			bool compareSonsParentLine(vector<int> a, vector<int> b) {
				bool isEquel = false;
				for (int i = 0; i < a.size(); i++) {
					for (int t = 0; t < b.size(); t++)
						if (a[i] == b[t]) {
							b.erase(b.begin() + t);
							isEquel = true;
							break;
						}
					if (!isEquel) return false;
					isEquel = false;
				}
				return true;
			}

			void modifiedSubtree(string exp) {
				vector<Node*> lifts;
				createVectorOfLifts(subRoot, lifts);
				for (int i = 0; i < lifts.size(); i++) {
					rotateSubtree(lifts[i], nullptr);

					subRoot = lifts[i];
					depthAndParentLine(subRoot, 0);
					buildCorteg(subRoot, subCorteg);
					if (compareSubtree()) { cout << "Isomorph subtree: " << exp << endl; return; }
					deleteCorteg(subCorteg);
					subCorteg.clear();
				}
			}

			void createVectorOfLifts(Node* cur, vector<Node*> &lifts) {
				for (int i = 0; i < cur->sons.size(); i++) createVectorOfLifts(cur->sons[i], lifts);
				if (!cur->sons.size()) lifts.push_back(cur);
			}

			void rotateSubtree(Node* cur, Node* parent) {
				if (cur->parent) {
					Node* next = cur->parent;
					cur->sons.push_back(cur->parent);
					cur->parent->sons.erase(find(cur->parent->sons.begin(), cur->parent->sons.end(), cur));

					rotateSubtree(next, cur);
				}
				cur->parent = parent;
			}
};

void main() {
	cout << "Enter exp: ";
	string exp;
	cin >> exp;
	Tree mytree;
	mytree.create(exp);
	//cout<<mytree.print()<<endl;
	mytree.createSubtree();
	//mytree.printSubtrees();
	cout << "Enter exp2: ";
	cin >> exp;
	mytree.isomorph(exp);
	system("pause");
}