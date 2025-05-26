#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

typedef struct Point
{
    float x, y;
} Point;

int nVerts;
Point *verts = NULL;
Point *transVerts = NULL;
float tx = 0, ty = 0;

void translate(Point verts[], Point transVerts[], int nVerts, float tx, float ty)
{
    for (int i = 0; i < nVerts; i++)
    {
        transVerts[i].x = verts[i].x + tx;
        transVerts[i].y = verts[i].y + ty;
    }
}

void drawPolygon(int nVerts, Point *verts, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < nVerts; i++)
    {
        glVertex2f(verts[i].x, verts[i].y);
    }
    glEnd();
}

void drawAxes()
{
    glColor3f(0.8f, 0.8f, 0.8f); // Light grey axes
    glBegin(GL_LINES);
    glVertex2i(-WIN_WIDTH / 2, 0);
    glVertex2i(WIN_WIDTH / 2, 0);
    glVertex2i(0, -WIN_HEIGHT / 2);
    glVertex2i(0, WIN_HEIGHT / 2);
    glEnd();
}

void displayFunc()
{
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f); // Background color
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();
    drawPolygon(nVerts, verts, 0.0f, 1.0f, 0.8f);      // Cyan-green (original)
    drawPolygon(nVerts, transVerts, 1.0f, 0.6f, 0.2f); // Orange (translated)

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
    transVerts = (Point *)malloc(sizeof(Point) * nVerts);

    printf("Enter coordinates of each vertex (x y):\n");
    for (int i = 0; i < nVerts; i++)
    {
        printf("Vertex %d: ", i + 1);
        scanf("%f %f", &verts[i].x, &verts[i].y);
    }

    printf("Enter translation vector (tx ty): ");
    scanf("%f %f", &tx, &ty);

    translate(verts, transVerts, nVerts, tx, ty);

    glutInit(&argc, argv);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("User-defined 2D Polygon Translation");

    init();
    glutDisplayFunc(displayFunc);
    glutMainLoop();

    free(verts);
    free(transVerts);

    return 0;
}
