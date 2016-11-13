#define _CRT_SECURE_NO_WARNINGS
#include "myString.h"
#include <iostream>

myString::myString(void)
{
	data = NULL;
	len = 0;
}

myString::myString(char * str)
{
	len = strlen(str);
	data = new char[len+1];
	strcpy(data,str);
}

myString::myString(const myString & str)
{
	len = str.len;
	data = new char[len+1];
	strcpy(data,str.data);
}

myString::~myString(void)
{
	delete [] data;
}

int myString::length()
{
	return len;
}

char * myString::data_()
{
	return data;
}

char myString::operator[](int i)
{
	if(i < len) return data[i];
	return NULL;
}

myString myString::operator+(char * str)
{
	char * temp = new char[len + strlen(str) + 1];
	strcpy(temp, this->data);
	strcat(temp, str);
    myString result(temp);
    delete []temp;
    return result;
}

myString myString::operator+(const myString str)
{
	char *temp = new char[len + str.len + 1];
	strcpy(temp, this->data);
	strcat(temp, str.data);
    myString result(temp);
    delete []temp;
    return result;
}

myString myString::operator+ (const char c)  {
        int t_size;
        if(len != 0)
            t_size = this->len + 2;
        else
            t_size = 2;
        char *temp = new char[t_size];
        if(data)
			strcpy(temp, this->data);
        temp[t_size - 2] = c;
        temp[t_size - 1] = '\0';
        myString result(temp);
        delete []temp;
        return result;
    }

bool myString::operator==(myString str)
{
	return !strcmp(this->data,str.data);
}

bool myString::operator==(char * str)
{
	return !strcmp(this->data,str);
}

bool myString::operator!=(myString str)
{
	return strcmp(this->data,str.data);
}

bool myString::operator!=(char * str)
{
	return !strcmp(this->data,str);
}

myString & myString::operator=(const myString str)
{
	if(&str == this)
		return *this;
	delete []data;
        len = str.len;
        data = new char[len + 1];
        strcpy(data, str.data);
        return *this;
}

myString & myString::operator=(char * str)
{
	delete []data;
        len = strlen(str);
        data = new char[len + 1];
        strcpy(data, str);
        return *this;
}

std::ostream& operator<<(std::ostream& os,  myString& str)
{
    return os << str.data_();
}
 
std::istream& operator>>(std::istream& is, myString& str)
{
    char BUFF[2048];
    is.getline(BUFF, sizeof(BUFF));
    str = BUFF;
    return is;
}
 