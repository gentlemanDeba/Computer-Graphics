#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

typedef struct Point {
    float x, y;
} Point;

int nVerts;
Point *verts = NULL;
Point *reflVerts = NULL;
int reflectChoice;
Point pReflect;

void reflect(int nVerts, Point verts[], Point reflVerts[], Point pReflect)
{
    for (int i = 0; i < nVerts; i++) {
        reflVerts[i].x = -verts[i].x + 2 * pReflect.x;
        reflVerts[i].y = -verts[i].y + 2 * pReflect.y;
    }
}

void reflectX(int nVerts, Point verts[], Point reflVerts[])
{
    for (int i = 0; i < nVerts; i++) {
        reflVerts[i].x = verts[i].x;
        reflVerts[i].y = -verts[i].y;
    }
}

void reflectY(int nVerts, Point verts[], Point reflVerts[])
{
    for (int i = 0; i < nVerts; i++) {
        reflVerts[i].x = -verts[i].x;
        reflVerts[i].y = verts[i].y;
    }
}

void reflectDiag(int nVerts, Point verts[], Point reflVerts[])
{
    for (int i = 0; i < nVerts; i++) {
        reflVerts[i].x = verts[i].y;
        reflVerts[i].y = verts[i].x;
    }
}

void reflectDiag2(int nVerts, Point verts[], Point reflVerts[])
{
    for (int i = 0; i < nVerts; i++) {
        reflVerts[i].x = -verts[i].y;
        reflVerts[i].y = -verts[i].x;
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
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_LINES);
    glVertex2i(-WIN_WIDTH / 2, 0);
    glVertex2i(WIN_WIDTH / 2, 0);
    glVertex2i(0, -WIN_HEIGHT / 2);
    glVertex2i(0, WIN_HEIGHT / 2);
    glEnd();
}

void displayFunc()
{
    glClearColor(0.05f, 0.05f, 0.15f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();
    drawPolygon(nVerts, verts, 1.0, 0.0, 0.0); // original in red

    // Apply reflection based on user input
    switch (reflectChoice) {
        case 1: reflectX(nVerts, verts, reflVerts); break;
        case 2: reflectY(nVerts, verts, reflVerts); break;
        case 3: reflectDiag(nVerts, verts, reflVerts); break;
        case 4: reflectDiag2(nVerts, verts, reflVerts); break;
        case 5: reflect(nVerts, verts, reflVerts, pReflect); break;
        default: break;
    }

    drawPolygon(nVerts, reflVerts, 0.0, 1.0, 0.6); // reflected in cyan-green

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
    reflVerts = (Point *)malloc(nVerts * sizeof(Point));

    printf("Enter coordinates of each vertex (x y):\n");
    for (int i = 0; i < nVerts; i++) {
        printf("Vertex %d: ", i + 1);
        scanf("%f %f", &verts[i].x, &verts[i].y);
    }

    printf("\nReflection Options:\n");
    printf("1. About X-axis (y = 0)\n");
    printf("2. About Y-axis (x = 0)\n");
    printf("3. About y = x\n");
    printf("4. About y = -x\n");
    printf("5. About a custom point (x, y)\n");
    printf("Enter your choice (1-5): ");
    scanf("%d", &reflectChoice);

    if (reflectChoice == 5) {
        printf("Enter reflection point (x y): ");
        scanf("%f %f", &pReflect.x, &pReflect.y);
    }

    glutInit(&argc, argv);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("2D Polygon Reflection");

    init();
    glutDisplayFunc(displayFunc);
    glutMainLoop();

    free(verts);
    free(reflVerts);

    return 0;
}
