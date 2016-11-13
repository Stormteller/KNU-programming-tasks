#include <iostream>
#include <string>

using namespace std;

class Singleton
{
	string name;
protected:
	static Singleton* _self;
	Singleton(string n):name(n) {
		cout << n << " created!" << endl;
	}

public:
	static Singleton* Instance(string n)
	{
		if (!_self)
		{
			_self = new Singleton(n);
		}
		return _self;
	}

	static bool DeleteInstance()
	{
		if (_self)
		{
			delete _self;
			_self = 0;
			return true;
		}
		return false;
	}
};

Singleton* Singleton::_self = 0;

int main() {
	Singleton* World = Singleton::Instance("Amazing world");
	Singleton* World2 = Singleton::Instance("Amazing world2");

	system("pause");
	return 0;
}