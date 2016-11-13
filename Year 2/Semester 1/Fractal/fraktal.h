#pragma once
#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;
class Fractal {
public:	string axiom;
	map<string, string> rules;
	map<string, string> interpretation;
	string fraktal;
	double size=1;
	void(*pf)();

	Fractal() {
	ifstream in("input.txt");
	getline(in, axiom);
	string s;
	getline(in, s);
	while (s != "drawingrules") {
		pair<string, string> t;
		t.first = s[0];
		s.erase(0, 2);
		t.second = s;
		rules.insert(t);
		getline(in, s);
	}
	while (!in.eof()) {
		getline(in, s);
		pair<string, string> t;
		t.first = s[0];
		s.erase(0, 2);
		t.second = s;
		interpretation.insert(t);
	}
	cout << axiom << endl;
	//pf();
	fraktal = axiom;
}

		void makeFractal() {			
			string newFraktal;
			//while (true) {
				//system("pause");
				for (unsigned i = 0; i < fraktal.size(); i++) {
					string s = "0";
					s[0]=fraktal[i];
					map<string, string>::iterator it = rules.find(s);
					if(it!=rules.end())	newFraktal += it->second;
					else newFraktal += fraktal[i];
				}
				fraktal = newFraktal;
				newFraktal = "";
				cout << fraktal<<endl;
				//pf();
			//}
		}
};