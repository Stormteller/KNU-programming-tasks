#include <gl\glut.h>
#include <vector>
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

using namespace std;

struct State {

	vector<vector<int>> field;
	int size;
	bool tick = true;
};

class Memento {
	State state;

public:
	Memento(State st) {
		state = st;
	}

	State getState() {
		return state;
	}
};

class FieldCaretaker {
	Memento* memento;

public:
	FieldCaretaker() {}

	Memento* getMemento() {
		return memento;
	}

	void setMemento(Memento* mem) {
		memento = mem;
	}
};

class Field {
	State state;
public:

	Field() {
		state.size = 3;
		state.field.resize(state.size, vector<int>(state.size, 0));
	}

	void drawGrid() {
		glColor3d(0, 0, 0);
		glBegin(GL_LINES);
			glVertex2d(0.33, 0);
			glVertex2d(0.33, 1);
			glVertex2d(0.66, 0);
			glVertex2d(0.66, 1);
			glVertex2d(0, 0.33);
			glVertex2d(1, 0.33);
			glVertex2d(0, 0.66);
			glVertex2d(1, 0.66);
		glEnd();
	}

	State getState() {
		return state;
	}

	void setState(State st) {
		state = st;
	}

	Memento * saveState() {
		return new Memento(state);
	}

	void restoreState(Memento* memento) {
		state = memento->getState();
	}

	void putTick(int x, int y) {
		state.field[x][y] = 1;
	}

	void putTac(int x, int y) {
		state.field[x][y] = 2;
	}

	void drawEllipse(float radius, float x, float y)
	{
		const float DEG2RAD = 3.14159 / 180.0;
		glBegin(GL_LINE_LOOP);

		for (int i = 0; i < 360; i++)
		{
			//convert degrees into radians
			float degInRad = i*DEG2RAD;
			glVertex2f(cos(degInRad)*radius + x, sin(degInRad)*radius + y);
		}
		glEnd();
	}

	void drawField() {
		glColor3d(0, 0, 0);
		
		for (int i = 0; i < state.size; i++) {
			for (int j = 0; j < state.size; j++) {
				if (state.field[i][j] == 1) {
					glBegin(GL_LINES);
						glVertex2d(i*0.34, j*0.34);
						glVertex2d(i*0.34 + 0.32, j*0.34 + 0.32);

						glVertex2d(i*0.34 + 0.32, j*0.34);
						glVertex2d(i*0.34, j*0.34 + 0.32);
					glEnd();
				}
				if (state.field[i][j] == 2) {
					drawEllipse(0.15, i*0.33 + 0.17, j*0.33 + 0.17);
				}
			}
		}
	}

	void clear() {
		state.field.assign(state.size, vector<int>(state.size, 0));
		state.tick = true;
	}

	void changeTick() {
		state.tick = !state.tick;
	}

	bool getTick() {
		return state.tick;
	}
};


Field field;
FieldCaretaker fieldCaretaker;


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	field.drawField();
	field.drawGrid();
	glFlush();
	glutPostRedisplay();
	
}

void init(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1, 1, 0);
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 'c' || key == 'C')
	{
		field.clear();
	}
	if (key == 'x' || key == 'X')
	{
		field.restoreState(fieldCaretaker.getMemento());
		//step back
		
	}
}

void mouse(int button, int state, int x, int y) {
	if (state == 1) {
		fieldCaretaker.setMemento(field.saveState());
		float orthoX = x / (float)700;
		float orthoY = y / (float)700;
		int i = orthoX / 0.33;
		int j = orthoY / 0.33;
		if (field.getTick()) field.putTick(i, j);
		if (!field.getTick()) field.putTac(i, j);
		field.changeTick();
	}
}

void main() {
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tic-tac-toe");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glClearColor(1.0, 1.0, 1.0, 1);
	glutMainLoop();
}