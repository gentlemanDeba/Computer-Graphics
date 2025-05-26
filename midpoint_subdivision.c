#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#undef y1

// Clipping window bounds
int xmin = 100, ymin = 100, xmax = 300, ymax = 300;

// Line endpoints (user input)
int x1, y1, x2, y2;

// Check if a point is inside the clipping rectangle
int isInside(int x, int y)
{
    return (x >= xmin && x <= xmax && y >= ymin && y <= ymax);
}

// Recursive Midpoint Subdivision Clipping
void midpointClip(int x1, int y1, int x2, int y2)
{
    if (isInside(x1, y1) && isInside(x2, y2))
    {
        glBegin(GL_LINES);
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
        glEnd();
        return;
    }

    if ((x1 < xmin && x2 < xmin) || (x1 > xmax && x2 > xmax) ||
        (y1 < ymin && y2 < ymin) || (y1 > ymax && y2 > ymax))
    {
        return;
    }

    // Subdivide
    int mx = (x1 + x2) / 2;
    int my = (y1 + y2) / 2;

    // Stop if very small segment
    if (abs(x1 - x2) < 1 && abs(y1 - y2) < 1)
        return;

    midpointClip(x1, y1, mx, my);
    midpointClip(mx, my, x2, y2);
}

// Display callback
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clipping window
    glColor3f(1.0, 0.0, 0.0); // Red
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin, ymin);
    glVertex2i(xmax, ymin);
    glVertex2i(xmax, ymax);
    glVertex2i(xmin, ymax);
    glEnd();

    // Original line (gray)
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();

    // Clipped line (green)
    glColor3f(0.0, 1.0, 0.0);
    midpointClip(x1, y1, x2, y2);

    glFlush();
}

// OpenGL Initialization
void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glColor3f(0.0, 0.0, 0.0);         // Black drawing color
    gluOrtho2D(0, 500, 0, 500);       // Coordinate system
}

int main(int argc, char **argv)
{
    printf("Enter line coordinates (x1 y1 x2 y2): ");
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Midpoint Subdivision Line Clipping");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
