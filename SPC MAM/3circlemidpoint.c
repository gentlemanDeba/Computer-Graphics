#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define POINT_SIZE 10

int Xc, Yc, Radius;

#define ORTHO_LEFT -(int)(WIN_WIDTH / POINT_SIZE) / 2
#define ORTHO_RIGHT (int)(WIN_WIDTH / POINT_SIZE) / 2
#define ORTHO_BOTTOM -(int)(WIN_HEIGHT / POINT_SIZE) / 2
#define ORTHO_TOP (int)(WIN_HEIGHT / POINT_SIZE) / 2

void drawCircle(int xc, int yc, int r)
{
	int p = 1 - r;
	int x = 0;
	int y = r;

	while (x <= y) {
		glColor3f(0.1f, 0.2f, 0.8f);
		glBegin(GL_POINTS);
		glVertex2i(xc + x, yc + y);
		glVertex2i(xc + x, yc - y);
		glVertex2i(xc - x, yc + y);
		glVertex2i(xc - x, yc - y);
		glVertex2i(xc + y, yc + x);
		glVertex2i(xc + y, yc - x);
		glVertex2i(xc - y, yc + x);
		glVertex2i(xc - y, yc - x);
		glEnd();

		x = x + 1;
		if (p < 0) {
			p = p + 2 * x + 1;
		} else {
			y = y - 1;
			p = p + 2 * x - 2 * y + 1;
		}

		printf("(%d, %d)\n", x, y);
	}
}

void drawAxes()
{
	glColor3f(0.2f, 0.3f, 0.5f);
	glBegin(GL_LINES);
	glVertex2i(ORTHO_LEFT, 0);
	glVertex2i(ORTHO_RIGHT, 0);
	glVertex2i(0, ORTHO_BOTTOM);
	glVertex2i(0, ORTHO_TOP);
	glEnd();
}

void displayFunc()
{
	glClearColor(0.85f, 0.95f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	drawAxes();
	drawCircle(Xc, Yc, Radius);
	glFlush();
}

int main(int argc, char **argv)
{
	printf("Enter Xc, Yc and Radius: ");
	scanf("%d %d %d", &Xc, &Yc, &Radius);

	glutInit(&argc, argv);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutCreateWindow("MidPoint Circle");

	gluOrtho2D(ORTHO_LEFT, ORTHO_RIGHT, ORTHO_BOTTOM, ORTHO_TOP);
	glPointSize(POINT_SIZE);

	glutDisplayFunc(displayFunc);
	glutMainLoop();
}