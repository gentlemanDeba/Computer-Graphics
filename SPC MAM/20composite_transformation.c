#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M_PI 3.14159265358979323846
#define MAX_VERTICES 100

int n; // number of vertices
float polygon[MAX_VERTICES][2];

float tx = 0.0f, ty = 0.0f;
float angle = 0.0f; // in degrees
float sx = 1.0f, sy = 1.0f;

void drawAxes() {
    glLineWidth(1.5f);
    glBegin(GL_LINES);
        // X-axis (Red)
        glColor3f(1, 0, 0);
        glVertex2f(-500, 0);
        glVertex2f(500, 0);

        // Y-axis (Green)
        glColor3f(0, 1, 0);
        glVertex2f(0, -500);
        glVertex2f(0, 500);
    glEnd();
}

void drawPolygon(float shape[MAX_VERTICES][2]) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < n; i++) {
        glVertex2f(shape[i][0], shape[i][1]);
    }
    glEnd();
}

void applyTransformations(float src[MAX_VERTICES][2], float dst[MAX_VERTICES][2], int applyTranslation, int applyRotation, int applyScaling) {
    float rad = angle * M_PI / 180.0;

    for (int i = 0; i < n; i++) {
        float x = src[i][0];
        float y = src[i][1];

        // Step 1: Translate
        if (applyTranslation) {
            x += tx;
            y += ty;
        }

        // Step 2: Rotate
        if (applyRotation) {
            float tempX = x * cos(rad) - y * sin(rad);
            float tempY = x * sin(rad) + y * cos(rad);
            x = tempX;
            y = tempY;
        }

        // Step 3: Scale
        if (applyScaling) {
            x *= sx;
            y *= sy;
        }

        dst[i][0] = x;
        dst[i][1] = y;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    drawAxes();

    float transformed[MAX_VERTICES][2];

    // 1. Original
    glColor3f(0, 0, 0); // Black
    drawPolygon(polygon);

    // 2. Translated
    applyTransformations(polygon, transformed, 1, 0, 0);
    glColor3f(0, 0, 1); // Blue
    drawPolygon(transformed);

    // 3. Translated + Rotated
    applyTransformations(polygon, transformed, 1, 1, 0);
    glColor3f(1, 0.5, 0); // Orange
    drawPolygon(transformed);

    // 4. Translated + Rotated + Scaled
    applyTransformations(polygon, transformed, 1, 1, 1);
    glColor3f(1, 0, 1); // Magenta
    drawPolygon(transformed);

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a': tx -= 10; break;
        case 'd': tx += 10; break;
        case 'w': ty += 10; break;
        case 's': ty -= 10; break;
        case 'r': angle += 5; break;
        case 'R': angle -= 5; break;
        case '+': sx += 0.1f; sy += 0.1f; break;
        case '-': if (sx > 0.1 && sy > 0.1) { sx -= 0.1f; sy -= 0.1f; } break;
        case 27: exit(0); // ESC key
    }
    glutPostRedisplay();
}

void init() {
    glClearColor(1, 1, 1, 1); // White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -500, 500); // Coordinate system
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    printf("Enter number of polygon vertices: ");
    scanf("%d", &n);
    if (n < 3 || n > MAX_VERTICES) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("Enter %d vertex coordinates (x y):\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%f %f", &polygon[i][0], &polygon[i][1]);
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Composite Transformations on Polygon");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
