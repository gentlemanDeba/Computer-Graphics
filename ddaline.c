#include <GL/freeglut.h>
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

	glColor3f(0.416, 0.173, 0.439);
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
	drawLine(20, -5, -15, 10);
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