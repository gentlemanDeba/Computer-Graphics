#include <GL/glut.h>
#include <stdio.h>

// Region codes
const int INSIDE = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;

// Clipping window
float xmin = 100, ymin = 100, xmax = 400, ymax = 400;

// Line coordinates (to be set by user)
float x1, y1, x2, y2;

// Compute region code
int computeCode(float x, float y) {
    int code = INSIDE;

    if (x < xmin) code |= LEFT;
    else if (x > xmax) code |= RIGHT;
    if (y < ymin) code |= BOTTOM;
    else if (y > ymax) code |= TOP;

    return code;
}

// Cohen-Sutherland algorithm
void cohenSutherlandClip(float x1, float y1, float x2, float y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    int accept = 0;

    while (1) {
        if ((code1 == 0) && (code2 == 0)) {
            accept = 1;
            break;
        } else if (code1 & code2) {
            break;
        } else {
            int codeOut;
            float x, y;

            codeOut = code1 ? code1 : code2;

            if (codeOut & TOP) {
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            } else if (codeOut & BOTTOM) {
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            } else if (codeOut & RIGHT) {
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            } else if (codeOut & LEFT) {
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    if (accept) {
        glColor3f(0.0, 1.0, 0.0); // Green for clipped line
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    }
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clipping window
    glColor3f(1.0, 0.0, 0.0); // Red
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    // Draw original line
    glColor3f(0.0, 0.0, 1.0); // Blue
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();

    // Apply clipping
    cohenSutherlandClip(x1, y1, x2, y2);

    glFlush();
}

// Initialization
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glColor3f(0.0, 0.0, 0.0);         // Default color
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

// Main function
int main(int argc, char** argv) {
    printf("Enter coordinates of the line (x1 y1 x2 y2): ");
    scanf("%f %f %f %f", &x1, &y1, &x2, &y2);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cohen-Sutherland Line Clipping (with User Input)");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
