#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define POINT_SIZE 10

#define ORTHO_LEFT -(int)(WIN_WIDTH / POINT_SIZE) / 2
#define ORTHO_RIGHT (int)(WIN_WIDTH / POINT_SIZE) / 2
#define ORTHO_BOTTOM -(int)(WIN_HEIGHT / POINT_SIZE) / 2
#define ORTHO_TOP (int)(WIN_HEIGHT / POINT_SIZE) / 2

void drawLine(int x0, int y0, int xEnd, int yEnd)
{
	float x = x0, y = y0, xInc, yInc;

	int dx = xEnd - x0;
	int dy = yEnd - y0;

	int steps;

	if (abs(dx) > abs(dy)) {
		steps = abs(dx);
	} else {
		steps = abs(dy);
	}

	xInc = (float)dx / (float)steps;
	yInc = (float)dy / (float)steps;

	glColor3f(1.0f, 0.4f, 0.1f);
	glBegin(GL_POINTS);
	for (int i = 0; i <= steps; i++) {
		glVertex2f(roundf(x), roundf(y));
		x = x + xInc;
		y = y + yInc;
	}
	glEnd();
}

void drawAxes()
{
	glColor3f(0.2f, 0.2f, 0.6f);
	glBegin(GL_LINES);
	glVertex2i(ORTHO_LEFT, 0);
	glVertex2i(ORTHO_RIGHT, 0);
	glVertex2i(0, ORTHO_BOTTOM);
	glVertex2i(0, ORTHO_TOP);
	glEnd();
}

void displayFunc()
{
	glClearColor(0.9f, 0.95f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	drawAxes();
	drawLine(-30, 25, 30, -25);
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutCreateWindow("DDA Line");

	gluOrtho2D(ORTHO_LEFT, ORTHO_RIGHT, ORTHO_BOTTOM, ORTHO_TOP);
	glPointSize(POINT_SIZE);

	glutDisplayFunc(displayFunc);
	glutMainLoop();
}