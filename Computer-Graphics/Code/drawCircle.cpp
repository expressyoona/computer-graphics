#include <iostream>
#include <GL/glut.h>
#include <math.h>

#define MAX_WIDTH 1000
#define MAX_HEIGHT 1000
#define MIDDLE_X MAX_WIDTH / 2
#define MIDDLE_Y MAX_HEIGHT / 2

struct Point {
    int x;
    int y;
};

// Prototype
void initGL();

void drawCircle();
void midPointCircle(Point I, int radius);
void bresenhamCircle(Point I, int radius);

void draw8points(int x, int y);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutCreateWindow("Drawing Circle");
	glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutDisplayFunc(drawCircle);
	initGL();
	// std::cout<<"OpenGL version: "<<glGetString(GL_VERSION);
	glutMainLoop();
	return 0;
}

// Definition

void initGL() {
	glClearColor( 1.0, 1.0, 1.0, 0.0 );	//get white background color
  	glColor3f( 0.0f, 0.0f, 0.0f );	//set drawing color
	glPointSize( 2.0 );	//a dot is 4x4
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();	//replace current matrix with identity matrix
	gluOrtho2D( 0.0, MAX_WIDTH, 0.0, MAX_HEIGHT);
}

void drawCircle() {
	// Center point is I(x, y) and radius
	// Using Bresenham algorithm
	// Parameter: I(a, b) and the radius's length
	Point I = {0, 0};
	int radius = 300;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0, 0);
	glBegin(GL_POINTS);
		// midPointCircle(a, b, radius);
		bresenhamCircle(I, radius);
	glEnd();
	glFlush();
}

void midPointCircle(Point I, int radius) {
	// d0 = 5/4 - radius;
	float d = 5 / 4 - radius;
	
	int x = 0;
	int y = radius;
	float x2 = radius * sqrt(2) / 2;
	
	int translationX, translationY;
	if (I.x*I.y >= 0) {
		// Both of a and b are the same sign
		translationX = I.x + MIDDLE_X;
	} else {
		translationX = MIDDLE_X - I.x;
	}
	translationY = I.y + MIDDLE_Y;
	
	// Draw center point of the circle
	glVertex2i(translationX, translationY);
	
	for(;x <= (int) x2;x++) {
		// std::cout<<std::endl<<"("<<x<<", "<<y<<") => d = "<<d<<std::endl;
		// Draw first point
		glVertex2i(translationX + x, translationY + y);
		
		// Draw other 7 points
		glVertex2i(translationX - x, translationY + y);
		glVertex2i(translationX + x, translationY - y);
		glVertex2i(translationX - x, translationY - y);
		
		glVertex2i(translationY + y, translationX + x);
		glVertex2i(translationY - y, translationX + x);
		glVertex2i(translationY + y, translationX - x);
		glVertex2i(translationY - y, translationX - x);
		
		if (d >= 0) {
			// (x + 1, y - 1)
			d = d + 2 * x - 2 * y + 5;
			y--;
		} else {
			// (x + 1, y)
			d = d + 2 * x + 3;
		}		
		
	}
}

void bresenhamCircle(Point I, int radius) {
	int x = 0;
	int y = radius;
	
	// d = f(P) + f(S)
	// f(P) = f(x + 1, y)
	// f(S) = f(x + 1, y - 1)
	int d = 3 - 2 * radius;
	float x2 = radius * sqrt(2) / 2;
	
	int translationX, translationY;
	if (I.x*I.y >= 0) {
		// Both of a and b are the same sign
		translationX = I.x + MIDDLE_X;
	} else {
		translationX = MIDDLE_X - I.x;
	}
	translationY = I.y + MIDDLE_Y;
	
	glVertex2i(translationX, translationY);
	
	for(;x <= x2;x++) {
		std::cout<<x<<", "<<y<<" - d = "<<d<<"\n";
		glVertex2i(translationX + x, translationY + y);
		
		// Draw other 7 lines
		glVertex2i(translationX - x, translationY + y);
		glVertex2i(translationX + x, translationY - y);
		glVertex2i(translationX - x, translationY - y);
		
		glVertex2i(translationY + y, translationX + x);
		glVertex2i(translationY - y, translationX + x);
		glVertex2i(translationY + y, translationX - x);
		glVertex2i(translationY - y, translationX - x);
		
		if (d >= 0) {
			y--;	
			d = d +  4 * (x - y) + 10;
		} else {
			d = d + 4 * x  + 6;
		}
	}
}

void draw8points(int x, int y) {
    glVertex2i(x, y);
    glVertex2i(-x, y);
    glVertex2i(x, -y);
    glVertex2i(-x, -y);
    glVertex2i(y, x);
    glVertex2i(-y, x);
    glVertex2i(y, -x);
    glVertex2i(-y, -x);
}