#pragma once

enum BreedingType { Agamobium, Syngenesis  };

enum Sex { Male, Female };

struct Cell {
	int spec;
	//bool used;
	//Sex sex;

	Cell() {
		spec = 0;
		//used = false;
	}

	Cell(int sp) {
		spec = sp;
		//used = false;
	}

	/*Cell(int sp, bool u) {
		spec = sp;
		used = u;
	}*/
};

struct Settings {
	int fieldSize;
	int resettlRadius;
	int breedRadius;
	int fertility;
	float density;
	int numOfSpecies;
	int numOfGenerations;
	BreedingType brType;
};