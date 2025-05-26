#include <GL/glut.h>
#include <stdio.h>

#define INSIDE 0 // 0000
#define LEFT   1 // 0001
#define RIGHT  2 // 0010
#define BOTTOM 4 // 0100
#define TOP    8 // 1000

float x_min, y_min, x_max, y_max; // Clipping window
float x1, y1, x2, y2;             // Line coordinates

int computeCode(float x, float y) {
    int code = INSIDE;

    if (x < x_min)
        code |= LEFT;
    else if (x > x_max)
        code |= RIGHT;
    if (y < y_min)
        code |= BOTTOM;
    else if (y > y_max)
        code |= TOP;

    return code;
}

void drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (int i = 0; text[i]; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clipping window
    glColor3f(0.0, 0.0, 1.0); // Blue
    glBegin(GL_LINE_LOOP);
    glVertex2f(x_min, y_min);
    glVertex2f(x_max, y_min);
    glVertex2f(x_max, y_max);
    glVertex2f(x_min, y_max);
    glEnd();

    // Draw original line in red
    glColor3f(1.0, 0.0, 0.0); // Red
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();

    // Generate and display endpoint codes
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);

    char codeStr1[5], codeStr2[5];
    for (int i = 0; i < 4; i++) {
        codeStr1[3 - i] = (code1 & (1 << i)) ? '1' : '0';
        codeStr2[3 - i] = (code2 & (1 << i)) ? '1' : '0';
    }
    codeStr1[4] = '\0';
    codeStr2[4] = '\0';

    glColor3f(0.0, 0.6, 0.0); // Green
    drawText(x1 + 5, y1 + 5, codeStr1);
    drawText(x2 + 5, y2 + 5, codeStr2);

    glFlush();
}

void init() {
    glClearColor(1, 1, 1, 1); // White background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 600, 0, 600); // Coordinate system
}

int main(int argc, char** argv) {
    printf("Enter clipping window (x_min y_min x_max y_max): ");
    scanf("%f %f %f %f", &x_min, &y_min, &x_max, &y_max);

    printf("Enter line coordinates (x1 y1 x2 y2): ");
    scanf("%f %f %f %f", &x1, &y1, &x2, &y2);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("End Point Code Generation - OpenGL");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
