#include <GL/glut.h>
#include <stdio.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define NVERTS 4

typedef struct Vector
{
    float x;
    float y;
} Vector;

Vector vecSubtract(Vector v1, Vector v2)
{
    return (Vector){v1.x - v2.x, v1.y - v2.y};
}

float vecDotProduct(Vector v1, Vector v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y);
}

Vector normal(Vector edgeLine)
{
    return (Vector){edgeLine.y, -edgeLine.x};
}

int cyrusBeck(Vector p1, Vector p2, Vector *polygon, int nVerts,
              Vector *clipped1, Vector *clipped2)
{
    Vector D = vecSubtract(p2, p1);
    float tLower = 0.0;
    float tUpper = 1.0;

    for (int i = 0; i < nVerts; i++)
    {
        Vector f = polygon[i];
        Vector fNext = polygon[(i + 1) % nVerts];

        Vector edgeLine = vecSubtract(fNext, f);
        Vector ni = normal(edgeLine);

        Vector wi = vecSubtract(p1, f);

        float Dni = vecDotProduct(D, ni);
        float wini = vecDotProduct(wi, ni);

        if (Dni == 0)
        {
            if (wini < 0)
            {
                return 0;
            }
            else
            {
                continue;
            }
        }

        float t = -(wini / Dni);

        if (Dni > 0)
        {
            if (t > 1)
            {
                return 0;
            }
            else
            {
                if (t > tLower)
                {
                    tLower = t;
                }
            }
        }
        else
        {
            if (t < 0)
            {
                return 0;
            }
            else
            {
                if (t < tUpper)
                {
                    tUpper = t;
                }
            }
        }
    }

    if (tLower > tUpper)
    {
        return 0;
    }

    *clipped1 = (Vector){p1.x + D.x * tLower, p1.y + D.y * tLower};
    *clipped2 = (Vector){p1.x + D.x * tUpper, p1.y + D.y * tUpper};
    return 1;
}

void drawPolygon(Vector *polygon, int nVerts)
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < nVerts; i++)
    {
        glVertex2f(polygon[i].x, polygon[i].y);
    }
    glEnd();
}

void drawLine(Vector p1, Vector p2, float color[])
{
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_LINES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();
}

void drawAxes()
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(-(int)(WIN_WIDTH / 2), 0);
    glVertex2f((int)(WIN_WIDTH / 2), 0);
    glVertex2f(0, -(int)(WIN_HEIGHT / 2));
    glVertex2f(0, (int)(WIN_HEIGHT / 2));
    glEnd();
}

void displayFunc()
{
    int nVerts = NVERTS;
    Vector polygon[NVERTS] = {{20.0, 20.0},
                              {20.0, 200.0},
                              {200.0, 200.0},
                              {200.0, 20.0}};

    Vector p1 = {10.0, 30.0};
    Vector p2 = {240.0, 260.0};

    Vector clipped1, clipped2;
    float red[3] = {1.0, 0.0, 0.0};
    float green[3] = {0.0, 1.0, 0.0};

    glClearColor(0.0, 0.0, 0.0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();
    drawPolygon(polygon, nVerts);
    drawLine(p1, p2, red);

    int clipped = cyrusBeck(p1, p2, polygon, nVerts, &clipped1, &clipped2);

    if (clipped)
    {
        drawLine(clipped1, clipped2, green);
    }
    else
    {
        printf("Segment not clipped.\n");
    }
    glFlush();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-(float)WIN_WIDTH / 2, (float)WIN_WIDTH / 2,
               -(float)WIN_HEIGHT / 2, (float)WIN_HEIGHT / 2);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("2D Line clipping (Cyrus-Beck Algorithm)");

    init();
    glutDisplayFunc(displayFunc);
    glutMainLoop();

    return 0;
}
