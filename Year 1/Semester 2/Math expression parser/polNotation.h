#pragma once

#include <string>
#include <vector>

bool isOp(char);
bool isOp(std::string);
int priority(char);
int priority(std::string);
bool isNumber(std::string str);
bool isVariable(char);
bool isVariable(std::string);
std::string avoidUnary(std::string);
std::string getPolNotation(std::string);
std::vector<std::string> strToArray(std::string,char);