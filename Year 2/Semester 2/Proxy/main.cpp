#include <iostream>
#include <string>
#include <map>

using namespace std;

class IData {
public:
	map<string, string> allowed;
	virtual string secretCode(string, string) = 0;
};

class SecureData : public IData {
public:
	SecureData() {
		allowed["admin"] = "adminpassword";
	}
	string secretCode(string login, string password) {
		cout << "[SecureData log] Code was given to: " << login << endl;
		return "SUPERSECRETECODE";
	}
};

class SecureDataProxy : public IData{
	IData * data;
public:
	SecureDataProxy() {
		data = new SecureData(); 
	}

	string secretCode(string login, string password) {
		if (data->allowed[login] == password) {
			return data->secretCode(login, password);
		}
		else return "Access denied";
	}
};

int main() {
	IData * proxy = new SecureDataProxy();
	cout << proxy->secretCode("user", "userpassword") << endl;
	cout << proxy->secretCode("admin", "adminpassword") << endl;
	system("pause");
	return 0;
}