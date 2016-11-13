#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdlib.h>

using namespace std;

struct date
{
	int day;
	int month;
	int year;
	date& operator=(date& Date)
	{
		(*this).day = Date.day;
		(*this).month = Date.month;
		(*this).year = Date.year;
		return (*this);
	}
};

bool operator==(date Date1,date Date2)
{
	if (Date1.day == Date2.day && Date1.month == Date2.month && Date1.year == Date2.year) return true;
	else return false;
}

struct personInfo
{
	char name[24];
	char surname[64] ;
	char email[64];
	bool married;
	date birth;
	short children;
	bool deleted;
};

void clearBase()
{
	FILE * data_base = fopen("data.bin", "wb");
	fclose(data_base);
}

date str_to_date(char * str)
{
	char temp[5] ={0};
	short i = 0;
	short j = 0;
	date Date;
	while (str[j]!='.'&&str[j]!=','&&str[j]!='\0')
		temp[i++]=str[j++];
	i = 0; j++;
	Date.day=atoi(temp);
	while (str[j]!='.'&&str[j]!=','&&str[j]!='\0')
		temp[i++]=str[j++];
	i = 0; j++;
	Date.month=atoi(temp);
	while (str[j]!='.'&&str[j]!=','&&str[j]!='\0')
		temp[i++]=str[j++];
	i = 0; j++;
	Date.year=atoi(temp);
	return Date;
}

bool checkSubstr(char * str1, char * str2)
{
	if (strstr(str1, str2) != NULL) return true;
	else return false;
}

void toArray(int &counter, personInfo * ans)
{
	FILE * data_base = fopen("data.bin", "rb+");
	fread(&counter, sizeof(int), 1, data_base);
	for (int i = 0; i < counter; i++)
		fread(&ans[i], sizeof(personInfo), 1, data_base);
	fclose(data_base);
}

void toFile(int &counter, personInfo * ans)
{
	FILE * data_base = fopen("data.bin", "rb+");
	fwrite(&counter, sizeof(int), 1, data_base);
	for (int i = 0; i < counter; i++)
		fwrite(&ans[i], sizeof(personInfo), 1, data_base);
	fclose(data_base);
}

void addPerson()
{
	FILE * data_base = fopen("data.bin", "rb+");
	personInfo person;
	int counter = 0;
	char c;
	fread(&counter, sizeof(int), 1, data_base);
	counter++;
	fseek(data_base, 0, SEEK_SET);
	fwrite(&counter, sizeof(int), 1, data_base);
	printf("First name: ");
	cin >> person.name;
	printf("Second name: ");
	cin >> person.surname;
	printf("E-mail: ");
	cin >> person.email;
	printf("Birthday: ");
	char temp[20]; cin >> temp;
	person.birth = str_to_date(temp);
	printf("Married(+/-): ");
	cin >> c;
	if(c == '+') person.married = true; else if(c == '-') person.married = false; else {cout << "error input\n"; return;}
	printf("Number of children: ");
	cin >> person.children;
	person.deleted = false;
	fseek(data_base, (counter-1)*sizeof(personInfo), SEEK_CUR);
	fwrite(&person, sizeof(personInfo), 1, data_base);
	fclose(data_base);
}

void outPerson (personInfo person)
{
	cout << "First name: " << person.name << endl; 
	cout << "Second name: " << person.surname << endl;
	cout << "E-mail: " << person.email << endl; 
	cout << "Birthday: "; 
	if (person.birth.day < 10) cout << '0' << person.birth.day << '.';
	else cout << person.birth.day << '.';
	if (person.birth.month < 10) cout << '0' << person.birth.month << '.';
	else cout << person.birth.day << '.';
	cout << person.birth.year << endl;
	person.married? cout << "Married: " << "Married" << endl : cout << "Married: " << "Not married" << endl;
	cout << "Children: " << person.children << endl; 
	cout << endl;
}

personInfo getPersonByID(int i)
{
	FILE * data_base = fopen("data.bin", "rb+");
	int counter;
	personInfo person;
	fread(&counter, sizeof(int), 1, data_base);
	fseek(data_base, (i-1)*sizeof(personInfo), SEEK_CUR);
	fread(&person, sizeof(personInfo), 1, data_base);
	fclose(data_base);
	return person;
}

int findByKey(char * key)
{
	FILE * data_base = fopen("data.bin", "rb+");
	int counter;
	personInfo person;
	fread(&counter, sizeof(int), 1, data_base);
	for (int i = 0; i < counter; i++)
	{
		fread(&person, sizeof(personInfo), 1, data_base);
		if ((checkSubstr(person.name, key) || checkSubstr(person.surname, key) || checkSubstr(person.email, key)) && !person.deleted)
		{
			cout << "First name: " << person.name << endl;  cout << " Second name: " << person.surname << endl; cout << "E-mail: " << person.email << endl;  fclose(data_base); return i + 1;
		}
	}

}

void deleteItem(int j)
{
	FILE * data_base = fopen("data.bin", "rb+");
	int counter;
	personInfo person[2000];
	toArray(counter, person);
	for (int i = j-1; i < counter; i++)
		person[i] = person[i + 1];
	counter--;
	clearBase();
	toFile(counter, person);
	fclose(data_base);
}

void findByData(int type_data, char * key)
{
	FILE * data_base = fopen("data.bin", "rb+");
	int counter;
	personInfo person;
	fread(&counter, sizeof(int), 1, data_base);
	if (type_data == 1)
	{
	for (int i = 0; i < counter; i++)
	{
		fread(&person, sizeof(personInfo), 1, data_base);
		if (!strcmp(person.name,key) && !person.deleted) outPerson(person);
	}
	}
	if (type_data == 2)
	{
	for (int i = 0; i < counter; i++)
	{
		fread(&person, sizeof(personInfo), 1, data_base);
		if (!strcmp(person.surname,key) && !person.deleted) outPerson(person);
	}
	}
	if (type_data == 3)
	{
	for (int i = 0; i < counter; i++)
	{
		fread(&person, sizeof(personInfo), 1, data_base);
		if (!strcmp(person.email,key) && !person.deleted) outPerson(person);
	}
	}
	if (type_data == 4)
	{
	for (int i = 0; i < counter; i++)
	{
		fread(&person, sizeof(personInfo), 1, data_base);
		if (person.birth == str_to_date(key) && !person.deleted) outPerson(person);
	}
	}
	if (type_data == 5)
	{
	for (int i = 0; i < counter; i++)
	{
		fread(&person, sizeof(personInfo), 1, data_base);
		if (person.children == atoi(key) && !person.deleted) outPerson(person);
	}
	}
	if (type_data == 6)
	{
	for (int i = 0; i < counter; i++)
	{
		fread(&person, sizeof(personInfo), 1, data_base);
		if (!strcmp(key,"+"))
			if (person.married && !person.deleted) outPerson(person);
		if (!strcmp(key,"-"))
			if (!person.married && !person.deleted) outPerson(person);
	}
	}
	fclose(data_base);
}

void deleteItem(char * key)
{
	 deleteItem(findByKey(key));
}

int compare(const void * x1, const void * x2)   
{
	return ((*(personInfo*)x1).surname[0] - (*(personInfo*)x2).surname[0]);             
}

void editPersonByID(int i)
{
	FILE * data_base = fopen("data.bin", "rb+");
	int counter;
	personInfo person;
	fread(&counter, sizeof(int), 1, data_base);
	fseek(data_base, (i-1)*sizeof(personInfo), SEEK_CUR);
	fread(&person, sizeof(personInfo), 1, data_base);
	if(!person.deleted)
	{
	outPerson(person);
	cout << "Do you want to change person info? (+/-)\n";
	char c;
	cin >> c;
	if(c == '+') 
	{
		fseek(data_base, (i-1)*sizeof(personInfo)+sizeof(int), SEEK_SET);
		printf("First name: ");
		cin >> person.name;
		printf("Second name: ");
		cin >> person.surname;
		printf("E-mail: ");
		cin >> person.email;
		printf("Birthday: ");
		char temp[20]; cin >> temp;
		person.birth = str_to_date(temp);
		printf("Married(+/-): ");
		char z;
		cin >> z;
		if(z == '+') person.married = true; else if(z == '-') person.married = false; else {cout << "error input\n"; return;}
		printf("Number of children: ");
		cin >> person.children;
		person.deleted = false;
		fwrite(&person, sizeof(personInfo), 1, data_base);
	}
	}
	else cout << "Sorry,item in a trash bin";
	fclose(data_base);
}

void sort_data()
{
	FILE * data_base = fopen("data.bin", "rb+");
	int counter;
	personInfo person[200];
	toArray(counter, person);
	qsort(person, counter, sizeof(personInfo),compare);
	toFile(counter, person);
	fclose(data_base);
}

void out()
{
	FILE * data_base = fopen("data.bin", "rb+");
	int counter;
	personInfo person;
	fread(&counter, sizeof(int), 1, data_base);
	for (int i = 0; i < counter; i++)
	{
		fread(&person, sizeof(personInfo), 1, data_base);
		if(!person.deleted)outPerson(person);
		cout << endl;
	}
	fclose(data_base);
}

int statisticMoreChildrenThan(int i)
{
	FILE * data_base = fopen("data.bin", "rb+");
	int counter;
	personInfo person;
	int res = 0;
	fread(&counter, sizeof(int), 1, data_base);
	for (int i = 0; i < counter; i++)
	{
		fread(&person, sizeof(personInfo), 1, data_base);
		if (person.children >= i && !person.deleted) res++;
	}
	return res;
}

int statisticOlderThan(int i)
{
	FILE * data_base = fopen("data.bin", "rb+");
	int counter;
	personInfo person;
	int res = 0;
	fread(&counter, sizeof(int), 1, data_base);
	for (int i = 0; i < counter; i++)
	{
		fread(&person, sizeof(personInfo), 1, data_base);
		if (2014-person.birth.year >= i && !person.deleted) res++;
	}
	return res;
}

int staticticBirthdayInMonth (int i)
{
FILE * data_base = fopen("data.bin", "rb+");
	int counter;
	personInfo person;
	int res = 0;
	fread(&counter, sizeof(int), 1, data_base);
	for (int i = 0; i < counter; i++)
	{
		fread(&person, sizeof(personInfo), 1, data_base);
		if (person.birth.month == i && !person.deleted) res++;
	}
	return res;
}

int staticticMarried()
{
FILE * data_base = fopen("data.bin", "rb+");
	int counter;
	personInfo person;
	int res = 0;
	fread(&counter, sizeof(int), 1, data_base);
	for (int i = 0; i < counter; i++)
	{
		fread(&person, sizeof(personInfo), 1, data_base);
		if (person.married && !person.deleted) res++;
	}
	return res;
}

void statisticInfoMenu()
{
cout << "___________________________________________________________________________\n" <<
		"|Get info about people who older than a given age press 'o'               |\n" <<
		"|Get info about people who have more children than a given value press 'c'|\n" <<
		"|Get info about people who have birthday in a given month press 'b'       |\n" <<
		"|Get info about people who married press 'm'                              |\n" <<
		"|Quit press 'q'                                                           |\n" <<
		"|_________________________________________________________________________|\n";
}

void startMenu()
{
	cout << "______________________________________________________\n" <<
			"|Actions with data base 'a'                          |\n" <<
			"|Get statistic info 's'                              |\n" <<
			"|Quit '#'                                            |\n" <<
			"|____________________________________________________|\n";
}

void actionInfoOutput()
{
	cout << 
		"____________________________________________\n" <<
		"|Add person '+'                            |\n" <<
		"|Edit person info 'e'                      |\n" <<
		"|Delete item by number 'd'                 |\n" <<
		"|Delete item by key 'k'                    |\n" <<
		"|Find person by number 'n'                 |\n" <<
		"|Find person by key 'f'                    |\n" <<
		"|Find all people by a given value 'v'      |\n" <<
		"|Add item to the trash bin 't'             |\n" <<
		"|Remove item from the trash bin 'r'        |\n" <<
		"|Sort data 's'                             |\n" <<
		"|Clear data base 'c'                       |\n" <<
		"|Output data 'o'                           |\n" <<
		"|Quit 'q'                                  |\n" <<
		"|__________________________________________|\n";
}

void valueTypes()
{
	cout << "Input value type: " << endl;
	cout << 
		"___________________________\n" <<
		"|1 - Name                 |\n" <<
		"|2 - Surname              |\n" <<
		"|3 - E-mail               |\n" <<
		"|4 - Birthday             |\n" <<
		"|5 - Number of children   |\n" <<
		"|6 - Married or not       |\n" <<
		"|_________________________|\n";
}

void addToTrashBin(int i)
{
	FILE * data_base = fopen("data.bin", "rb+");
	int counter;
	personInfo person;
	fread(&counter, sizeof(int), 1, data_base);
	fseek(data_base, (i-1)*sizeof(personInfo), SEEK_CUR);
	fread(&person, sizeof(personInfo), 1, data_base);
	fseek(data_base, (i-1)*sizeof(personInfo)+sizeof(int), SEEK_SET);
	person.deleted = true;
	fwrite(&person, sizeof(personInfo), 1, data_base);
	fclose(data_base);
}

void removeFromTrashBin(int i)
{
	FILE * data_base = fopen("data.bin", "rb+");
	int counter;
	personInfo person;
	fread(&counter, sizeof(int), 1, data_base);
	fseek(data_base, (i-1)*sizeof(personInfo), SEEK_CUR);
	fread(&person, sizeof(personInfo), 1, data_base);
	fseek(data_base, (i-1)*sizeof(personInfo)+sizeof(int), SEEK_SET);
	person.deleted = false;
	fwrite(&person, sizeof(personInfo), 1, data_base);
	fclose(data_base);
}

int main()
{
	char c;
	do {
		system("cls");
		startMenu();
		cin >> c;
		if (c == 'a')
		{
			do {
			system("cls");
			actionInfoOutput();
			cin >> c;
			if(c == '+') {system("cls"); addPerson();}
			if(c == 'e') {system("cls"); int i; cout << "Input number: "; cin >> i; editPersonByID(i);system("pause");}
			if(c == 'd') {system("cls"); int i; cout << "Input number: "; cin >> i; deleteItem(i);}
			if(c == 'k') {system("cls"); char s[64]; cout << "Input key: ";  cin >> s; deleteItem(s);}
			if(c == 'n') {system("cls"); int i; cout << "Input number: "; cin >> i; outPerson(getPersonByID(i));system("pause");}
			if(c == 'f') {system("cls"); int i; cout << "Input key: "; cin >> i; outPerson(getPersonByID(i));system("pause");}
			if(c == 'v') {system("cls"); int i; valueTypes(); cin >> i; cout << "Input value: "; char s[32]; cin >> s; findByData(i,s);system("pause");}
			if(c == 't') {system("cls"); int i; cout << "Input number: "; cin >> i; addToTrashBin(i);}
			if(c == 'r') {system("cls"); int i; cout << "Input number: "; cin >> i; removeFromTrashBin(i);}
			if(c == 's') {system("cls"); sort_data();}
			if(c == 'c') {system("cls"); clearBase();}
			if(c == 'o') {system("cls"); out();system("pause");}
			} while ( c != 'q');
		}
		if (c == 's')
		{
			do {
			
			system("cls");
			statisticInfoMenu();
			cin >> c;
			if(c == 'o') {system("cls"); int i; cout <<"Input age: "; cin>>i; cout << "Number of people who older than " << i << " : " << statisticOlderThan(i) << endl; system("pause");}
			if(c == 'c') {system("cls"); int i; cout <<"Input number of childen: "; cin>>i; cout << "Number of people who have more children than " << i << " : " << statisticMoreChildrenThan(i) << endl; system("pause");}
			if(c == 'b') {system("cls"); int i; cout <<"Input month"; cin>>i; cout << "Number of people who have birthday in " << i << " : " << staticticBirthdayInMonth(i) << endl; system("pause");}
			if(c == 'm') {system("cls"); cout << "Number of people who married: "  << staticticMarried() << endl; system("pause");}
			} while ( c != 'q');
		}
	} while (c != '#');
	system("pause");
	return 0;
}