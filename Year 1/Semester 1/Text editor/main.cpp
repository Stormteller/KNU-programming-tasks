#include <iostream>
#include <string>
#include <fstream>
using namespace std;

enum action {SIZE,MODE,PARAG,FIELD,INTERVAL};
enum mode_type {FULL,UNFULL,RIGHT};
struct command
{
	//action type;
	//size
	int width = 10;
	int height = 10;
	//mode
	mode_type mode = FULL;
	//parag
	int indent = 0;
	int enters = 0;
	//field
	int right = 0;
	int left = 0;
	//interval
	int space = 1;
	command()
	{
		int width = 10;
		int height = 10;
		//mode
		mode_type mode = FULL;
		//parag
		int indent = 0;
		int enters = 0;
		//field
		int right = 0;
		int left = 0;
		//interval
		int space = 0;
	}
};

action checkType(string s)
{
	if (!s.compare("?размер")) return SIZE;
	if (!s.compare("?режим")) return MODE;
	if (!s.compare("?абзац")) return PARAG;
	if (!s.compare("?поле")) return FIELD;
	if (!s.compare("?интервал")) return INTERVAL;
}

mode_type checkMode(string s)
{
	if (!s.compare("плотный")) return FULL;
	if (!s.compare("неплотный")) return UNFULL;
	if (!s.compare("выравнивание")) return RIGHT;
}

action commandType(string s)
{
		int i = 0;
		string word = "";
		while (s[i] == ' ') i++;
		while (s[i] != ' ')
			word.push_back(s[i++]);
		return checkType(word);
}

void parseCommand(string s,command &com)
{
	int i = 0;
	string word="";
	while (s[i] == ' ') i++;
	while (s[i] != ' ')
		word.push_back(s[i++]);
	while (s[i] == ' ') i++;
	//com.type = checkType(word);
	switch (checkType(word))
	{
	case SIZE:
	{
		word = "";
		while ((s[i] != ' ') && (s[i] != '\n') && (s[i] != '\0')) word.push_back(s[i++]);
		com.height = stoi(word.c_str());
		word = "";
		while (s[i] == ' ') i++;
		while ((s[i] != ' ') && (s[i] != '\n') && (s[i] != '\0')) word.push_back(s[i++]);
		com.width = stoi(word.c_str());
	}
		break;
	case MODE:
	{
		 word = "";
		 while ((s[i] != ' ') && (s[i] != '\n') && (s[i] != '\0'))
		 word.push_back(s[i++]);
		 com.mode = checkMode(word);
	}
		break;
	case PARAG:
	{
			word = "";
			while ((s[i] != ' ') && (s[i] != '\n') && (s[i] != '\0')) word.push_back(s[i++]);
			com.indent = stoi(word.c_str());
			word = "";
			while (s[i] == ' ') i++;
			while ((s[i] != ' ') && (s[i] != '\n') && (s[i] != '\0')) word.push_back(s[i++]);
			com.enters = stoi(word.c_str());
	}
		break;
	case FIELD:
	{
			word = "";
			while ((s[i] != ' ') && (s[i] != '\n') && (s[i] != '\0')) word.push_back(s[i++]);
			com.left = stoi(word.c_str());
			word = "";
			while (s[i] == ' ') i++;
			while ((s[i] != ' ') && (s[i] != '\n') && (s[i] != '\0')) word.push_back(s[i++]);
			com.right = stoi(word.c_str());
	}
		break;
	case INTERVAL:
	{
			word = "";
			while ((s[i] != ' ') && (s[i] != '\n') && (s[i] != '\0')) word.push_back(s[i++]);
			com.space = stoi(word.c_str());
	}
		break;
	default: cout << "Some is going on";
		break;
	}
}

int getWords(string s, string words[100])
{
	int i = 0;
	int count = 0;
	for (i; i < s.length();)
	{
		while (s[i] == ' ') i++;
		while ((s[i] != ' ') && (s[i] != '\0')) words[count].push_back(s[i++]);
		count++;
	}
	return count - 1;
}

void writeStr(string s, command settings, bool first, ofstream &fout)
{
	string words[100];
	int count = getWords(s, words);
	if (first)
	{
		if (settings.mode == FULL)
		{
			for (int i = 0; i < count; i++)
			{
				if ((words[i][words[i].length() - 1] == '.') || (words[i][words[i].length() - 1] == '!') || (words[i][words[i].length() - 1] == '?')) fout << words[i] << "  ";
				else fout << words[i] << ' ';
			}
		}
		if (settings.mode == UNFULL)
		{
			fout << s;
		}
		if (settings.mode == RIGHT)
		{
			int sum_length = 0;
			for (int i = 0; i < count; i++)
			for (int j = 0; j < words[i].length(); j++) sum_length++;
			int spaces = (settings.height - settings.right - settings.indent - sum_length + 1) / count;
			if (spaces == 0) spaces++;
			for (int i = 0; i < count; i++)
			{
				fout << words[i];
				for (int j = 0; j <= spaces - (settings.indent)/count + 1; j++) fout << ' ';
			}
			fout << words[count];
		}
	}
	else
	{
		if (settings.mode == FULL)
		{
			for (int i = 0; i < count; i++)
			{
				if ((words[i][words[i].length() - 1] == '.') || (words[i][words[i].length() - 1] == '!') || (words[i][words[i].length() - 1] == '?')) fout << words[i] << "  ";
				else fout << words[i] << ' ';
			}
		}
		if (settings.mode == UNFULL)
		{
			fout << s;
		}
		if (settings.mode == RIGHT)
		{
			int sum_length = 0;
			for (int i = 0; i < count; i++)
			for (int j = 0; j < words[i].length(); j++) sum_length++;
			int spaces = (settings.height - settings.left - settings.right - sum_length + 1) / count;
			if (spaces == 0) spaces++;
			for (int i = 0; i < count; i++)
			{
				fout << words[i];
				for (int j = 0; j < spaces; j++) fout << ' ';
			}
			fout << words[count];
		}
	}
}
int main()
{
	setlocale(LC_ALL,"rus");
	ifstream fin("sinput.txt");
	ofstream fout("soutput.txt");
	string temp;
	bool first = true;
	int count = 0;
	getline(fin,temp);
	command settings;
	parseCommand(temp,settings);
	while (!fin.eof())
	{
		getline(fin, temp);
		if (temp[0] == '?')
		{
			first = true;
			switch (commandType(temp))
			{
				case SIZE: parseCommand(temp, settings);
					break;
				case MODE: parseCommand(temp, settings);
				break;
				case PARAG: parseCommand(temp, settings);
					break;
				case FIELD: parseCommand(temp, settings);
					break;
				case INTERVAL: parseCommand(temp, settings);
					break;
				default: cout << "Some is going on";
					break;
			}
		}
		else
		{
			if (first)
			{
				for (int i = 0; i < settings.enters; i++) fout << endl;
				for (int i = 0; i < settings.indent; i++) fout << ' ';
				for (int i = 0; i < settings.left; i++) fout << ' ';
				writeStr(temp, settings, first, fout);
				for (int i = 0; i < settings.space; i++) fout << endl;
				first = false;
			}
			else
			{
				for (int i = 0; i < settings.left; i++) fout << ' ';
				writeStr(temp, settings, first, fout);
				for (int i = 0; i < settings.space; i++) fout << endl;
			}
		}
	}
	/*string **text = new string[N];
	for (int i = 0; i < N; i++)
		text[i] = new char[M];*/
	fout.close();
	fin.close();
	system("pause");
	return 0;
}