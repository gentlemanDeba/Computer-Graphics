#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

typedef struct Point {
    float x, y;
} Point;

const double pi = 3.14159265359;

int nVerts;
Point *verts = NULL;
Point *rotVerts = NULL;
Point pivot = { 0, 0 };
double theta = 0; // in radians

void rotate(Point verts[], Point rotVerts[], Point pvtPt, int nVerts, double theta)
{
    for (int i = 0; i < nVerts; i++) {
        rotVerts[i].x = pvtPt.x + (verts[i].x - pvtPt.x) * cos(theta) -
                        (verts[i].y - pvtPt.y) * sin(theta);
        rotVerts[i].y = pvtPt.y + (verts[i].x - pvtPt.x) * sin(theta) +
                        (verts[i].y - pvtPt.y) * cos(theta);
    }
}

void drawPolygon(Point *pts, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < nVerts; i++) {
        glVertex2f(pts[i].x, pts[i].y);
    }
    glEnd();
}

void drawAxes()
{
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_LINES);
    glVertex2i(-WIN_WIDTH / 2, 0);
    glVertex2i(WIN_WIDTH / 2, 0);
    glVertex2i(0, -WIN_HEIGHT / 2);
    glVertex2i(0, WIN_HEIGHT / 2);
    glEnd();
}

void drawPivot(Point p)
{
    glPointSize(8);
    glColor3f(1.0f, 1.0f, 0.0f); // yellow
    glBegin(GL_POINTS);
    glVertex2f(p.x, p.y);
    glEnd();
}

void displayFunc()
{
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();
    drawPolygon(verts, 0.0f, 1.0f, 1.0f);        // Cyan - original
    drawPolygon(rotVerts, 1.0f, 0.6f, 0.2f);     // Orange - rotated
    drawPivot(pivot);

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
    printf("Enter number of vertices: ");
    scanf("%d", &nVerts);

    verts = (Point *)malloc(sizeof(Point) * nVerts);
    rotVerts = (Point *)malloc(sizeof(Point) * nVerts);

    printf("Enter coordinates of each vertex (x y):\n");
    for (int i = 0; i < nVerts; i++) {
        printf("Vertex %d: ", i + 1);
        scanf("%f %f", &verts[i].x, &verts[i].y);
    }

    printf("Enter pivot point (x y): ");
    scanf("%f %f", &pivot.x, &pivot.y);

    printf("Enter angle of rotation in degrees: ");
    float angleDeg;
    scanf("%f", &angleDeg);
    theta = angleDeg * pi / 180.0;

    rotate(verts, rotVerts, pivot, nVerts, theta);

    glutInit(&argc, argv);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("User-defined Polygon Rotation");

    init();
    glutDisplayFunc(displayFunc);
    glutMainLoop();

    free(verts);
    free(rotVerts);

    return 0;
}
