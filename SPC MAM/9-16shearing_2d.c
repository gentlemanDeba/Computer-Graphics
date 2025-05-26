#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

typedef struct Point {
    float x, y;
} Point;

int nVerts;
Point *verts = NULL;
Point *shearVerts = NULL;
float shx = 0.0f, shy = 0.0f;
int shearChoice;

void shear(int nVerts, Point verts[], Point shearVerts[], float shx, float shy)
{
    for (int i = 0; i < nVerts; i++) {
        shearVerts[i].x = verts[i].x + shx * verts[i].y;
        shearVerts[i].y = verts[i].y + shy * verts[i].x;
    }
}

void drawPolygon(int nVerts, Point *verts, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < nVerts; i++) {
        glVertex2f(verts[i].x, verts[i].y);
    }
    glEnd();
}

void drawAxes()
{
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_LINES);
    glVertex2i(-WIN_WIDTH / 2, 0);
    glVertex2i(WIN_WIDTH / 2, 0);
    glVertex2i(0, -WIN_HEIGHT / 2);
    glVertex2i(0, WIN_HEIGHT / 2);
    glEnd();
}

void displayFunc()
{
    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();
    drawPolygon(nVerts, verts, 1.0, 0.0, 0.0); // original in red
    drawPolygon(nVerts, shearVerts, 0.0, 1.0, 0.6); // sheared in cyan-green

    glFlush();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-WIN_WIDTH / 2, WIN_WIDTH / 2, -WIN_HEIGHT / 2, WIN_HEIGHT / 2);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    printf("Enter number of vertices: ");
    scanf("%d", &nVerts);

    verts = (Point *)malloc(nVerts * sizeof(Point));
    shearVerts = (Point *)malloc(nVerts * sizeof(Point));

    printf("Enter coordinates of each vertex (x y):\n");
    for (int i = 0; i < nVerts; i++) {
        printf("Vertex %d: ", i + 1);
        scanf("%f %f", &verts[i].x, &verts[i].y);
    }

    printf("\nShearing Options:\n");
    printf("1. Shear in X-direction\n");
    printf("2. Shear in Y-direction\n");
    printf("3. Shear in both X and Y directions\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &shearChoice);

    switch (shearChoice) {
        case 1:
            printf("Enter shear factor shx: ");
            scanf("%f", &shx);
            shy = 0;
            break;
        case 2:
            printf("Enter shear factor shy: ");
            scanf("%f", &shy);
            shx = 0;
            break;
        case 3:
            printf("Enter shear factors shx and shy: ");
            scanf("%f %f", &shx, &shy);
            break;
        default:
            printf("Invalid choice. Exiting.\n");
            exit(1);
    }

    shear(nVerts, verts, shearVerts, shx, shy);

    glutInit(&argc, argv);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("2D Polygon Shearing");

    init();
    glutDisplayFunc(displayFunc);
    glutMainLoop();

    free(verts);
    free(shearVerts);

    return 0;
}
