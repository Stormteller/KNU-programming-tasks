#include <iostream>
#include "HashMap.h"
#include <string>

using namespace std;

int main() {
	

	HashMap<string, int> hmap;
	hmap.put("Datata", 3);
	hmap.put("ddd", 964);
	hmap.put("qqq", 22);

	int value;
	hmap.get("Datata", value);
	cout << value << endl;
	bool res = hmap.get("qqq", value);
	if (res)
		cout << value << endl;
	hmap.remove("ddd");
	res = hmap.get("ddd", value);
	if (res)
		cout << value << endl;
	system("pause");
	return 0;
}