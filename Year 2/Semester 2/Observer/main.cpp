#include <iostream>
#include <string>
#include <vector>

using namespace std;

class IObserver;
class IObservable {
public:
	virtual void addObserver(IObserver*) = 0;
	virtual void removeObserver(IObserver*) = 0;
	virtual void notifyObservers() = 0;
};

class Newspapper;
class IObserver {
public:
	virtual void handleEvent(const Newspapper&) = 0;
};


class Newspapper: public IObservable {
	vector<IObserver*> observers;
public:
	string title;
	string content;
	int amount;

	Newspapper(string t, string c) {
		title = t;
		content = c;
		amount = 0;
	}
	void addObserver(IObserver* o) override {
		observers.push_back(o);
	}

	void removeObserver(IObserver* o) override {
		auto it = std::find(observers.begin(), observers.end(), o);
		if (it != observers.end())
			observers.erase(it);
	}

	void notifyObservers() override {
		for (int i = 0; i < observers.size(); i++) {
			observers[i]->handleEvent(*this);
		}
	}

	void comesFromPublishingHouse() {
		amount++;
		notifyObservers();
	}

	void sold() {
		amount--;
		notifyObservers();
	}

	/*void updateTitle(string newT) {
		title = newT;
		notifyObservers();
	}

	void updateContent(string newC) {
		content = newC;
		notifyObservers();
	}*/
};

class Subscriber : public IObserver {
	string name;
public:
	Subscriber(string name) {
		this->name = name;
	}
	void handleEvent(const Newspapper& o) override {
		cout << this->name << ": " << o.title << ": " << o.amount << endl;
	}
};

class news1 : public Newspapper {
public:
	news1(string s1, string s2):Newspapper(s1, s2) {	}
};

class news2 : public Newspapper {
public:
	news2(string s1, string s2) :Newspapper(s1, s2) {	}
};

int main() {
	news1* n1 = new news1("T1", "C1");
	news2* n2 = new news2("T2", "C2");
	Subscriber* subs1 = new Subscriber("subs1");
	Subscriber* subs2 = new Subscriber("subs2");
	n1->addObserver(subs1);
	n1->addObserver(subs2);
	n2->addObserver(subs1);
	n1->comesFromPublishingHouse();
	n1->sold();
	n2->comesFromPublishingHouse();

	system("pause");
	return 0;
}