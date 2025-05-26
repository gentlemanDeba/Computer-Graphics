#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

#define MAX_VERTICES 100

typedef struct
{
    float x, y;
} Point;

Point polygon[MAX_VERTICES];
int numVertices = 0;

Point lineStart = {50, 50};
Point lineEnd = {425, 425};

void drawPolygon()
{
    glColor3f(0.0, 0.0, 1.0); // Blue polygon
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numVertices; i++)
    {
        glVertex2f(polygon[i].x, polygon[i].y);
    }
    glEnd();
}

void drawLine(Point p1, Point p2, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_LINES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();
}

Point subtract(Point a, Point b)
{
    Point result = {a.x - b.x, a.y - b.y};
    return result;
}

float dotProduct(Point a, Point b)
{
    return a.x * b.x + a.y * b.y;
}

Point normal(Point a, Point b)
{
    Point edge = subtract(b, a);
    Point n = {-edge.y, edge.x}; // Perpendicular to edge
    return n;
}

void cyrusBeckClip()
{
    Point d = subtract(lineEnd, lineStart);
    float tE = 0.0, tL = 1.0;

    for (int i = 0; i < numVertices; i++)
    {
        Point a = polygon[i];
        Point b = polygon[(i + 1) % numVertices];
        Point n = normal(a, b);
        Point w = subtract(lineStart, a);
        float DdotN = dotProduct(d, n);
        float WdotN = dotProduct(w, n);

        if (DdotN == 0)
        {
            if (WdotN < 0)
            {
                // Line is outside and parallel to edge
                return;
            }
            // Line is parallel and inside; no effect
            continue;
        }

        float t = -WdotN / DdotN;
        if (DdotN > 0)
        {
            if (t > 1.0)
                return;
            if (t > tE)
                tE = t;
        }
        else
        {
            if (t < 0.0)
                return;
            if (t < tL)
                tL = t;
        }
    }

    if (tE > tL)
        return;

    Point clippedStart = {lineStart.x + d.x * tE, lineStart.y + d.y * tE};
    Point clippedEnd = {lineStart.x + d.x * tL, lineStart.y + d.y * tL};

    drawLine(clippedStart, clippedEnd, 1.0, 0.0, 0.0); // Red clipped line
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawPolygon();
    drawLine(lineStart, lineEnd, 0.0, 1.0, 0.0); // Green original line
    cyrusBeckClip();
    glFlush();
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glColor3f(0.0, 0.0, 0.0);         // Black drawing color
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv)
{
    // Define a convex polygon (e.g., square)
    polygon[0] = (Point){100, 100};
    polygon[1] = (Point){400, 100};
    polygon[2] = (Point){400, 400};
    polygon[3] = (Point){100, 400};
    numVertices = 4;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Cyrus-Beck Line Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
