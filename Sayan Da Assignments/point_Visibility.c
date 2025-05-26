#include <GL/glut.h>
#include <stdio.h>

#define MAX 100

int n;
float polyX[MAX], polyY[MAX];
float pointX, pointY;
int isVisible = 0;

int isPointInsidePolygon(float x, float y)
{
    int i, j, c = 0;
    for (i = 0, j = n - 1; i < n; j = i++)
    {
        if (((polyY[i] > y) != (polyY[j] > y)) &&
            (x < (polyX[j] - polyX[i]) * (y - polyY[i]) / (polyY[j] - polyY[i]) + polyX[i]))
            c = !c;
    }
    return c;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.5f, 0.5f, 1.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++)
    {
        glVertex2f(polyX[i], polyY[i]);
    }
    glEnd();

    if (isVisible)
        glColor3f(1.0, 0.0, 0.0);
    else
        glColor3f(0.0, 1.0, 0.0);

    glPointSize(6.0);
    glBegin(GL_POINTS);
    glVertex2f(pointX, pointY);
    glEnd();

    glFlush();
}

void init()
{
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv)
{
    printf("Enter number of polygon vertices: ");
    scanf("%d", &n);

    if (n < 3)
    {
        printf("A polygon must have at least 3 vertices.\n");
        return 0;
    }

    printf("Enter polygon vertices (x y):\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%f %f", &polyX[i], &polyY[i]);
    }

    printf("Enter test point (x y): ");
    scanf("%f %f", &pointX, &pointY);

    isVisible = isPointInsidePolygon(pointX, pointY);

    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Point Visibility Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
