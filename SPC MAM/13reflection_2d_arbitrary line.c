#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_VERTICES 100

typedef struct {
    float x, y;
} Point;

int nVerts;
Point origVerts[MAX_VERTICES];
Point reflVerts[MAX_VERTICES];
float A, B, C;  // Coefficients of the line Ax + By + C = 0

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

void drawAxes() {
    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_LINES);
    glVertex2f(-WIN_WIDTH / 2, 0);
    glVertex2f(WIN_WIDTH / 2, 0);
    glVertex2f(0, -WIN_HEIGHT / 2);
    glVertex2f(0, WIN_HEIGHT / 2);
    glEnd();
}

void drawPolygon(Point *verts, int n, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < n; i++) {
        glVertex2f(verts[i].x, verts[i].y);
    }
    glEnd();
}

void drawLineFromEquation(float A, float B, float C) {
    glColor3f(0.2, 0.6, 1.0);
    glBegin(GL_LINES);
    float x1 = -WIN_WIDTH / 2, x2 = WIN_WIDTH / 2;
    float y1, y2;

    if (B != 0) {
        y1 = (-A * x1 - C) / B;
        y2 = (-A * x2 - C) / B;
    } else {
        x1 = x2 = -C / A;
        y1 = -WIN_HEIGHT / 2;
        y2 = WIN_HEIGHT / 2;
    }

    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void reflectPointAcrossLine(Point *src, Point *dst, float A, float B, float C) {
    float d = A * A + B * B;
    float x = src->x, y = src->y;

    dst->x = x - 2 * A * (A * x + B * y + C) / d;
    dst->y = y - 2 * B * (A * x + B * y + C) / d;
}

void reflectPolygonAcrossLine(Point *src, Point *dst, int n, float A, float B, float C) {
    for (int i = 0; i < n; i++) {
        reflectPointAcrossLine(&src[i], &dst[i], A, B, C);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    drawLineFromEquation(A, B, C);

    drawPolygon(origVerts, nVerts, 1.0, 0.0, 0.0);     // Red: original
    drawPolygon(reflVerts, nVerts, 0.0, 1.0, 0.5);     // Cyan-green: reflected

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-WIN_WIDTH / 2, WIN_WIDTH / 2, -WIN_HEIGHT / 2, WIN_HEIGHT / 2);
}

int main(int argc, char **argv) {
    printf("Enter number of vertices: ");
    scanf("%d", &nVerts);

    if (nVerts > MAX_VERTICES) {
        printf("Too many vertices. Max allowed: %d\n", MAX_VERTICES);
        return 1;
    }

    printf("Enter the coordinates of each vertex (x y):\n");
    for (int i = 0; i < nVerts; i++) {
        printf("Vertex %d: ", i + 1);
        scanf("%f %f", &origVerts[i].x, &origVerts[i].y);
    }

    printf("Enter coefficients of the line Ax + By + C = 0:\n");
    printf("A: "); scanf("%f", &A);
    printf("B: "); scanf("%f", &B);
    printf("C: "); scanf("%f", &C);

    reflectPolygonAcrossLine(origVerts, reflVerts, nVerts, A, B, C);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("2D Reflection Across Arbitrary Line");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
