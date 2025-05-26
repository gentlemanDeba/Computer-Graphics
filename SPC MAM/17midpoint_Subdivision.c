#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

#define WIN_WIDTH 700
#define WIN_HEIGHT 700
#define TOLERANCE 1.0

typedef struct Point {
    float x, y;
} Point;

Point p1, p2;  // Line endpoints

// Clipping rectangle boundaries
const float xmin = 100, ymin = 100;
const float xmax = 400, ymax = 400;

int inside(Point p) {
    return (p.x >= xmin && p.x <= xmax && p.y >= ymin && p.y <= ymax);
}

void drawLine(Point a, Point b) {
    glBegin(GL_LINES);
    glVertex2f(a.x, a.y);
    glVertex2f(b.x, b.y);
    glEnd();
}

void clipLine(Point a, Point b) {
    if (inside(a) && inside(b)) {
        drawLine(a, b);
        return;
    }

    if (fabs(a.x - b.x) < TOLERANCE && fabs(a.y - b.y) < TOLERANCE) {
        return;
    }

    Point mid;
    mid.x = (a.x + b.x) / 2;
    mid.y = (a.y + b.y) / 2;

    clipLine(a, mid);
    clipLine(mid, b);
}

void drawClippingWindow() {
    glColor3f(0.0, 0.0, 1.0);  // Blue clipping rectangle
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();
}

void drawAxes() {
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_LINES);
    glVertex2f(-WIN_WIDTH / 2, 0);
    glVertex2f(WIN_WIDTH / 2, 0);
    glVertex2f(0, -WIN_HEIGHT / 2);
    glVertex2f(0, WIN_HEIGHT / 2);
    glEnd();
}

void displayFunc() {
    glClearColor(0.95f, 0.95f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();
    drawClippingWindow();

    glColor3f(1.0f, 0.0f, 0.0f);  // Red: original line
    drawLine(p1, p2);

    glColor3f(0.0f, 0.7f, 0.2f);  // Green: clipped part
    clipLine(p1, p2);

    glFlush();
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIN_WIDTH, 0, WIN_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    printf("Enter coordinates of the line:\n");
    printf("Point 1 (x y): ");
    scanf("%f %f", &p1.x, &p1.y);
    printf("Point 2 (x y): ");
    scanf("%f %f", &p2.x, &p2.y);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("Midpoint Subdivision Line Clipping");

    init();
    glutDisplayFunc(displayFunc);
    glutMainLoop();

    return 0;
}
