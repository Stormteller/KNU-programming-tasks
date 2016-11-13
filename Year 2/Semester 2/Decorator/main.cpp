#include <iostream>

using namespace std;

class ICharacter {
public:
	virtual void move() = 0;
};

class Hero : public ICharacter {

public:
	Hero() {}

	void move() {
		cout << "Move X" << endl;
	}
};

class Decorator : public ICharacter {
public:
	ICharacter* character;
	Decorator(ICharacter* c) {
		character = c;
	}

	void move() {
		character->move();
	}
};

class moveYDecorator : public Decorator {
public:
	moveYDecorator(ICharacter* c):Decorator(c) {	}

	void move() {
		Decorator::move();
		cout << "Move Y" << endl;
	}
};

class jumpDecorator : public Decorator {
public:
	jumpDecorator(ICharacter* c) :Decorator(c) {	}

	void move() {
		Decorator::move();
		cout << "Move Z" << endl;
	}
};

int main() {
	ICharacter * hero = new Hero();
	hero->move();

	ICharacter * heroY = new moveYDecorator( new Hero() );
	heroY->move();

	ICharacter * heroYZ = new jumpDecorator( new moveYDecorator(new Hero()) );
	heroYZ->move();
	system("pause");
	return 0;
}