#pragma once

class myString
{
private:
	char * data;
	int len;
public:
	myString(char * str);
	char operator[](int i);
	myString operator+(char * str);
	myString operator+(myString str);
	myString operator+ (const char c);
	myString & operator=(myString str);
	myString & operator=(char * str);
	bool operator==(myString str);
	char * myString::data_();
	bool operator==(char * str);
	bool operator!=(myString str);
	bool operator!=(char * str);
	int length();
	myString(const myString & str);
	myString(void);
	~myString(void);
	friend std::ostream& operator<<(std::ostream&, const myString&);
    friend std::istream& operator>>(std::istream&, myString&);

};

