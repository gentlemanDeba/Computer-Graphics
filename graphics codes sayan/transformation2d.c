#include <GL/glut.h>
#include <math.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define NVERTS 4

typedef struct Point {
	float x, y;
} Point;

typedef float Matrix3x3[3][3];
Matrix3x3 transform;
const double pi = 3.14159265359;

/**
 * Creates a unit matrix. Like this -
 * [1 0 0]
 * [0 1 0]
 * [0 0 1]
 */
void identityMat3x3(Matrix3x3 mat3x3)
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			mat3x3[i][j] = (i == j);
		}
	}
}

/**
 * Multiply matrices.
 */
void matrixMultiply(Matrix3x3 m1, Matrix3x3 m2)
{
	Matrix3x3 mulMat;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			mulMat[i][j] = m1[i][0] * m2[0][j] +
				       m1[i][1] * m2[1][j] +
				       m1[i][2] * m2[2][j];
		}
	}

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			m2[i][j] = mulMat[i][j];
		}
	}
}

/**
 * @param tx Translate distance over x
 * @param ty Translate distance over y
 */
void translate2d(float tx, float ty)
{
	Matrix3x3 transMat;
	identityMat3x3(transMat);

	transMat[0][2] = tx;
	transMat[1][2] = ty;

	matrixMultiply(transMat, transform);
}

/**
 * @param pvtPt A point that is center of rotation.
 * @param theta Angle to rotate.
 */
void rotation2d(Point pvtPt, double theta)
{
	Matrix3x3 rotateMat;
	identityMat3x3(rotateMat);

	rotateMat[0][0] = cos(theta);
	rotateMat[0][1] = -sin(theta);
	rotateMat[0][2] = pvtPt.x * (1 - cos(theta)) + pvtPt.y * sin(theta);

	rotateMat[1][0] = sin(theta);
	rotateMat[1][1] = cos(theta);
	rotateMat[1][2] = pvtPt.y * (1 - cos(theta)) - pvtPt.x * sin(theta);

	matrixMultiply(rotateMat, transform);
}

/**
 * @param sx Scaling factor over x
 * @param sy Scaling factor over y
 * @param fixedPt A fixed point. All points scale relative to it. This point is unchanged after scale.
 */
void scale2d(float sx, float sy, Point fixedPt)
{
	Matrix3x3 scaleMat;
	identityMat3x3(scaleMat);

	scaleMat[0][0] = sx;
	scaleMat[0][2] = fixedPt.x * (1 - sx);
	scaleMat[1][1] = sy;
	scaleMat[1][2] = fixedPt.y * (1 - sy);

	matrixMultiply(scaleMat, transform);
}

/**
 * Apply transformations to the vertices.
 */
void applyTransformation(int nVerts, Point *verts, Point *transformedVerts)
{
	for (int i = 0; i < nVerts; i++) {
		transformedVerts[i].x = verts[i].x * transform[0][0] +
					verts[i].y * transform[0][1] +
					transform[0][2];
		transformedVerts[i].y = verts[i].x * transform[1][0] +
					verts[i].y * transform[1][1] +
					transform[1][2];
	}
}

/**
 * Draws X and Y axis.
 */
void drawAxes()
{
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex2i(-(int)(WIN_WIDTH / 2), 0);
	glVertex2i((int)(WIN_WIDTH / 2), 0);
	glVertex2i(0, -(int)(WIN_HEIGHT / 2));
	glVertex2i(0, (int)(WIN_HEIGHT / 2));
	glEnd();
}

/**
 * Draws a polygon.
 * @param nVerts number of vertices in the polygon
 * @param verts vertex points
 */
void drawPolygon(int nVerts, Point *verts)
{
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < nVerts; i++) {
		glVertex2f(verts[i].x, verts[i].y);
	}
	glEnd();
}

void displayFunc()
{
	int nVerts = NVERTS;
	float tx = 30.0, ty = 10.0;
	float sx = 1.5, sy = 1.5;
	double theta = (3 * pi) / 4;

	Point fixedPt = { 35.0, 35.0 };
	Point pvtPt = { 35.0, 35.0 };

	Point verts[NVERTS] = {
		{ 20.0, 20.0 }, { 20.0, 50.0 }, { 50.0, 50.0 }, { 50.0, 20.0 }
	};

	Point transformedVerts[NVERTS];

	identityMat3x3(transform);

	glClearColor(0.118, 0.118, 0.18, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	drawPolygon(nVerts, verts);

	scale2d(sx, sy, fixedPt);
	rotation2d(pvtPt, theta);
	translate2d(tx, ty);

	applyTransformation(nVerts, verts, transformedVerts);
	drawPolygon(nVerts, transformedVerts);

	drawAxes();
	glFlush();
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-WIN_WIDTH / 2, WIN_WIDTH / 2, -WIN_HEIGHT / 2,
		   WIN_HEIGHT / 2);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutCreateWindow("Two dimensional transformation");

	init();
	glutDisplayFunc(displayFunc);
	glutMainLoop();
}
