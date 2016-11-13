#include <iostream>
#include <string>

using namespace std;

class Worker;
class Company;
class IVisitor {
public:
	virtual void visit(Worker*) = 0;
	virtual void visit(Company*) = 0;
};

class IVisitable {
public:
	virtual void accept(IVisitor*) = 0;
};

class Worker : public IVisitable {
	string name;
	double salary;
public: 
	Worker(string n, double s) {
		name = n;
		salary = s;
	}

	string getName() {
		return name;
	}

	double getSalary() {
		return salary;
	}

	void accept(IVisitor* visitor) {
		visitor->visit(this);
	}
};

class Company : public IVisitable {
	string name;
	double revenue;
public:
	Company(string n, double r) {
		name = n;
		revenue = r;
	}

	string getName() {
		return name;
	}

	double getRevenue() {
		return revenue;
	}

	void accept(IVisitor* visitor) {
		visitor->visit(this);
	}
};

class TaxCalculator : public IVisitor {
	double sumWorkerTaxes;
	double sumCompanyTaxes;
public:
	void visit(Worker* worker) {
		double tax = worker->getSalary() * 0.2;
		cout << worker->getName() << ": " << tax << endl;
		sumWorkerTaxes += tax;
	}

	void visit(Company* company) {
		double tax = company->getRevenue() * 0.13;
		cout << company->getName() << ": " << round(tax) << endl;
		sumCompanyTaxes += tax;
	}

	double getSumWorkersTaxes() {
		return sumWorkerTaxes;
	}

	double getSumCompanyTaxes() {
		return sumCompanyTaxes;
	}
};

int main() {
	Worker* w1 = new Worker("Bob", 70000);
	Worker* w2 = new Worker("Steve", 120000);
	Company* c1 = new Company("MelkomyagkyaCorp", 10000000);

	TaxCalculator* tc = new TaxCalculator();

	w1->accept(tc);
	w2->accept(tc);
	c1->accept(tc);

	cout << tc->getSumWorkersTaxes() << endl;

	system("pause");
	return 0;
}