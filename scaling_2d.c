#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

typedef struct Point {
    float x, y;
} Point;

int nVerts;
Point *verts = NULL;
Point *scaleVerts = NULL;
Point fixedPt;
float sx, sy;

void scale(Point verts[], Point scaleVerts[], Point fixedPt, int nVerts, float sx, float sy)
{
    for (int i = 0; i < nVerts; i++) {
        scaleVerts[i].x = verts[i].x * sx + fixedPt.x * (1 - sx);
        scaleVerts[i].y = verts[i].y * sy + fixedPt.y * (1 - sy);
    }
}

void drawPolygon(int nVerts, Point *verts, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < nVerts; i++) {
        glVertex2f(verts[i].x, verts[i].y);
    }
    glEnd();
}

void drawAxes()
{
    glColor3f(0.7f, 0.7f, 0.7f); // Light grey
    glBegin(GL_LINES);
    glVertex2i(-WIN_WIDTH / 2, 0);
    glVertex2i(WIN_WIDTH / 2, 0);
    glVertex2i(0, -WIN_HEIGHT / 2);
    glVertex2i(0, WIN_HEIGHT / 2);
    glEnd();
}

void displayFunc()
{
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f); // Dark background
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();
    drawPolygon(nVerts, verts, 0.0f, 1.0f, 0.6f);         // Original polygon (cyan-green)
    drawPolygon(nVerts, scaleVerts, 1.0f, 0.5f, 0.2f);    // Scaled polygon (orange)

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

    verts = (Point *)malloc(nVerts * sizeof(Point));
    scaleVerts = (Point *)malloc(nVerts * sizeof(Point));

    printf("Enter coordinates of each vertex (x y):\n");
    for (int i = 0; i < nVerts; i++) {
        printf("Vertex %d: ", i + 1);
        scanf("%f %f", &verts[i].x, &verts[i].y);
    }

    printf("Enter scaling fixed point (x y): ");
    scanf("%f %f", &fixedPt.x, &fixedPt.y);

    printf("Enter scaling factors (sx sy): ");
    scanf("%f %f", &sx, &sy);

    scale(verts, scaleVerts, fixedPt, nVerts, sx, sy);

    glutInit(&argc, argv);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("User-defined 2D Polygon Scaling");

    init();
    glutDisplayFunc(displayFunc);
    glutMainLoop();

    free(verts);
    free(scaleVerts);

    return 0;
}
