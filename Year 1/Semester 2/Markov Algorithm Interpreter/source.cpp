#include <iostream>
#include <fstream>

using namespace std;

struct algo
{
	char from[100];
	char to[100];
	bool ended;
	static int number;
	algo ()
	{
		memset(from,0,sizeof(from));
		memset(to,0,sizeof(to));
		ended = false; number++;
	}
};

int algo::number = 0;

void getAlgo(algo * algoMas)
{
	ifstream fin("input.txt");
	int i = 0;
	char temp[100];
	while(!fin.eof())
	{
		int c = 0, t = 0;
		fin.getline(temp,sizeof(temp));
		while (temp[c] != ' ' && c < strlen(temp)) 
			algoMas[i].from[t++] = temp[c++];
		while (temp[c] == ' ' && c < strlen(temp)) c++;
		if(temp[c+2] == '*') algoMas[i].ended = true;
		else algoMas[i].ended = false;
		while (temp[c] != ' ' && c < strlen(temp)) c++;
		while (temp[c] == ' ' && c < strlen(temp)) c++;
		t = 0;
		while (temp[c] != ' ' && temp[c] != '\n' && temp[c] != '\0' && c < strlen(temp)) 
			algoMas[i].to[t++] = temp[c++];
		i++;
	}
	fin.close();
}

void deleteSubStr(char *& str1, char * str2)
{
	int index = strstr(str1,str2) - str1;
	char res[100] = {0};
	int i = 0,c = 0;
	while (i < index) res[c++] = str1[i++]; 
	while (i < index + strlen(str2)) i++;
	while (i < strlen(str1)) res[c++] = str1[i++];
	str1 = res;
}

void push_front(char *& str1, char * str2)
{
	char res[100] = {0};
	int i = 0,c = 0;
	while (i < strlen(str2)) res[c++] = str2[i++];
	i = 0;
	while (i < strlen(str1)) res[c++] = str1[i++];
	str1 = res;
//	for(int  j = 0; j < strlen(res); j++) cout << res[j] << " ";
}

void replace_str(char *& str1, char * str2, char * str3)
{
	int index = strstr(str1,str2) - str1;
	char res[100] = {0};
	int i = 0,c = 0,k = 0;
	while (i < index) res[c++] = str1[i++]; 
	while (k < strlen(str3)) res[c++] = str3[k++];
	while (i < index + strlen(str2)) i++;
	while (i < strlen(str1)) res[c++] = str1[i++];
	str1 = res;
	//for(int  j = 0; j < strlen(res); j++) cout << res[j] << " ";
}

void workAlgo(char * s,algo * algoMas)
{
	int i = 0;
	bool can = true;
	while (!algoMas[i].ended && can)
	{
		if(algoMas[i].from == "-") {
			push_front(s,algoMas[i].to);i = 0;
			continue;}
		if (strstr(s,algoMas[i].from) != NULL)
		{
			if(algoMas[i].to == "-"){ deleteSubStr(s,algoMas[i].from);i = 0;}
			else  {replace_str(s,algoMas[i].from,algoMas[i].to);i = 0;}
			continue;
		}
		if(i == algoMas[i].number && strstr(s,algoMas[i].from) == NULL) can = false;
		i++;
	}
	for(int  j = 0; j < strlen(s); j++) cout << s[j] << " "; 
}

int main()
{
	algo algoMas[100];
	getAlgo(algoMas);
	//if (strstr("xyxyx",algoMas[0].from) != NULL) cout << "lalala"; else cout << "asd";
	char s[100] = {0};
	cin >> s;
	workAlgo(s,algoMas);
	system("pause");
	return 0;
}
