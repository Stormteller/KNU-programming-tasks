#include "fraktal.h"
#include <GL\glut.h> 
#include <stack>

class turtle {
public: double x=0;
		double y=0;
		double alpha=0;
};

Fractal my;

void display(void)
{
	my.size /= 1.5;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	turtle t;
	stack<turtle> stackT;
	glBegin(GL_LINE_STRIP);
	glVertex2d(t.x, t.y);
	for (unsigned i = 0; i < my.fraktal.size();i++) {
		string s = "0";
		s[0] = my.fraktal[i];
		map<string, string>::iterator it = my.interpretation.find(s);
		if(it!=my.interpretation.end())
			s = it->second;
		else s = " ";
		switch(s[0])
		{
		case 'F':
			t.x = t.x + my.size*cos(t.alpha);
			t.y = t.y + my.size*sin(t.alpha);
			glVertex2d(t.x, t.y);
			break;
		/*case 'S':
			stackT.push(t);
			break;
		case 'R':
			t = stackT.top();
			stackT.pop();
			break;*/
		default:
			if (s[0] == '-' || (s[0] >= '0' && s[0] <= '9')) {
				double a = stod(s);
				t.alpha += a / 180 * 3.14;
			}
			break;
		}
	}
	glEnd();
	glFlush();
}

void mouseclick(int button, int state, int x, int y)
{
	if (button != GLUT_RIGHT_BUTTON) my.makeFractal();
	glutPostRedisplay();
}

void init(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 2, 0, 2);
}

void start()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Fraktal");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouseclick);
	glutMainLoop();
}

void main() {
	my.pf = &display;
	start();
	my.makeFractal();
	system("pause");
}