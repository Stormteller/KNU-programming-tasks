#pragma once
#include <fstream>
#include <iostream>
#include <vector>

//Given function
class function
{
public:
	function(std::ifstream&);	//Construstor, read data from stream
	~function();
	double value(std::vector<double>);	//Calculate function value in point
	std::vector<double> gradient(std::vector<double>);	//Calculate gradient in point
	std::vector<double> gradientDescent(std::vector<double>);	//Find extremum using gradient descent method
	bool checkCondition(std::vector<double>);	//Check point satisfies conditions system

private:
	std::vector<double> aCoefs;	//a-coefficients near Xi
	std::vector<double> bCoefs;	//b-coefficients near Xi^2
	std::vector<std::vector<double>> cCoefs;	//Matrix of c-coefficients of conditions 
	std::vector<double> dCoefs;	//d-coefficients in condition system
	int varAmount;	//Amount of variables
	int condAmount;	//Amount of conditions inequalities
	const double LAMBDA = 1;	//lambda coefficient in gradient descent
	const double DELTA = 0.95;	//delta coefficient in gradient descent
	const double EPS = 0.1;	//epsilon coefficient in gradient descent
};

