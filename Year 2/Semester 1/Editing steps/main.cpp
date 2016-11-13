#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class vocabular {
	vector<string*> words;
	vector<string*> ladder;
	bool similar(string s1, string s2);
	vector<string*> step(string* s, vector<string*>&);
public: vocabular();
		void findLadder();
		void printLadder();
};

bool vocabular::similar(string s1, string s2)
{
	if (s1.size() > s2.size()) swap(s1, s2);
	//if(s1.size()<s2.size())
	unsigned t = 0;
	for (unsigned i = 0; i < s2.size(); i++)
		if (s1[t] == s2[i])t++;
	if (t == s2.size() - 1) return true;
	return false;
}

vector<string*> vocabular::step(string* s, vector<string*>& voc)
{
	vector<string*> max = voc;
	for (unsigned i = 0; i < words.size(); i++)
		if (*s != *words[i] && abs((int)((*s).size() - (*words[i]).size())) < 2 && similar(*s, *words[i])
			&& find(voc.begin(), voc.end(), words[i]) == voc.end()) {
			voc.push_back(words[i]);
			vector<string*> tmp = step(words[i], voc);
			if (max.size() < tmp.size()) max = tmp;
			voc.erase(voc.end() - 1);
		}
	return max;
}

vocabular::vocabular()
{
	string s;
	ifstream fin("input.txt");
	while (fin >> s) {
		string* str = new string(s);
		words.push_back(str);
	}
}

void vocabular::findLadder()
{
	vector<string*> voc;
	for (unsigned i = 0; i < words.size(); i++)
	{
		voc.push_back(words[i]);
		vector<string*> tmp = step(words[i], voc);
		if (ladder.size() < tmp.size()) ladder = tmp;
		voc.erase(voc.end() - 1);
	}
}

void vocabular::printLadder()
{
	cout << "Max ladder is:\n";
	for (unsigned i = 0; i < ladder.size(); i++)
		cout << *ladder[i] << endl;
}

int main() {
	vocabular my;
	my.findLadder();
	my.printLadder();
	system("pause");
	return 0;
}