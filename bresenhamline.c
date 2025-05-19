#include <GL/freeglut.h>
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

	printf("Slope: %f\n", (float)dy / dx);

	int p = 2 * dy - dx;
	int x = x0;
	int y = y0;

	glColor3f(0.416, 0.173, 0.439);
	glBegin(GL_POINTS);
	for (int i = x0; i < xEnd; i++) {
		if (p < 0) {
			glVertex2i(x, y);
			p = p + 2 * dy;
		} else {
			glVertex2i(x, y);
			p = p + 2 * dy - 2 * dx;
			y = y + 1;
		}
		x = x + 1;
	}
	glEnd();
}

void drawAxes()
{
	glColor3f(0.941, 0.541, 0.365);
	glBegin(GL_LINES);
	glVertex2f(ORTHO_LEFT, 0);
	glVertex2f(ORTHO_RIGHT, 0);
	glVertex2f(0, ORTHO_BOTTOM);
	glVertex2f(0, ORTHO_TOP);
	glEnd();
}

void displayFunc()
{
	glClearColor(0.976, 0.929, 0.412, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	drawAxes();
	drawLine(1,1,5,3);
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