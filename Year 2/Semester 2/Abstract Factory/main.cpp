#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class ISubtitles {
public:
	virtual string getData() = 0;
};

class ISound {
public:
	virtual string getAudio() = 0;
};

class UASubtitles : public ISubtitles {
public:
	string getData() {
		return "UA Subtitles";
	}
};

class RUSubtitles : public ISubtitles {
public:
	string getData() {
		return "RU Subtitles";
	}
};

class UASound : public ISound {
public:
	string getAudio() {
		return "UA Audio";
	}
};

class RUSound : public ISound {
public:
	string getAudio() {
		return "RU Audio";
	}
};


class ILang {
public:
	virtual ISound* getSound() = 0;
	virtual ISubtitles* getSubtitle() = 0;
};

class RULang : public ILang {
public:
	ISound* getSound() {
		return new RUSound();
	}

	ISubtitles* getSubtitle() {
		return new RUSubtitles();
	}
};

class UALang : public ILang {
public:
	ISound* getSound() {
		return new UASound();
	}

	ISubtitles* getSubtitle() {
		return new UASubtitles();
	}
};

class Film {
	ILang* lang;
public:
	Film(string l) {
		if (l == "ru" || l == "RU") lang = new RULang();
		if (l == "ua" || l == "UA") lang = new UALang();
	}

	void changeLang(string l) {
		delete lang;
		if (l == "ru" || l == "RU") lang = new RULang();
		if (l == "ua" || l == "UA") lang = new UALang();
	}

	void startMovie() {
		cout << lang->getSound()->getAudio() << endl;
		cout << lang->getSubtitle()->getData() << endl;
		cout << "Movie Started" << endl;
	}
};

int main() {
	Film f("ru");
	f.startMovie();
	f.changeLang("ua");
	f.startMovie();
	system("pause");
	return 0;
}