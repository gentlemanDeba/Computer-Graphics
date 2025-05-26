#include <GL/glut.h>
#include <math.h>

// Polyline points in Cartesian coordinates (origin at center)
int points[][2] = {
    {-200, -100},
    {-100, 50},
    {0, 100},
    {100, 70},
    {200, 120}
};

int numPoints = sizeof(points) / sizeof(points[0]);

// Plot a single pixel
void plotPoint(int x, int y) {
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
}

// DDA Line Drawing Algorithm
void drawLineDDA(int x1, int y1, int x2, int y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;

    float steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    float xInc = dx / steps;
    float yInc = dy / steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++) {
        plotPoint(round(x), round(y));
        x += xInc;
        y += yInc;
    }
}

// Draw X and Y axes (centered at origin)
void drawAxes() {
    glColor3f(1.0, 0.0, 0.0); // Red X-axis
    drawLineDDA(-300, 0, 300, 0);

    glColor3f(0.0, 1.0, 0.0); // Green Y-axis
    drawLineDDA(0, -300, 0, 300);
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0); // Black for polyline

    // Draw axes
    drawAxes();

    // Draw polyline using DDA
    for (int i = 0; i < numPoints - 1; i++) {
        drawLineDDA(points[i][0], points[i][1], points[i+1][0], points[i+1][1]);
    }

    glFlush();
}

// Initialization
void init() {
    glClearColor(1, 1, 1, 1); // White background
    glColor3f(0, 0, 0);       // Default drawing color
    glPointSize(2.0);         // Size of plotted pixels
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300, 300, -300, 300); // Center origin in the middle
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Polyline with Proper Coordinate Axes");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}