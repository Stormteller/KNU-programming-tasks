#include <iostream>

using namespace std;

class IMediator;
class Display {
protected:
public:
	bool enable;
	int brightness;
	IMediator* mediator;
	Display(IMediator* med) {
		mediator = med;
		enable = false;
		brightness = 50;
	}
	virtual void toggleEnable() = 0;
	virtual void increaseBrightness() = 0;
	virtual void decreaseBrightness() = 0;
};

class MainScreen: public Display {
public:
	MainScreen(IMediator* med) :Display(med) {}

	void toggleEnable() {
		enable = !enable;
		cout << "MainScreen toggled" << endl;
	}

	void increaseBrightness() {
		brightness++;
	}

	void decreaseBrightness() {
		brightness--;
	}
};

class SmallDisplay : public Display {
public:
	SmallDisplay(IMediator* med) :Display(med) {}

	void toggleEnable() {
		enable = !enable;
		cout << "SmallDisplay toggled" << endl;
	}

	void increaseBrightness() {
		brightness++;
	}

	void decreaseBrightness() {
		brightness--;
	}
};

class Projector : public Display {
public:
	Projector(IMediator* med) :Display(med) {}

	void toggleEnable() {
		enable = !enable;
		cout << "Projector toggled" << endl;
	}

	void increaseBrightness() {
		brightness++;
	}

	void decreaseBrightness() {
		brightness--;
	}
};



class IMediator {
public:
	virtual void registerMainScreen(MainScreen*) = 0;
	virtual void registerProjector(Projector*) = 0;
	virtual void registerSmallDisplay(SmallDisplay*) = 0;
	virtual void toggleScreen(string) = 0;
	virtual void decBrgth(string) = 0;
	virtual void incBrgth(string) = 0;
};

class Mediator : public IMediator {
	SmallDisplay* smd;
	MainScreen* ms;
	Projector* pr;
public:
	void registerMainScreen(MainScreen* m) {
		ms = m;
	}

	void registerProjector(Projector* p) {
		pr = p;
	};

	void registerSmallDisplay(SmallDisplay* s) {
		smd = s;
	};

	void toggleScreen(string s) {
		if (s == "SmallDisplay") {
			smd->toggleEnable();
		}
		else if(s == "MainScreen"){
			ms->toggleEnable();
		}
		else if (s == "Projector") {
			pr->toggleEnable();
		}
	}

	void decBrgth(string s) {
		if (s == "SmallDisplay") {
			smd->decreaseBrightness();
		}
		else if (s == "MainScreen") {
			ms->decreaseBrightness();
		}
		else if (s == "Projector") {
			pr->decreaseBrightness();
		}
	}

	void incBrgth(string s) {
		if (s == "SmallDisplay") {
			smd->increaseBrightness();
		}
		else if (s == "MainScreen") {
			ms->increaseBrightness();
		}
		else if (s == "Projector") {
			pr->increaseBrightness();
		}
	}
};

int main() {
	IMediator* m = new Mediator();

	MainScreen* ms = new MainScreen(m);
	SmallDisplay* sd = new SmallDisplay(m);
	Projector* pr = new Projector(m);

	m->registerMainScreen(ms);
	m->registerProjector(pr);
	m->registerSmallDisplay(sd);

	ms->mediator->toggleScreen("Projector");
	sd->mediator->toggleScreen("SmallDisplay");
	pr->mediator->toggleScreen("MainScreen");

	ms->mediator->toggleScreen("SmallDisplay");
	system("pause");
	return 0;
}