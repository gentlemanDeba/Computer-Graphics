#include <GL/glut.h>
#include <stdio.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define INSIDE 0b0000
#define LEFT 0b0001
#define RIGHT 0b0010
#define BOTTOM 0b0100
#define TOP 0b1000

typedef struct Point
{
	float x, y;
} Point;

int generateCode(Point p, float window[])
{
	int code = INSIDE;
	if (p.x < window[0])
		code = code | LEFT;
	else if (p.x > window[1])
		code = code | RIGHT;
	if (p.y < window[2])
		code = code | BOTTOM;
	else if (p.y > window[3])
		code = code | TOP;

	return code;
}

int accept(int code1, int code2)
{
	return (!(code1 | code2));
}

int reject(int code1, int code2)
{
	return (code1 & code2);
}

void cohenSutherland(Point line[], float window[])
{
	int codeP1 = generateCode(line[0], window);
	int codeP2 = generateCode(line[1], window);
	int acceptLine = 0;

	while (1)
	{
		if (accept(codeP1, codeP2))
		{
			acceptLine = 1;
			break;
		}
		else if (reject(codeP1, codeP2))
		{
			break;
		}
		else
		{
			float slope = (line[1].y - line[0].y) /
						  (line[1].x - line[0].x);

			int codeOuter = codeP1 ? codeP1 : codeP2;

			Point pt;

			if (codeOuter & LEFT)
			{
				pt.y = slope * (window[0] - line[0].x) +
					   line[0].y;
				pt.x = window[0];
			}
			else if (codeOuter & RIGHT)
			{
				pt.y = slope * (window[1] - line[0].x) +
					   line[0].y;
				pt.x = window[1];
			}
			else if (codeOuter & BOTTOM)
			{
				pt.x = line[0].x +
					   (window[3] - line[0].y) / slope;
				pt.y = window[3];
			}
			else if (codeOuter & TOP)
			{
				pt.x = line[0].x +
					   (window[4] - line[0].y) / slope;
				pt.y = window[4];
			}

			if (codeOuter == codeP1)
			{
				line[0].x = pt.x;
				line[0].y = pt.y;
				codeP1 = generateCode(line[0], window);
			}
			else
			{
				line[1].x = pt.x;
				line[1].y = pt.y;
				codeP2 = generateCode(line[1], window);
			}
		}
	}

	if (acceptLine)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
		glVertex2f(line[0].x, line[0].y);
		glVertex2f(line[1].x, line[1].y);
		glEnd();
	}
}

void drawPolygon(Point *verts)
{
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(verts[i].x, verts[i].y);
	}
	glEnd();
}

void drawAxes()
{
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(-(int)(WIN_WIDTH / 2), 0);
	glVertex2f((int)(WIN_WIDTH / 2), 0);
	glVertex2f(0, -(int)(WIN_HEIGHT / 2));
	glVertex2f(0, (int)(WIN_HEIGHT / 2));
	glEnd();
}

void displayFunc()
{
	float window[4] = {30.0, 70.0, 120.0, 80.0};
	Point verts[4] = {{window[0], window[2]},
					  {window[1], window[2]},
					  {window[1], window[3]},
					  {window[0], window[3]}};

	glClearColor(0.0, 0.0, 0.0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	Point line[2] = {{10.0, 30.0}, {240.0, 180.0}};
	drawPolygon(verts);
	cohenSutherland(line, window);

	drawAxes();
	glFlush();
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-WIN_WIDTH / 2, WIN_WIDTH / 2, -WIN_HEIGHT / 2,
			   WIN_HEIGHT / 2);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutCreateWindow("2D Line CLipping (Cohen-Sutherland Algorithm)");

	init();
	glutDisplayFunc(displayFunc);
	glutMainLoop();

	return 0;
}
