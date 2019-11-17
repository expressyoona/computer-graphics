/*
	-lglut32 -lglu32 -lopengl32 -lwinmm -lgdi32
*/

#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <bits/stdc++.h>

#define MAX_HEIGHT 1000
#define MAX_WIDTH 1000
#define MIDDLE_X MAX_WIDTH/2
#define MIDDLE_Y MAX_HEIGHT/2
#define f(i, a, b) for(int i = a;i < b;i++)

struct Point {
	int x;
	int y;
};

struct Vector {
	int x;
	int y;
};

int matrix[3][3];

void init();

void draw();
void putAPixel(Point X, float* color);
void drawTriangle(Point A, Point B, Point C, float* color);

float toRadian(int degree);

Point transformPoint(Point A, float matrix[][]);

// Base transformations
Point translation(Point A, Vector v);
Point reflectionViaOx(Point A);
Point reflectionViaOy(Point A);
Point reflectionViaOrigin(Point A);
Point scalingAsOrigin(Point A, int Sx, int Sy); // Origin
Point scalingAsOrigin(Point A, float Sx, float Sy);
Point rotationAroundOrigin(Point A, int degree);
Point rotationAroundOrigin(Point A, float radian);

// Advanced transformations
Point scaling(Point A, Point I, int Sx, int Sy);
Point scaling(Point A, Point I, float Sx, float Sy);
Point reflection(Point A, Point I);
Point rotation(Point A, Point I, int degree);
Point reflectionViaSpeicificLine(Point A, int a, int b);

using namespace std;
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
	glutCreateWindow("OpenGL 2D Transformations");
	glutInitWindowPosition(0, 0);
	glutDisplayFunc(draw);
	init();
	glutMainLoop();
	return 0;
}

Point transformPoint(Point A, matrix F[][]) {
	Point B;
	B.x = A.x*F[0][0] + A.y*F[1][0] + F[2][0];
	B.y = A.x*F[0][1] + A.y*F[1][1] + F[2][1];
	return B;
}

float toRadian(int degree) {
	return M_PI*degree/180;
}

void draw() {
	float beforeColor[] = {0.0, 0.0, 0.0};
	float afterColor[] = {1.0, 0.0, 0.0};
	// ABC -> EFG
	Point A = {0, 150};
	Point B = {-100, -150};
	Point C = {-200, 0};
	drawTriangle(A, B, C, beforeColor);
	/*
	Point F = reflectionViaOrigin(A);
	Point G = reflectionViaOrigin(B);
	Point H = reflectionViaOrigin(C);
	*/
	Point I = {-100, 100};
	int Sx = 2, Sy = 2;
	Point F = scaling(A, I, Sx, Sy);
	Point G = scaling(B, I, Sx, Sy);
	Point H = scaling(C, I, Sx, Sy);
	
	/*
	Point F = rotationAroundOrigin(A, 90);
	Point G = rotationAroundOrigin(B, 90);
	Point H = rotationAroundOrigin(C, 90);
	*/
	/*
	Point I = A;
	int degree = 360;
	Point F = rotation(A, I, 360);
	Point G = rotation(B, I, 360);
	Point H = rotation(C, I, 360);
	*/
	// y = x
	/*
	Point F = reflectionViaSpeicificLine(A, 1, 0);
	Point G = reflectionViaSpeicificLine(B, 1, 0);
	Point H = reflectionViaSpeicificLine(C, 1, 0);
	*/
	drawTriangle(F, G, H, afterColor);
	
}	

void init() {
	memset(matrix, 0, sizeof(matrix));

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

Point translation(Point A, Vector v) {
	Point B = {A.x + v.x, A.y + v.y};
	return B;
}

Point reflectionViaOx(Point A) {
	return {A.x, -A.y};
}

Point reflectionViaOy(Point A) {
	return {-A.x, A.y};
}

Point reflectionViaOrigin(Point A) {
	return {-A.x, -A.y};
}

Point scalingAsOrigin(Point A, float Sx, float Sy) {
	return {(int)A.x*Sx, (int)A.y*Sy};
}

Point scalingAsOrigin(Point A, int Sx, int Sy) {
	return {A.x*Sx, A.y*Sy};
}

Point rotationAroundOrigin(Point A, int degree) {
	float rad = toRadian(degree);
	int x = (int)A.x*cos(rad) - A.y*sin(rad);
	int y = (int)A.x*sin(rad) + A.y*cos(rad);
	return {x,y};
}

Point rotationAroundOrigin(Point A, float radian) {
	int x = (int)A.x*cos(radian) - A.y*sin(radian);
	int y = (int)A.x*sin(radian) + A.y*cos(radian);
	return {x,y};
}

// Advanced transformation implmentation
Point scaling(Point A, Point I, int Sx, int Sy) {
	Point B = translation(A, {-I.x, -I.y});
	B = scalingAsOrigin(B, Sx, Sy);
	return translation(B, {I.x, I.y});
}

Point scaling(Point A, Point I, float Sx, float Sy) {
	Point B = translation(A, {-I.x, -I.y});
	B = scalingAsOrigin(B, Sx, Sy);
	return translation(B, {I.x, I.y});
}

Point reflection(Point A, Point I) {
	Point B = translation(A, {-I.x, -I.y});
	B = reflectionViaOrigin(B);
	B = translation(B, {I.x, I.y});
	return B;
}

Point rotation(Point A, Point I, int degree) {
	Point B = translation(A, {-I.x, -I.y});
	B = rotationAroundOrigin(B, degree);
	return translation(B, {I.x, I.y});
}

Point reflectionViaSpeicificLine(Point A, int a, int b) {
	if (a != 0) {
		Point x0 = {0, b};
		Point y0 = {-b/a, 0};
		Point B = translation(A, {-y0.x, -y0.y});
		float rad;
		// atan return radian value!!!
		
		if (a > 0) {
			rad = atan(a);
		} else {
			rad = M_PI - atan(a);
		}
		// out<<"Radian: "<<rad<<endl;
		B = rotationAroundOrigin(B, -rad);
		B = reflectionViaOx(B);
		B = rotationAroundOrigin(B, rad);
		B = translation(B, {y0.x, y0.y});
		cout<<"("<<A.x<<", "<<A.y<<") -> ("<<B.x<<", "<<B.y<<")"<<endl;
		return B;
	}
}

void drawTriangle(Point A, Point B, Point C, float* color) {
	glPointSize(5.0);
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_LINE_LOOP);
		glVertex2i(MIDDLE_X + A.x, MIDDLE_Y + A.y);
		glVertex2i(MIDDLE_X + B.x, MIDDLE_Y + B.y);
		glVertex2i(MIDDLE_X + C.x, MIDDLE_Y + C.y);
	glEnd();
	glFlush();
}

void putAPixel(Point X, float* color) {
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_POINTS);
		glVertex2i(MIDDLE_X + X.x, MIDDLE_Y + X.y);
	glEnd();
	glFlush();
}
