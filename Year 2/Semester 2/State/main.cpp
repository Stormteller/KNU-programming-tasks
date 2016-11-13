#include <iostream>
#include <string>

using namespace std;



class Grant;
class IState {
protected:
	Grant* grant;
public:
	virtual void showStatus() = 0;
	virtual void getNext() = 0;
};

class CreatedState : public IState {
public:
	CreatedState(Grant* g);

	void showStatus();

	void getNext();
};

class Grant {
public:
	IState* state;
	string name;

	Grant(string n) {
		name = n;
		state = new CreatedState(this);
	}

	void nextState() {
		state->getNext();
	};
	void setState(IState* s) {
		state = s;
	}
};

class CanceledState : public IState {

public:
	CanceledState(Grant* g) {
		grant = g;
	}

	void showStatus() {
		cout << "Grant is canceled" << endl;
	}

	void getNext() {
		cout << "No next state" << endl;
	}
};


class AcceptedState : public IState {

public:
	AcceptedState(Grant* g) {
		grant = g;
	}

	void showStatus() {
		cout << "Grant is accepted" << endl;
	}

	void getNext() {
		grant->setState(new AcceptedState(grant));
	}
};

class ConsideredState : public IState {

public:
	ConsideredState(Grant* g) {
		grant = g;
	}

	void showStatus() {
		cout << "Grant is considered" << endl;
	}

	void getNext() {
		grant->setState(new AcceptedState(grant));
	}
};

CreatedState::CreatedState(Grant* g) {
	grant = g;
}

void CreatedState::showStatus() {
	cout << "Grant created" << endl;
}

void CreatedState::getNext() {
	grant->setState(new ConsideredState(grant));
}


int main() {
	Grant* grant = new Grant("Fulbright");
	grant->state->showStatus();
	grant->nextState();
	grant->state->showStatus();
	grant->nextState();
	grant->state->showStatus();
	grant->setState(new CanceledState(grant));
	grant->state->showStatus();
	system("pause");
	return 0;
}