#include <iostream>
#include <math.h>
#include <gl/glut.h>

#define MAX_HEIGHT 1000
#define MAX_WIDTH 1000
#define MIDDLE_X MAX_WIDTH/2
#define MIDDLE_Y MAX_HEIGHT/2


struct Point2D {
    int x;
    int y;
};

struct Point3D {
    int x;
    int y;
    int z;
};

void init();
void draw();

void drawSephere(float R);

using namespace std;
int main(int argc, char **argv) {
    glutInit(&argc, argv);
	glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
	glutCreateWindow("Draw Sephere");
	glutInitWindowPosition(0, 0);
	glutDisplayFunc(draw);
	init();
	glutMainLoop();
	return 0;
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
	// glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, MAX_WIDTH, 0.0, MAX_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex2i(-MAX_WIDTH, MIDDLE_X);
		glVertex2i(MAX_WIDTH, MIDDLE_X);
		glVertex2i(MIDDLE_Y, MAX_HEIGHT);
		glVertex2i(MIDDLE_Y, -MAX_HEIGHT);
	glEnd();
	glFlush();
}

void draw() {
    float R = 100;
    drawSephere(R);
}

void drawSephere(float R) {
    Point3D A;
    Point2D B;
    double deltaU, deltaV, u, v, PI_2 = M_PI/2;
    deltaU = deltaV = 0.1;
    glBegin(GL_POINTS);
    // glPointSize(2.0);
    for(v = -PI_2;v < PI_2;v += deltaV) {
        for(u = 0;u < 2*M_PI;u += deltaU) {
            A.x = R*cos(u)*cos(v);
            A.y = R*sin(u)*cos(v);
            A.z = R*sin(v);
            // B = projection(mode, P);
            B.x = A.x;
            B.y = A.z;
            glVertex2i(MIDDLE_Y + B.x, MIDDLE_Y + B.y);
        }
    }
    glEnd();
    glFlush();
}