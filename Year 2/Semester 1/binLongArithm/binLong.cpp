#include "binLong.h"

binLong::binLong(std::string s) : number(NMAX, 0) {
	if (s.length() <= this->NMAX) {
		this->len = 0;
		if (s[0] == '+' || s[0] == '-') {
			if (s[0] == '+') {
				this->number[0] = 0;
				this->len++;
			}
			else {
				this->number[0] = 225;
				this->len++;
			}
			int last = 1;
			while (s[last] == '0') last++;
			for (int i = s.length() - 1; i > last - 1; i--) {
				if (s[i] == '0' || s[i] == '1') {
					this->number[this->len] = s[i] - '0';
					this->len++;
				}
				else {
					throw std::invalid_argument("Invalid argument");
				}
			}
			if (this->len == 1) { this->len++; }
		}
		else {
			throw std::invalid_argument("Invalid argument");
		}
	}
	else {
		throw std::invalid_argument("Too long");
	}
}

binLong::binLong(const binLong &num) : binLong::binLong(num.numToStr())  {}

std::string binLong::plusAbs(binLong operand) {
	std::string resStr = "";
	unsigned short extraDigit = 0;
	for (int i = 1; i < std::max(this->length(), operand.length()) + 1; i++) {
		unsigned short currRes = (*this)[i] + operand[i] + extraDigit;
		extraDigit = currRes / 2;
		currRes %= 2;
		resStr = static_cast<char>(currRes + '0') + resStr;
	}
	
	return resStr;
}

std::string binLong::minusAbs(binLong operand) {
	std::string resStr = "";
	binLong *op1;
	binLong *op2;
	if (this->compareAbs(operand) == 1) {
		op1 = new binLong(*this);
		op2 = new binLong(operand);
	}
	else {
		if (this->compareAbs(operand) == -1) {
			op1 = new binLong(operand);
			op2 = new binLong(*this);
		}
		else { return "0"; }
	}

	short extraDigit = 0;
	for (int i = 1; i < std::max(op1->length(), op2->length()); i++) {
		short currDigit = (*op1)[i] - (*op2)[i];
		if (extraDigit) { currDigit--; extraDigit++; }
		if (currDigit < 0) { extraDigit--; }
		resStr = char(abs(currDigit) % 2 + '0') + resStr;
	}
	
	return resStr;
}

binLong binLong::operator+(binLong operand) {
	std::string resStr;
	if (this->sameSign(operand)) {
		resStr = this->plusAbs(operand);
		(*this)[0] ? resStr = '-' + resStr : resStr = '+' + resStr;
	}
	else {
		if (this->compareAbs(operand) == 1 && !(this->isPositive())) {
			resStr = '-' + this->minusAbs(operand);
		}
		if (this->compareAbs(operand) == 1 && this->isPositive()) {
			resStr = '+' + this->minusAbs(operand);
		}
		if (this->compareAbs(operand) == -1 && !(this->isPositive())) {
			resStr = '+' + this->minusAbs(operand);
		}
		if (this->compareAbs(operand) == -1 && this->isPositive()) {
			resStr = '-' + this->minusAbs(operand);
		}
		if (this->compareAbs(operand) == 0) {
			resStr = "+0";
		}
	}

	return binLong(resStr);
}

binLong binLong::operator-(binLong operand)
{
	std::string resStr = "";
	operand.toggleSign();
	return (*this) + operand;
}

binLong binLong::operator*(binLong operand)
{
	std::string resSrt = "";
	binLong resNum("+0");

	for (int i = 1; i < operand.length(); i++) {
		if (operand[i]) {
			std::string currStr = this->numToStr();
			for (int j = 0; j < i - 1; j++) {
				currStr += '0';
			}

			resNum = (resNum) + binLong(currStr);
			
		}
	}

	if (this->sameSign(operand)) { resNum.setSign('+'); }
	else { resNum.setSign('-'); }

	return resNum;
}

binLong binLong::operator/(binLong operand)
{
	if(operand.compareAbs(binLong("+0")) == 0) {
		std::invalid_argument("Division by zero");
	}
	else {
		binLong counter("+0");

		if (!this->sameSign(operand)) { this->toggleSign(); }
		binLong currNum(*this);

		while (currNum.compareAbs(operand) >= 0) {
			currNum = currNum - operand;
			counter = counter + binLong("+1");
		}

		if (this->sameSign(operand)) { this->toggleSign(); }

		if (this->sameSign(operand)) { counter.setSign('+'); }
		else { counter.setSign('-'); }

		return counter;
	}
}

void binLong::toggleSign()
{
	if (this->number[0] == 0) { this->number[0] = 225; }
	else { this->number[0] = 0; }
}

bool binLong::isPositive()
{
	if (number[0] == 0) return true;
	return false;
}

bool binLong::sameSign(binLong operand)
{
	if (this->number[0] == operand[0]) return true;
	return false;
}

int binLong::compareAbs(binLong operand)
{
	if (this->len > operand.length()) return 1;
	if (this->len < operand.length()) return -1;
	for (int i = this->len - 1; i > 0; i--) {
		if ((*this)[i] > operand[i]) return 1;
		if ((*this)[i] < operand[i]) return -1;
	}
	return 0;
}

void binLong::setSign(char sign)
{
	if (sign == '+' || sign == '-') {
		sign == '+' ? this->number[0] = 0 : this->number[0] = 225;
	}
	else {
		std::invalid_argument("Invalid argument");
	}
}

unsigned short binLong::operator[](int index)
{
	if (index >= NMAX) {
		throw std::invalid_argument("Out of range");
	}
	else {
		return this->number[index];
	}
}

std::string binLong::numToStr() const
{
	std::string resStr = "";
	if (this->number[0]) { resStr += '-'; }
	else { resStr += '+'; }
	for (int i = this->len - 1; i > 0; i--) {
		resStr += this->number[i] + '0';
	}
	return resStr;
}

void binLong::print()
{
	std::cout << this->numToStr() << '\n';
}

int binLong::length() const
{
	return this->len;
}

binLong::~binLong() {}

