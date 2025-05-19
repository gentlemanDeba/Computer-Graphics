#include <GL/glut.h>
#include <stdio.h>

GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};

GLubyte indices[] = {
    0, 1,
    1, 2,
    2, 3,
    3, 0
};

// Global shear factor
GLfloat shx = 0.0f;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the axes
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0); // White
    glVertex3f(-1.5, 0.0, 0.0);
    glVertex3f(1.5, 0.0, 0.0);
    glVertex3f(0.0, -1.5, 0.0);
    glVertex3f(0.0, 1.5, 0.0);
    glEnd();

    // Original square
    glPushMatrix();
    glColor3f(0.0, 1.0, 1.0); // Cyan
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawElements(GL_LINES, 8, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();

    // X-direction shearing matrix with user input
    GLfloat shearXMatrix[] = {
        1.0f, shx, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    glPushMatrix();
    glMultMatrixf(shearXMatrix);

    // Sheared square
    glColor3f(1.0, 0.0, 0.0); // Red
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawElements(GL_LINES, 8, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();

    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.5, 1.5, -1.5, 1.5, -1.5, 1.5);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    printf("Enter shear factor for X-direction: ");
    scanf("%f", &shx);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("X-Direction Sheared Square (User Input)");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
