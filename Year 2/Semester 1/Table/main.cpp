#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;

class Table {
	vector<vector<string>> data;
	string type;
	int rows;

public:
	Table(int rows, string type) {
		this->rows = rows;
		string newData;
		for (int i = 0; i < rows; i++) {
			vector<string> newRow;
			do {
				cin >> newData;
				if (newData != ".") {
					newRow.push_back(newData);
				}
			} while (newData != ".");
			data.push_back(newRow);
		}
		this->type = type;
	}

	Table(string filename) {
		ifstream fin(filename);
		fin >> type;
		fin >> rows;
		string newData;
		for (int i = 0; i < rows; i++) {
			vector<string> newRow;
			do {
				fin >> newData;
				if (newData != ".") {
					newRow.push_back(newData);
				}
			} while (newData != ".");
			data.push_back(newRow);
		}
		fin.close();
	}

	void saveToFile(string filename) {
		ofstream fout(filename);
		fout << type << endl;
		fout << rows << endl;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < data[i].size(); j++) {
				fout << data[i][j] << ' ';
			}
			fout << "." << endl;
		}
		fout.close();
	}

	void loadFromFile(string filename) {
		ifstream fin(filename);
		fin >> type;
		fin >> rows;
		string newData;
		data.clear();
		for (int i = 0; i < rows; i++) {
			vector<string> newRow;
			do {
				fin >> newData;
				if (newData != ".") {
					newRow.push_back(newData);
				}
			} while (newData != ".");
			data.push_back(newRow);
		}
		fin.close();
	}

	void print() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < data[i].size(); j++) {

				if (type == "int")	cout << stoi(data[i][j]) << ' ';
				if (type == "short")	cout << (short)stoi(data[i][j]) << ' ';
				if (type == "char")	cout << (char)stoi(data[i][j]) << ' ';
				if (type == "string")	cout << data[i][j] << ' ';
				if (type == "double")	cout << stod(data[i][j]) << ' ';
				if (type == "bool")	  cout << ((data[i][j] != "0")? "true" : "false" ) << ' ';

			}
			cout << endl;
		}
	}

	void deleteRow(int n) {
		if (data.size() >= n) {
			data.erase(data.begin() + n - 1);
			rows--;
		}
	}

	void deleteCol(int n) {
		for (int i = 0; i < rows; i++) {
			if (data[i].size() >= n) {
				data[i].erase(data[i].begin() + n - 1);
			}
		}
	}

	void deleteCell(int i, int j) {
		if (data.size() >= i && data[i].size() >= j) {
			data[i - 1].erase(data[i - 1].begin() + j - 1);
		}
	}

	void insertRow(int n, vector<string> newRow) {
		rows++;
		if (n >= data.size()) { 
			data.push_back(newRow);
		}
		else { 
			data.insert(data.begin() + n, newRow);
		}
	}

	void insertCol(int n, vector<string> newCol) {
		for (int i = 0; i < rows; i++) {
			if (n >= data[i].size()) {
				data[i].push_back(newCol[i]);
			}
			else {
				data[i].insert(data[i].begin() + n, newCol[i]);
			}
		}	
	}

	void insertCell(int i, int j, string newData) {
		if(data.size() >= i) {
			if (j >= data[i - 1].size()) {
				data[i - 1].push_back(newData);
			}
			else {
				data[i - 1].insert(data[i - 1].begin() + j, newData);
			}
		}
	}

	void updateRow(int n, vector<string> newRow) {
		if (n <= data.size()) {
			data[n - 1] = newRow;
		}
	}

	void updateCol(int n, vector<string> newCol) {
		for (int i = 0; i < rows; i++) {
			if (n <= data[i].size()) {
				data[i][n - 1] = newCol[i];
			}
		}
	}

	void updateCell(int i, int j, string newData) {
		if (data.size() >= i) {
			if (j <= data[i - 1].size()) {
				data[i - 1][j - 1] = newData;
			}
		}
	}

	void cast(string newType) {
		type = newType;
	}
};

class dialogMode {
	Table* table;
	static enum Commands { ADD_ROW, ADD_COL, ADD_CELL, DEL_ROW, DEL_COL, DEL_CELL, UPD_ROW, UPD_COL, UPD_CELL, LOAD, SAVE, CAST };
public:
	dialogMode (Table* table) {
		this->table = table;
	}

	 Commands commandType(string s) {
		if (s.substr(0, 4) == "load") return LOAD;
		if (s.substr(0, 4) == "save") return SAVE;
		if (s.substr(0, 4) == "cast") return CAST;
		if (s.substr(0, 7) == "add row") return ADD_ROW;
		if (s.substr(0, 7) == "add col") return ADD_COL;
		if (s.substr(0, 8) == "add cell") return ADD_CELL;
		if (s.substr(0, 10) == "delete row") return DEL_ROW;
		if (s.substr(0, 10) == "delete col") return DEL_COL;
		if (s.substr(0, 11) == "delete cell") return DEL_CELL;
		if (s.substr(0, 10) == "update row") return UPD_ROW;
		if (s.substr(0, 10) == "update col") return UPD_COL;
		if (s.substr(0, 11) == "update cell") return UPD_CELL;
	}
	
	 void execCommand(string s) {
		 Commands comType = commandType(s);
		 switch (comType) {
			 case LOAD: table->loadFromFile("input.txt"); break;
			 case SAVE: table->saveToFile("input.txt"); break;
			 case CAST: {
				 table->cast(s.substr(5));
				 break;
			 }
			 case ADD_ROW: {
				 s = s.substr(8);
				 int i = 0;
				 string currStr = "";
				 while (s[i] != ' ') {
					 currStr += s[i];
					 i++;
				 }
				 int rowN = stoi(currStr);
				 vector<string> newRow;
				 currStr = "";
				 i++;
				 for (; i < s.length(); i++) {
					 if (s[i] == ' ') {
						 newRow.push_back(currStr);
						 currStr = "";
					 }
					 else {
						 currStr += s[i];
					 }
				 }
				 newRow.push_back(currStr);
				 table->insertRow(rowN , newRow);
				 break;
			 }
			 case ADD_COL: {
				 s = s.substr(8);
				 int i = 0;
				 string currStr = "";
				 while (s[i] != ' ') {
					 currStr += s[i];
					 i++;
				 }
				 int rowN = stoi(currStr);
				 vector<string> newCol;
				 currStr = "";
				 i++;
				 for (; i < s.length(); i++) {
					 if (s[i] == ' ') {
						 newCol.push_back(currStr);
						 currStr = "";
					 }
					 else {
						 currStr += s[i];
					 }
				 }
				 newCol.push_back(currStr);
				 table->insertCol(rowN, newCol);
				 break;
			 }
			 case ADD_CELL: {
				 s = s.substr(9);
				 int i = 0;
				 string currStr = "";
				 string newData;
				 while (s[i] != ' ') {
					 currStr += s[i];
					 i++;
				 }
				 int rowN = stoi(currStr);
				 currStr = "";
				 i++;
				 while (s[i] != ' ') {
					 currStr += s[i];
					 i++;
				 }
				 int colN = stoi(currStr);
				 currStr = "";
				 i++; 
				 while (s[i] != ' ' && s[i] != '\0') {
					 currStr += s[i];
					 i++;
				 }
				 newData = currStr;
					
				 table->insertCell(rowN, colN, newData);
				 break;
			 }
			 case DEL_ROW: {
				 int rowN = stoi(s.substr(11));
				 table->deleteRow(rowN);
				 break;
			 }
			 case DEL_COL: {
				 int rowN = stoi(s.substr(11));
				 table->deleteCol(rowN);
				 break;
			 }
			 case DEL_CELL: {
				 s = s.substr(12);
				 int i = 0;
				 string currStr = "";
				 while (s[i] != ' ') {
					 currStr += s[i];
					 i++;
				 }
				 int rowN = stoi(currStr);
				 currStr = "";
				 i++;
				 while (s[i] != ' ' && s[i] != '\0') {
					 currStr += s[i];
					 i++;
				 }
				 int colN = stoi(currStr);
				 table->deleteCell(rowN, colN);
				 break;
			 }
			 case UPD_ROW: {
				 s = s.substr(11);
				 int i = 0;
				 string currStr = "";
				 while (s[i] != ' ') {
					 currStr += s[i];
					 i++;
				 }
				 int rowN = stoi(currStr);
				 vector<string> newRow;
				 currStr = "";
				 i++;
				 for (; i < s.length(); i++) {
					 if (s[i] == ' ') {
						 newRow.push_back(currStr);
						 currStr = "";
					 }
					 else {
						 currStr += s[i];
					 }
				 }
				 newRow.push_back(currStr);
				 table->updateRow(rowN, newRow);
				 break;
			 }
			 case UPD_COL: {
				 s = s.substr(11);
				 int i = 0;
				 string currStr = "";
				 while (s[i] != ' ') {
					 currStr += s[i];
					 i++;
				 }
				 int rowN = stoi(currStr);
				 vector<string> newCol;
				 currStr = "";
				 i++;
				 for (; i < s.length(); i++) {
					 if (s[i] == ' ') {
						 newCol.push_back(currStr);
						 currStr = "";
					 }
					 else {
						 currStr += s[i];
					 }
				 }
				 newCol.push_back(currStr);
				 table->updateCol(rowN, newCol);
				 break;
			 }
			 case UPD_CELL: {
				 s = s.substr(12);
				 int i = 0;
				 string currStr = "";
				 string newData;
				 while (s[i] != ' ') {
					 currStr += s[i];
					 i++;
				 }
				 int rowN = stoi(currStr);
				 currStr = "";
				 i++;
				 while (s[i] != ' ') {
					 currStr += s[i];
					 i++;
				 }
				 int colN = stoi(currStr);
				 currStr = "";
				 i++;
				 while (s[i] != ' ' && s[i] != '\0') {
					 currStr += s[i];
					 i++;
				 }
				 newData = currStr;
				 table->updateCell(rowN, colN, newData);
				 break;
			 }
			 default: {break;}

		 }
	 }

	 void print() {
		 table->print();
	 }
};

int main() {
	ifstream fin("input.txt");
	bool emptyFile = true;
	string type;
	if (fin >> type) emptyFile = false;
	Table* table;
	int rowN;
	if (!emptyFile) {
		table = new Table("input.txt");
	}
	else {
		cout << "Input rows amount:\n";
		cin >> rowN;
		cout << "Input table type:\n";
		cin >> type;
		cout << "Input table (finish lines with '.')\n";
		table = new Table(rowN, type);
	}
	fin.close();
	string command;
	dialogMode dial(table);
	dial.print();
	do {
		getline(cin, command);
		dial.execCommand(command);
		system("cls");
		dial.print();
	} while (command != "finish");

	system("pause");
	return 0;
}