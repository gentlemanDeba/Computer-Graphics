#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define POINT_SIZE 10

#define ORTHO_LEFT -(int)(WIN_WIDTH / POINT_SIZE) / 2
#define ORTHO_RIGHT (int)(WIN_WIDTH / POINT_SIZE) / 2
#define ORTHO_BOTTOM -(int)(WIN_HEIGHT / POINT_SIZE) / 2
#define ORTHO_TOP (int)(WIN_HEIGHT / POINT_SIZE) / 2

void drawLine(int x0, int y0, int xEnd, int yEnd)
{
	int dx = abs(xEnd - x0);
	int dy = abs(yEnd - y0);

	int sx = (x0 < xEnd) ? 1 : -1;
	int sy = (y0 < yEnd) ? 1 : -1;

	int err = dx - dy;

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POINTS);

	while (1) {
		glVertex2i(x0, y0);

		if (x0 == xEnd && y0 == yEnd)
			break;

		int e2 = 2 * err;
		if (e2 > -dy) {
			err = err - dy;
			x0 += sx;
		}
		if (e2 < dx) {
			err = err + dx;
			y0 += sy;
		}
	}
	glEnd();
}

void drawAxes()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2i(ORTHO_LEFT, 0);
	glVertex2i(ORTHO_RIGHT, 0);
	glVertex2i(0, ORTHO_BOTTOM);
	glVertex2i(0, ORTHO_TOP);
	glEnd();
}

void displayFunc()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	drawAxes();
	drawLine(-10,-25,5,17);

	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutCreateWindow("Bresenham Line");

	gluOrtho2D(ORTHO_LEFT, ORTHO_RIGHT, ORTHO_BOTTOM, ORTHO_TOP);
	glPointSize(POINT_SIZE);

	glutDisplayFunc(displayFunc);
	glutMainLoop();
}