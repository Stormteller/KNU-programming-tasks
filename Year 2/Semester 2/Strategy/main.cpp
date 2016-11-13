#include <iostream>
#include <string>

using namespace std;

class IStrategy {
public:
	virtual void use() = 0;
};

class Step: public IStrategy {
public:
	void use() {
		cout << "I can step" << endl;
	}
};

class Fly : public IStrategy {
public:
	void use() {
		cout << "I can fly" << endl;
	}
};

class GameUnit {
protected:
	IStrategy* strategy;
public:
	virtual void useStrategy() = 0;
	virtual void setStrategy(IStrategy*) = 0;
};

class Unit : public GameUnit {
public:
	string name;
	Unit(string s) {
		name = s;
	}

	void useStrategy() {
		cout << name << ": ";
		strategy->use();
	}

	void setStrategy(IStrategy* strat) {
		strategy = strat;
	}
};

int main() {
	Unit garpy("Garpy");
	Unit orc("Orc");
	Unit pegas("Pegas");

	orc.setStrategy(new Step());
	orc.useStrategy();

	garpy.setStrategy(new Step());
	garpy.useStrategy();

	garpy.setStrategy(new Fly());
	garpy.useStrategy();

	pegas.setStrategy(new Fly());
	pegas.useStrategy();

	system("pause");
	return 0;
}