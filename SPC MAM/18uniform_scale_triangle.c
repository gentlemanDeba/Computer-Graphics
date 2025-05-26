#include <GL/glut.h>
#include <stdio.h>

// Triangle vertex array
float triangle[3][2];
float scaleFactor;

// Function to draw coordinate axes
void drawAxes() {
    glColor3f(1, 0, 0); // Red X-axis
    glBegin(GL_LINES);
        glVertex2f(-300, 0);
        glVertex2f(300, 0);
    glEnd();

    glColor3f(0, 1, 0); // Green Y-axis
    glBegin(GL_LINES);
        glVertex2f(0, -300);
        glVertex2f(0, 300);
    glEnd();
}

// Function to draw triangle
void drawTriangle(float tri[3][2]) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 3; i++) {
        glVertex2f(tri[i][0], tri[i][1]);
    }
    glEnd();
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();

    // Draw original triangle
    glColor3f(0, 0, 1); // Blue
    drawTriangle(triangle);

    // Draw scaled triangle
    glColor3f(1, 0, 1); // Magenta
    float scaled[3][2];
    for (int i = 0; i < 3; i++) {
        scaled[i][0] = triangle[i][0] * scaleFactor;
        scaled[i][1] = triangle[i][1] * scaleFactor;
    }
    drawTriangle(scaled);

    glFlush();
}

// Initialization
void init() {
    glClearColor(1, 1, 1, 1); // White background
    glColor3f(0, 0, 0);       // Drawing color
    glPointSize(2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300, 300, -300, 300);
}

// Main function with user input
int main(int argc, char** argv) {
    printf("Enter the coordinates of the triangle vertices (x y):\n");
    for (int i = 0; i < 3; i++) {
        printf("Vertex %d: ", i + 1);
        scanf("%f %f", &triangle[i][0], &triangle[i][1]);
    }

    printf("Enter the uniform scaling factor: ");
    scanf("%f", &scaleFactor);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Uniform Scaling of 2D Triangle");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
