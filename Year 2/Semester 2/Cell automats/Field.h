#pragma once
#include <vector>
#include "utils.h"
#include "OpenGLControl.h"
#include <cmath>


class Field
{
	int size;
	std::vector<std::vector<Cell>> field;
	int resettlRadius;
	int breedRadius;
	int fertility;
	float density;
	int numOfSpecies;
	int numOfGenerations;
	BreedingType brType;

	const static float colors[30];

	void agamobBreed(int cellX, int cellY, int spec, std::vector<std::vector<bool>>& used);
public:
	Field(Settings settings);
	virtual ~Field();
	void drawGrid();
	void init();
	void drawField();
	void nextStep();
	int getGenerNum();
};
