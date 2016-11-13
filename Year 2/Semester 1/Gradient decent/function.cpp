#include "function.h"

function::function(std::ifstream &fin) {
	//Use -F(x) to find maximum
	double data;
	fin >> this->varAmount >> this->condAmount;
	//Read a-coefficients
	for (int i = 0; i < varAmount; i++) {
		fin >> data;
		this->aCoefs.push_back(-data);
	}
	//Read b-coefficients
	for (int i = 0; i < varAmount; i++) {
		fin >> data;
		this->bCoefs.push_back(-data);
	}
	//Read c-coefficients matrix
	for (int i = 0; i < condAmount; i++) {
		std::vector<double> row;
		for (int j = 0; j < varAmount; j++) {
			fin >> data;
			row.push_back(data);
		}
		this->cCoefs.push_back(row);
	}
	//Read d-coefficients
	for (int i = 0; i < condAmount; i++) {
		fin >> data;
		this->dCoefs.push_back(data);
	}
}

function::~function(){}

//Calculate function value in point
double function::value(std::vector<double> x) {
	double val = 0;	//fucntion value
	for (int i = 0; i < varAmount; i++) {
		val += x[i] * aCoefs[i] + x[i] * x[i] * bCoefs[i];
	}
	return val;
}

//Calculate function gradient in point
std::vector<double> function::gradient(std::vector<double> x) {
	std::vector<double> grad; //gradient in point x
	for (int i = 0; i < varAmount; i++) {
		grad.push_back(aCoefs[i] + 2 * bCoefs[i] * x[i]);
	}
	return grad;
}

//Check point satisfies conditions system
bool function::checkCondition(std::vector<double> x) {
	bool condition = true;

	//If condition exist 
	if (condAmount) {
		for (int i = 0; i < condAmount; i++) {
			double currSum = 0;
			for (int j = 0; j < varAmount; j++) {
				currSum += cCoefs[i][j] * x[j];
			}
			//check inequality
			if (currSum > dCoefs[i]) {
				condition = false; break;
			}
		}
	}
	return condition;
}


//Find extremum using gradient descent method
std::vector<double> function::gradientDescent(std::vector<double> startX) {
	std::vector<double> oldX;	//Previous point
	std::vector<double> currX = startX;	//Current point
	std::vector<double> grad;	//Gradient in current point
	std::vector <double> lastInCondition;	//Last point satisfied condtions
	double lambda = LAMBDA;	//Current lambda coef in gradient descent
	const int MAX_ITERATIONS = 10000;//Max number of iterations
	int iterator = 0;	//Current iteration
	double accuracyEps = 1e-5;	//Accuracy

	//Check start point satisfies condition
	if (checkCondition(currX)) {
		do {
			oldX = currX;	//Update previous point
			grad = gradient(currX);	//Recalculate gradient

			//Calculate next point
			for (int j = 0; j < currX.size(); j++) {
				currX[j] = currX[j] - lambda*grad[j];
			}

			//Square of norm of the gradient
			double normGradSqr = 0;
			for (int j = 0; j < currX.size(); j++) {
				normGradSqr += grad[j] * grad[j];
			}

			//Check need to decrease lambda
			while (value(currX) > value(oldX) - EPS*lambda*normGradSqr) {
				//lambda recounting
				lambda = lambda*DELTA;
				//Recounting current value with new lambda
				currX = oldX;
				for (int j = 0; j < currX.size(); j++)
					currX[j] = currX[j] - lambda*grad[j];
			}

			//If current point in conditions - update lastInCondition
			if (checkCondition(currX)) {
				lastInCondition = currX;
			} else {
				//Calculate new point that satisfies condition
				double oldLambda = lambda;	//save current lambda
				bool ignorCycleCond = false;	//Ignore cycle quit-conditions if new point is too close to current
				while (!checkCondition(currX)) {
					lambda = lambda*DELTA;
					currX = oldX;
					for (int j = 0; j < currX.size(); j++)
						currX[j] = currX[j] - lambda*grad[j];
					if ((fabs(value(currX) - value(oldX)) <= accuracyEps)) {
						ignorCycleCond = true;
						break;
					}
				}
				lastInCondition = currX;
				lambda = oldLambda;	
				if (ignorCycleCond) { continue; }
			}	
			iterator++;
		} while (iterator < MAX_ITERATIONS && (fabs(value(currX) - value(oldX)) > accuracyEps));	//Continue if points is not too close


	}
	else {
		throw std::exception("Bad start point");
	}
	std::cout << iterator << std::endl;
	return lastInCondition;	//Return extremum in conditioned area
}