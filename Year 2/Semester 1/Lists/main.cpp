#include <fstream>
#include <iostream>
#include "List.h"

using namespace std;

int main() {
	List list, greaterList, lessList;
	ifstream fin("input.txt");
	int n,data,index;
	char c;
	cout << "Initialize list:\n";
	while(fin >> data) {
		list.addTail(data);
	}
	list.print();

	cout << "1 - add\n2 - del\n3 - print\n4 - exit\n";

	
	do {
		cin >> c;
		switch (c) {
		case '1': { 
			cin >> index;
			cin >> data; 
			list.addIndex(index, data); 
			break;
		}
		case '2': {
			cin >> index; 
			list.delIndex(index); 
			break;
		}
		case '3': list.print(); break;

		case '4': break;

		default: cout << "Bad operation\n"; break;

		}
	} while (c != '4');

	cout << "Write N:\n";

	cin >> n;
	
	list.sliceList(n, greaterList, lessList);

	list.print();
	
	greaterList.print();

	lessList.print();


	system("pause");
	return 0;
}