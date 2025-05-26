#include <GL/glut.h>
#include <stdio.h>

const int INSIDE = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;

float x_min, y_min, x_max, y_max; // Clipping window
float x1, y1, x2, y2;             // Line coordinates


int computeCode(float x, float y)
{
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

void cohenSutherlandClip(float x1, float y1, float x2, float y2)
{
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    int accept = 0;

    while (1)
    {
        if ((code1 == 0) && (code2 == 0))
        {
            accept = 1;
            break;
        }
        else if (code1 & code2)
        {
            break;
        }
        else
        {
            int codeOut;
            float x, y;

            codeOut = code1 ? code1 : code2;

            if (codeOut & TOP)
            {
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            }
            else if (codeOut & BOTTOM)
            {
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            }
            else if (codeOut & RIGHT)
            {
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            }
            else if (codeOut & LEFT)
            {
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

            if (codeOut == code1)
            {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            }
            else
            {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    if (accept)
    {
        glColor3f(0.0, 1.0, 0.0); // Green for clipped line
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clipping window
    glColor3f(1.0, 0.0, 0.0); // Red
    glBegin(GL_LINE_LOOP);
    glVertex2f(x_min, y_min);
    glVertex2f(x_max, y_min);
    glVertex2f(x_max, y_max);
    glVertex2f(x_min, y_max);
    glEnd();

    // Draw original line
    glColor3f(0.0, 0.0, 1.0); // Blue
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();

    cohenSutherlandClip(x1, y1, x2, y2);

    glFlush();
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 700, 0, 700);
}

// Main function
int main(int argc, char **argv)
{
     printf("Enter clipping window (x_min y_min x_max y_max): ");
    scanf("%f %f %f %f", &x_min, &y_min, &x_max, &y_max);

    printf("Enter coordinates of the line (x1 y1 x2 y2): ");
    scanf("%f %f %f %f", &x1, &y1, &x2, &y2);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cohen-Sutherland Line Clipping");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
