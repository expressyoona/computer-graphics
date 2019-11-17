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

void drawLine();

void midPointAlgorithm(Point A, Point B);
void midLine1(Point A, Point B); // 0 < m < 1
void midLine2(Point A, Point B); // m > 1
void midLine3(Point A, Point B); // -1 < m < 0
void midLine4(Point A, Point B); // m < -1

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutCreateWindow("Drawing Line, Circle & Ellipse Program");
	glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutDisplayFunc(drawLine);
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

void drawLine() {
	/*
	* AB: A(x1, y1) and B(x2, y2)
	* x1, y1, x2, y2 are integer
	 */
    Point p[] = {
        {0, 0}, {100, 1000},
        {0, 0}, {400, 10},
        {0, 400}, {100, 0},
        {0, 100}, {400, 0}
    };
	glClear(GL_COLOR_BUFFER_BIT);
    int N = sizeof(p)/sizeof(p[0]);
	
	for(int i = 0;i < N;i += 2) {
		if (p[i].x <= p[i+1].x) {
			// bresenhamAlgorithm(points[i], points[i+1], points[i+2], points[i+3]);
			midPointAlgorithm(p[i], p[i+1]);	
		} else {
			// Swap two points
			// bresenhamAlgorithm(points[i+2], points[i+3], points[i], points[i+1]);
			midPointAlgorithm(p[i+1], p[i]);
		}
	}
	
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(2.0);
	glBegin(GL_POINTS);
	for(int y = -MIDDLE_Y;y <= MIDDLE_Y;y++) {
		glVertex2i(MIDDLE_X, MIDDLE_Y + y);
		glVertex2i(MIDDLE_Y + y, MIDDLE_X);
	}
	glEnd();
	
	glFlush();
}

void midPointAlgorithm(Point A, Point B) {
	std::cout<<"\nMid Point";
	float m = (float) (B.y - A.y) / (B.x - A.x);
	std::cout<<"Slope = "<<m<<std::endl;
	if ((m >= 0) && (m <= 1)) {
		std::cout<<" => [0,1]";
		midLine1(A, B);
	} else if (m > 1) {
		std::cout<<" => (1,infinite)";
		midLine2(A, B);
	} else if (m >= -1) {
		std::cout<<" => [-1,0]";
		midLine3(A, B);
	} else if (m < -1) {
		std::cout<<" => (infinite,-1)";
		midLine4(A, B);
	}
}

// 0 < m < 1
void midLine1(Point A, Point B) {
	int x = A.x, y = A.y;
	int a = B.y - A.y, b = A.x - B.x;
	float d = a + b / 2.0;
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	for(x = A.x;x <= B.x;x++) {
		glVertex2i(MIDDLE_X + x, MIDDLE_Y + y);
		if (d >= 0) {
			d += a + b;
			y++;
		} else {
			d += a;
		}
	}
	glEnd();
}

// m > 1
void midLine2(Point A, Point B) {
	int x = A.x, y = A.y;
	int a = B.y - A.y, b = A.x - B.x;
	float d = a / 2.0 + b;
	glBegin(GL_POINTS);
	glColor3f(0, 1, 0);
	for(x = A.x;x <= B.x;) {
		glVertex2i(MIDDLE_X + x, MIDDLE_Y + y);
		if (d >= 0) {
			d += b;
		} else {
			d += a + b;
			x++;
		}
		y++;
	}
	glEnd();
}

// -1 < m < 0
void midLine3(Point A, Point B) {
	int x = A.x, y = A.y;
	int a = B.y - A.y, b = A.x - B.x;
	float d = a - b / 2.0;
	glBegin(GL_POINTS);
	glColor3f(0, 0, 1);
	for(;x <= B.x;x++) {
		glVertex2i(MIDDLE_X + x, MIDDLE_Y + y);
		if (d < 0) {
			d += a;
		} else {
			d += a - b;
			y--;
		}
	}
	glEnd();
}

// m < -1
void midLine4(Point A, Point B) {
	int x = A.x, y = A.y;
	int a = B.y - A.y, b = A.x - B.x;
	float d = a / 2.0 - b;
	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	for(;x <= B.x;) {
		glVertex2i(MIDDLE_X + x, MIDDLE_Y + y);
		if (d < 0) {
			d = d - b;
		} else {
			d = d + a - b;
			x++;
		}
		y--;
	}
	glEnd();
}
