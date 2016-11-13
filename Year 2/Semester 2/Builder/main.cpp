#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class TextConverter {
public:
	virtual void convertAuthor(string) = 0;
	virtual void convertTitle(string) = 0;
	virtual void convertContent(string) = 0;
};

class XMLText {
	string xmlString;
public:
	XMLText() {
		xmlString = "<?xml version=\"1.0\" encoding=\"utf - 8\"?>\n<article>\n<\/article>\n";
	}
	void appendTag(string tag) {
		xmlString.insert(xmlString.length() - 11, tag);
	}

	void saveToFile(string filename) {
		ofstream fout(filename);
		fout << xmlString;
		fout.close();
	}
};

class XMLConverter: public TextConverter {
	XMLText xmltext;
public:
	void convertAuthor(string text) override {
		string res = "<author>" + text + "</author>\n";
		xmltext.appendTag(res);
	}

	void convertTitle(string text) override {
		string res = "<title>" + text + "</title>\n";
		xmltext.appendTag(res);
	}

	void convertContent(string text) override {
		string res = "<content>\n";
		for (int i = 0; i < text.size();) {
			string par = "<paragraph>";
			while ((i < text.size()) && (text[i] != '\n' && text[i] != '\0')) {
				if(text[i] == '>') par += "&gt;";
				else if (text[i] == '<') par += "&lt;";
				else if (text[i] == '&') par += "&amp;";
				else if (text[i] == '\'') par += "&apos;";
				else if (text[i] == '\"') par += "&quot;";
				else par += text[i];
				i++;
			}
			par += "</paragraph>\n";
			res += par;
			i++;
		}
		res += "</content>\n";
		xmltext.appendTag(res);
	}

	XMLText getResult() {
		return xmltext;
	}
};

class TxtReader {
	
	TextConverter* builder;
public:
	TxtReader(TextConverter* builder) {
		this->builder = builder;
	}

	void parseTxt(string filename) {
		ifstream fin(filename);
		while (!fin.eof()) {
			string title;
			string author;
			string content = "";
			getline(fin, title);
			getline(fin, author);
			string tempLine;
			while (getline(fin, tempLine)) {
				content += (tempLine + '\n');
			}
			builder->convertTitle(title);
			builder->convertAuthor(author);
			builder->convertContent(content);
		}
	}



};

int main() {
	XMLConverter* xmlconv = new XMLConverter();
	TxtReader reader(xmlconv);
	reader.parseTxt("input.txt");
	XMLText res = xmlconv->getResult();
	res.saveToFile("output.xml");

	system("pause");
	return 0;
}