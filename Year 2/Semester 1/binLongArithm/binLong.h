#pragma once
#include <string>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <vector>

class binLong
{
public:
	binLong(std::string);
	binLong(const binLong&);
	binLong operator+(binLong);
	binLong operator-(binLong);
	binLong operator*(binLong);
	binLong operator/(binLong);
	void toggleSign();
	bool isPositive();
	bool sameSign(binLong);
	int compareAbs(binLong);
	void setSign(char);
	unsigned short operator[](int);
	std::string numToStr() const;
	void print();
	int length() const;
	~binLong();

private:
	std::string plusAbs(binLong);
	std::string minusAbs(binLong);
	static const int NMAX = 10000;
	std::vector<unsigned short> number;
	int len;
};