#include <GL/glut.h>
#include <stdio.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define MAX 100

typedef struct Point {
    float x, y;
} Point;

int n;
Point poly[MAX];
Point testPoint;
int isVisible = 0;

int isPointInsidePolygon(Point point, Point poly[], int n)
{
    int i, j, c = 0;
    for (i = 0, j = n - 1; i < n; j = i++) {
        if (((poly[i].y > point.y) != (poly[j].y > point.y)) &&
            (point.x < (poly[j].x - poly[i].x) * (point.y - poly[i].y) / (poly[j].y - poly[i].y) + poly[i].x))
            c = !c;
    }
    return c;
}

void drawPolygon(int n, Point poly[], float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(poly[i].x, poly[i].y);
    }
    glEnd();
}

void drawAxes()
{
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_LINES);
    glVertex2i(-WIN_WIDTH / 2, 0);
    glVertex2i(WIN_WIDTH / 2, 0);
    glVertex2i(0, -WIN_HEIGHT / 2);
    glVertex2i(0, WIN_HEIGHT / 2);
    glEnd();
}

void display()
{
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();
    drawPolygon(n, poly, 0.3f, 0.6f, 1.0f);  // light blue polygon

    if (isVisible)
        glColor3f(1.0, 0.0, 0.0);  // red = inside
    else
        glColor3f(0.0, 1.0, 0.0);  // green = outside

    glPointSize(8.0);
    glBegin(GL_POINTS);
    glVertex2f(testPoint.x, testPoint.y);
    glEnd();

    glFlush();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-WIN_WIDTH / 2, WIN_WIDTH / 2, -WIN_HEIGHT / 2, WIN_HEIGHT / 2);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    printf("Enter number of polygon vertices: ");
    scanf("%d", &n);

    if (n < 3) {
        printf("A polygon must have at least 3 vertices.\n");
        return 0;
    }

    printf("Enter polygon vertices (x y):\n");
    for (int i = 0; i < n; i++) {
        printf("Vertex %d: ", i + 1);
        scanf("%f %f", &poly[i].x, &poly[i].y);
    }

    printf("Enter test point (x y): ");
    scanf("%f %f", &testPoint.x, &testPoint.y);

    isVisible = isPointInsidePolygon(testPoint, poly, n);

    glutInit(&argc, argv);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("Point-in-Polygon Visibility");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
