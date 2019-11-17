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

void bresenhamAlgorithm(Point A, Point B);
void bresLine1(Point A, Point B); // 0 < m < 1
void bresLine2(Point A, Point B); // m > 1
void bresLine3(Point A, Point B); // -1 < m < 0
void bresLine4(Point A, Point B); // m < -1

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutCreateWindow("Drawing Line by implemented Bresenham algorithm");
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
    Point points[] = {
        {0, 400}, {200, 200}
    };
	glClear(GL_COLOR_BUFFER_BIT);
    int N = sizeof(points)/sizeof(points[0]);
	
	for(int i = 0;i < N;i += 2) {
		if (points[i].x <= points[i+1].x) {
			bresenhamAlgorithm(points[i], points[i+1]);
		} else {
			// Swap two points
			bresenhamAlgorithm(points[i+1], points[i]);
		}
	}
	
	// Draw x-axis & y-axis
	
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for(int y = -MIDDLE_Y;y <= MIDDLE_Y;y++) {
		glVertex2i(MIDDLE_X, MIDDLE_Y + y);
		glVertex2i(MIDDLE_Y + y, MIDDLE_X);
	}
	glEnd();
	
	
	glFlush();
}

void bresenhamAlgorithm(Point A, Point B) {
	std::cout<<"\nBresenham\n";
	float m = (float)(B.y - A.y)/(B.x - A.x); //m la he so goc
	std::cout<<"\nSlope = "<<m;
	if ((m >= 0) && (m <= 1)) {
		std::cout<<" => [0,1]";
		bresLine1(A, B);
	} else if (m > 1) {
		std::cout<<" => (1,infinite)";
		bresLine2(A, B);
	} else if (m >= -1) {
		std::cout<<" => [-1,0]";
		bresLine3(A, B);
	} else if (m < -1) {
		std::cout<<" => (infinite,-1)";
		bresLine4(A, B);
	}
}

// 0 < m < 1 -> RED
void bresLine1(Point A, Point B) {
	int deltaX = B.x - A.x;
	int deltaY = B.y - A.y;
	float b = A.y - A.x * deltaY/deltaX;
	float d = deltaX*(2*A.y - 2*b + 1) - 2*deltaY*(A.x + 1);
	int x = A.x, y = A.y; 
	glColor3f(1, 0, 0);
	glBegin(GL_POINTS);
	for(;x <= B.x;x++) {
		glVertex2i(MIDDLE_X + x, MIDDLE_Y + y);
		if (d >= 0) {
			d = d - 2 * deltaY;
		} else {
			d = d + 2 * deltaX - 2 * deltaY;
			y++;
		}
	}
	glEnd();
	//glFlush();
}

// m > 1 -> GREEN
void bresLine2(Point A, Point B) {
	int deltaX = B.x - A.x;
	int deltaY = B.y - A.y;
	float b = A.y - A.x * deltaY/deltaX;
	float d = deltaX*(2*A.y - 2*b + 1) - 2*deltaY*(A.x + 1);
	int x = A.x, y = A.y; 
	//glPointSize(1);
	//glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	glColor3f(0, 1, 0);
	for(;x <= B.x;) {
		glVertex2i(MIDDLE_X + x, MIDDLE_Y + y);
		if (d >= 0) {
			d = d + 2*deltaX - 2*deltaY;
			x++;
		} else {
			d = d + 2*deltaX;
		}
		y++;
	}
	glEnd();
	//glFlush();
}

// -1 < m < 0 -> BLUE
void bresLine3(Point A, Point B) {
	int deltaX = B.x - A.x;
	int deltaY = B.y - A.y;
	float b = A.y - A.x * deltaY/deltaX;
	float d = deltaX*(2*A.y - 2*b + 1) - 2*deltaY*(A.x + 1);
	int x = A.x, y = A.y; 
	//glPointSize(1);
	//glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	glColor3f(0, 0, 1);
	for(;x <= B.x;x++) {
		glVertex2i(MIDDLE_X + x, MIDDLE_Y + y);
		if (d >= 0) {
			d = d + 2*deltaX - 2*deltaY;
			y--;
		} else {
			d = d - 2*deltaY;
		}
		
	}
	glEnd();
	//glFlush();
}

// m < -1
void bresLine4(Point A, Point B) {
	int deltaX = B.x - A.x;
	int deltaY = B.y - A.y;
	float b = A.y - A.x * deltaY/deltaX;
	float d = deltaX*(2*A.y - 2*b + 1) - 2*deltaY*(A.x + 1);
	int x = A.x, y = A.y; 
	//glPointSize(1);
	//glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	for(;x <= B.x;) {
		glVertex2i(MIDDLE_X + x, MIDDLE_Y + y);
		if (d >= 0) {
			d = d - 2*deltaX;
		} else {
			d = d - 2*deltaX - 2*deltaY;
			x++;
		}
		y--;
		
	}
	glEnd();
	//glFlush();
}
