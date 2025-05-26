#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265
#define WIN_WIDTH 600
#define WIN_HEIGHT 600

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw coordinate axes in black
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
        // X-axis
        glVertex2f(-1.0f, 0.0f);
        glVertex2f(1.0f, 0.0f);
        // Y-axis
        glVertex2f(0.0f, -1.0f);
        glVertex2f(0.0f, 1.0f);
    glEnd();

    // Draw the circle in red
    glColor3f(1.0, 0.0, 0.0);

    float radius = 0.5f;
    int num_segments = 100;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * PI * (float)i / (float)num_segments;
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Keep square coordinate system to match window
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);  // Square window
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Circle with Coordinate Axes - Parametric Equations");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
