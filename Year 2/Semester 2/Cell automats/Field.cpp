#include "stdafx.h"
#include "Field.h"
#include <gl/gl.h>
#include <gl/glu.h>



const float Field::colors[30] = {
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	1.0, 1.0, 0.0,
	1.0, 0.0, 1.0,
	0.0, 1.0, 1.0,
	1.0, 0.2, 0.2,
	0.2, 0.2, 1.0,
	0.2, 1.0, 0.2,
	0.5, 0.7, 0.5
};


Field::Field(Settings settings)
{
	size = settings.fieldSize;
	resettlRadius = settings.resettlRadius;
	breedRadius = settings.breedRadius;
	fertility = settings.fertility;
	density = settings.density;
	numOfSpecies = settings.numOfSpecies;
	numOfGenerations = settings.numOfGenerations;
	brType = settings.brType;
	field.resize(size, std::vector<Cell>( size, Cell() ));
}


Field::~Field()
{
}

void Field::drawGrid() { 
	float rectWidth = 1;
 	int numberOfLines = size - 1;
	float currPointStart = rectWidth / size;
	glLineWidth(1.0);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	for (int i = 1; i <= numberOfLines; i++) {
		glVertex2d(0, currPointStart*i);
		glVertex2d(1, currPointStart*i);
		glVertex2d(currPointStart*i, 0);
		glVertex2d(currPointStart*i, 1);
	}
	glEnd();
}

void Field::init() {
	srand(time(NULL));
	int numberOfIndivids = size * size * density / numOfSpecies;
	for (int sp = 1; sp <= numOfSpecies; sp++) {
		for (int i = 0; i < numberOfIndivids; i++) {
			int randomX = rand() % size;
			int randomY = rand() % size;

			//rerandom
			if (field[randomX][randomY].spec) {
				bool set = false;
				for (int ri = randomX; ri < size && !set; ri++) {
					for (int rj = randomY; rj < size && !set; rj++) {
						if (!field[ri][rj].spec) field[ri][rj].spec = sp, set = true;
					}
				}
				for (int ri = 0; ri < randomX && !set; ri++) {
					for (int rj = 0; rj < randomY && !set; rj++) {
						if (!field[ri][rj].spec) field[ri][rj].spec = sp, set = true;
					}
				}
			}
			else field[randomX][randomY].spec = sp;
		}
	}

}

void Field::drawField() {
	float squareWidth = 1 / float(size);
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_QUADS);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (field[i][j].spec) {
				int indiv = field[i][j].spec;
				glColor3f(colors[(indiv - 1) * 3], colors[(indiv - 1) * 3 + 1], colors[(indiv - 1) * 3 + 2]);
				glVertex2f(squareWidth*i, squareWidth*j);
				glVertex2f(squareWidth*i, squareWidth*(j + 1));
				glVertex2f(squareWidth*(i + 1), squareWidth*(j + 1));
				glVertex2f(squareWidth*(i + 1), squareWidth*j);
			}
		}
	}
	glEnd();
}



void Field::agamobBreed(int cellX, int cellY, int spec, std::vector<std::vector<bool>>& used) {
	srand(time(NULL));
	field[cellX][cellY].spec = 0;
	int topLeftX = cellX - resettlRadius > 0 ? cellX - resettlRadius : 0;
	int topLeftY = cellY - resettlRadius > 0 ? cellY - resettlRadius : 0;

	int botLeftX = topLeftX;
	int botLeftY = cellY + resettlRadius < size ? cellY + resettlRadius : size - 1;

	int topRightX = cellX + resettlRadius < size ? cellX + resettlRadius : size - 1;
	int topRighttY = topLeftY;

	int botRightX = topRightX;
	int botRightY = botLeftY;

	for (int i = 0; i < fertility; i++) {
		int randomX = rand() % (abs(topRightX - topLeftX) + 1);
		int randomY = rand() % (abs(botLeftY - topLeftY) + 1);
		if (field[topLeftX + randomX][topLeftY + randomY].spec) {
			int kill = rand() % 2;
			if (kill) {
				field[topLeftX + randomX][topLeftY + randomY].spec = spec;
				used[topLeftX + randomX][topLeftY + randomY] = true;
			}
		}
		else {
			field[topLeftX + randomX][topLeftY + randomY].spec = spec;
			used[topLeftX + randomX][topLeftY + randomY] = true;
		}
	}
}



void Field::nextStep() {
	if (brType == Agamobium) {
		std::vector<std::vector<bool>> used(size, std::vector<bool>(size, false));
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (field[i][j].spec && !used[i][j]) {
					agamobBreed(i, j, field[i][j].spec, used);
				}
			}
		}
	} 
	if (brType == Syngenesis) {
		
	}
}

int Field::getGenerNum() {
	return numOfGenerations;
}
