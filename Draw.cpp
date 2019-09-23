#include <iostream>
#include <GL/glut.h>
#include <math.h>

#include "subFile.cpp"

#define MAX_WIDTH 1000
#define MAX_HEIGHT 1000
#define MIDDLE_X MAX_WIDTH / 2
#define MIDDLE_Y MAX_HEIGHT / 2

// Prototype
void initGL();

void drawLine();

void midPointAlgorithm(int x1, int y1, int x2, int y2);
void midLine1(int x1, int y1, int x2, int y2); // 0 < m < 1
void midLine2(int x1, int y1, int x2, int y2); // m > 1
void midLine3(int x1, int y1, int x2, int y2); // -1 < m < 0
void midLine4(int x1, int y1, int x2, int y2); // m < -1

void bresenhamAlgorithm(int x1, int y1, int x2, int y2);
void bresLine1(int x1, int y1, int x2, int y2); // 0 < m < 1
void bresLine2(int x1, int y1, int x2, int y2); // m > 1
void bresLine3(int x1, int y1, int x2, int y2); // -1 < m < 0
void bresLine4(int x1, int y1, int x2, int y2); // m < -1

void drawCircle();
void midPointCircle(int a, int b, int radius);
void bresenhamCircle(int a, int b, int radius);

void drawEllipse();
void midPointEllipse(int a, int b, int r1, int r2);
void bresenhamEllipse(int a, int b, int r1, int r2);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutCreateWindow("Drawing Line, Circle & Ellipse Program");
	glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
	glutInitWindowPosition(0, 0);
	//glutDisplayFunc(drawLine);
	// glutDisplayFunc(drawCircle);
	glutDisplayFunc(drawEllipse);
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

void drawEllipse() {
	int a = -70;
	int b = 50;
	int r1 = 120;
	int r2 = 250;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
		// bresenhamEllipse(a, b, r1, r2);
		midPointEllipse(a, b, r1, r2);
	glEnd();
	glFlush();
}

void midPointEllipse(int a, int b, int r1, int r2) {
	/*
	*
	*/
	float init = r2*r2 - r1*r1*r2 + r1*r1/4.0;
	float p = init;
	
	float xQ = (float) r1 * r1 / sqrt(r1 * r1 + r2 * r2);
	float yQ = (float) r2 * r2 / sqrt(r1 * r1 + r2 * r2);
	
	int translationX = a + MIDDLE_X;
	int translationY = b + MIDDLE_Y;
	
	glVertex2i(translationX, translationY);
	
	// Region 1
	int x = 0, y = r2;
	for(;x <= xQ;x++) {
		glVertex2i(translationX + x, translationY + y);
		glVertex2i(translationX - x, translationY + y);
		glVertex2i(translationX + x, translationY - y);
		glVertex2i(translationX - x, translationY - y);
		if (p >= 0) {
			p = p + (2*x + 3)*(r2*r2)-2*(r1*r1)*(y-1);
			y--;
		} else {
			p = p + (2*x + 3)*r2*r2;
		}
	}
	
	// Region 2
	p = init;
	x = r1, y = 0;
	for(;y <= yQ;y++) {
		glVertex2i(translationX + x, translationY + y);
		glVertex2i(translationX - x, translationY + y);
		glVertex2i(translationX + x, translationY - y);
		glVertex2i(translationX - x, translationY - y);
		if (p >= 0) {
			p = p + (2*y + 3)*r1*r1 - 2*r2*r2*(x-1);
			x--;
		} else {
			p = p + r1*r1*(2*y + 3);
		}
	}
	
}

void bresenhamEllipse(int a, int b, int r1, int r2) {
	
	float p = 2.0 * r2 * r2 / (r1 * r1) - 2 * r2 + 1;
	// Q
	float xQ = (float) r1 * r1 / sqrt(r1 * r1 + r2 * r2);
	float yQ = (float) r2 * r2 / sqrt(r1 * r1 + r2 * r2);
	
	int translationX = a + MIDDLE_X;
	int translationY = b + MIDDLE_Y;
	
	glVertex2i(translationX, translationY);
	
	// Region 1
	int x = 0, y = r2;
	
	for(;x <= xQ;x++) {
		std::cout<<"("<<x<<", "<<y<<") : "<<p<<"\n";
		glVertex2i(translationX + x, translationY + y);
		glVertex2i(translationX - x, translationY + y);
		glVertex2i(translationX + x, translationY - y);
		glVertex2i(translationX - x, translationY - y);
		if (p >= 0) {
			p = p + 2 * r2 * r2 * (2 * x + 3) / (r1 * r1) + 4 * (1 - y);
			y--;
		} else {
			p = p + 2 * r2 * r2 * (2 * x + 3) / (r1 * r1);
		}
	}
	
	// Region 2
	p = 2 * r1 * r1 / (r2 * r2) - 2 * r1 + 1;
	x = r1;
	for(y = 0;y <= yQ;y++) {
		glVertex2i(translationX + x, translationY + y);
		glVertex2i(translationX - x, translationY + y);
		glVertex2i(translationX + x, translationY - y);
		glVertex2i(translationX - x, translationY - y);
		
		if (p >= 0) {
			p = p + 2 * r1 * r1 * (2 * y + 3) / (r2 * r2) + 4 * (1 - x);
			x--;
		} else {
			p = p + 2 * r1 * r1 * (2 * y + 3) / (r2 * r2);
		}
	}
}

void drawCircle() {
	// Center point is I(x, y) and radius
	// Using Bresenham algorithm
	// Parameter: I(a, b) and the radius's length
	int a = -50;
	int b = 50;
	int radius = 300;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0, 0);
	glBegin(GL_POINTS);
		// midPointCircle(a, b, radius);
		bresenhamCircle(a, b, radius);
	glEnd();
	glFlush();
}

void midPointCircle(int a, int b, int radius) {
	// d0 = 5/4 - radius;
	float d = 5 / 4 - radius;
	
	int x = 0;
	int y = radius;
	float x2 = radius * sqrt(2) / 2;
	
	int translationX, translationY;
	if (a * b >= 0) {
		// Both of a and b are the same sign
		translationX = a + MIDDLE_X;
	} else {
		translationX = MIDDLE_X - a;
	}
	translationY = b + MIDDLE_Y;
	
	// Draw center point of the circle
	glVertex2i(translationX, translationY);
	
	for(;x <= (int) x2;x++) {
		// std::cout<<std::endl<<"("<<x<<", "<<y<<") => d = "<<d<<std::endl;
		// Draw first point
		glVertex2i(translationX + x, b + MIDDLE_Y + y);
		
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

void bresenhamCircle(int a, int b, int radius) {
	int x = 0;
	int y = radius;
	
	// d = f(P) + f(S)
	// f(P) = f(x + 1, y)
	// f(S) = f(x + 1, y - 1)
	int d = 3 - 2 * radius;
	float x2 = radius * sqrt(2) / 2;
	
	int translationX, translationY;
	if (a * b >= 0) {
		// Both of a and b are the same sign
		translationX = a + MIDDLE_X;
	} else {
		translationX = MIDDLE_X - a;
	}
	translationY = b + MIDDLE_Y;
	
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

void drawLine() {
	/*
	* AB: A(x1, y1) and B(x2, y2)
	* x1, y1, x2, y2 are integer
	 */
	int points[] = {
		0, 0, 100, 1000,
		0, 0, 400, 10,
		0, 400, 100, 0,
		0, 100, 400, 0
	};
	glClear(GL_COLOR_BUFFER_BIT);
	// midPointAlgorithm(-500, 0, 500, 0);
	// 0 500 0 -500
	
	for(int i = 0;i < sizeof(points) / sizeof(points[0]);i += 4) {
		if (points[i] <= points[i+2]) {
			bresenhamAlgorithm(points[i], points[i+1], points[i+2], points[i+3]);
			// midPointAlgorithm(points[i], points[i+1], points[i+2], points[i+3]);	
		} else {
			// Swap two points
			bresenhamAlgorithm(points[i+2], points[i+3], points[i], points[i+1]);
			//midPointAlgorithm(points[i+2], points[i+3], points[i], points[i+1]);
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

void bresenhamAlgorithm(int x1, int y1, int x2, int y2) {
	std::cout<<"\nBresenham\n";
	float m = (float)(y2 - y1)	/ (x2 - x1); //m la he so goc
	std::cout<<"\nSlope = "<<m;
	if ((m >= 0) && (m <= 1)) {
		std::cout<<" => [0,1]";
		bresLine1(x1, y1, x2, y2);
	} else if (m > 1) {
		std::cout<<" => (1,infinite)";
		bresLine2(x1, y1, x2, y2);
	} else if (m >= -1) {
		std::cout<<" => [-1,0]";
		bresLine3(x1, y1, x2, y2);
	} else if (m < -1) {
		std::cout<<" => (infinite,-1)";
		bresLine4(x1, y1, x2, y2);
	}
}

// 0 < m < 1
void bresLine1(int x1, int y1, int x2, int y2) {
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	float b = y1 - x1 * (y2 - y1) / (x2 - x1);
	float d = 2 * y1 * deltaX + deltaX - 2 * x1 * deltaY - 2 * deltaY - 2 * b * deltaX;
	int x = x1, y = y1;
	//glPointSize(1);
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glBegin(GL_POINTS);
	for(;x < x2;x++) {
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

// m > 1
void bresLine2(int x1, int y1, int x2, int y2) {
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	float b = y1 - x1 * (y2 - y1) / (x2 - x1);
	float d = 2 * y1 * deltaX + deltaX - 2 * x1 * deltaY - 2 * deltaY - 2 * b * deltaX;
	int x = x1, y = y1;
	//glPointSize(1);
	//glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	glColor3f(0, 1, 0);
	for(;x < x2;) {
		glVertex2i(MIDDLE_X + x, MIDDLE_Y + y);
		if (d >= 0) {
			d = d + 2 * deltaX - 2 * deltaY;
			x++;
		} else {
			d = d + 2 * deltaX;
		}
		y++;
	}
	glEnd();
	//glFlush();
}

// -1 < m < 0
void bresLine3(int x1, int y1, int x2, int y2) {
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	float b = y1 - x1 * (y2 - y1) / (x2 - x1);
	float d = 2 * y1 * deltaX + deltaX - 2 * x1 * deltaY - 2 * deltaY - 2 * b * deltaX;
	int x = x1, y = y1;
	//glPointSize(1);
	//glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	glColor3f(0, 0, 1);
	for(;x < x2;x++) {
		glVertex2i(MIDDLE_X + x, MIDDLE_Y + y);
		if (d >= 0) {
			d = d + 2 * deltaX - 2 * deltaY;
			y--;
		} else {
			d = d - 2 * deltaY;
		}
		
	}
	glEnd();
	//glFlush();
}

// m < -1
void bresLine4(int x1, int y1, int x2, int y2) {
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	float b = y1 - x1 * (y2 - y1) / (x2 - x1);
	float d = 2 * y1 * deltaX + deltaX - 2 * x1 * deltaY - 2 * deltaY - 2 * b * deltaX;
	int x = x1, y = y1;
	//glPointSize(1);
	//glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	for(;x < x2;) {
		glVertex2i(MIDDLE_X + x, MIDDLE_Y + y);
		if (d >= 0) {
			d = d - 2 * deltaX;
		} else {
			d = d - 2 * deltaX - 2 * deltaY;
			x++;
		}
		y--;
		
	}
	glEnd();
	//glFlush();
}

void midPointAlgorithm(int x1, int y1, int x2, int y2) {
	std::cout<<"\nMid Point";
	float m = (float) (y2 - y1) / (x2 - x1);
	std::cout<<"Slope = "<<m<<std::endl;
	if ((m >= 0) && (m <= 1)) {
		std::cout<<" => [0,1]";
		midLine1(x1, y1, x2, y2);
	} else if (m > 1) {
		std::cout<<" => (1,infinite)";
		midLine2(x1, y1, x2, y2);
	} else if (m >= -1) {
		std::cout<<" => [-1,0]";
		midLine3(x1, y1, x2, y2);
	} else if (m < -1) {
		std::cout<<" => (infinite,-1)";
		midLine4(x1, y1, x2, y2);
	}
}

// 0 < m < 1
void midLine1(int x1, int y1, int x2, int y2) {
	int x = x1, y = y1;
	int a = y2 - y1, b = x1 - x2;
	float d = a + b / 2.0;
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	for(x = x1;x <= x2;x++) {
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
void midLine2(int x1, int y1, int x2, int y2) {
	int x = x1, y = y1;
	int a = y2 - y1, b = x1 - x2;
	float d = a / 2.0 + b;
	glBegin(GL_POINTS);
	glColor3f(0, 1, 0);
	for(x = x1;x <= x2;) {
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
void midLine3(int x1, int y1, int x2, int y2) {
	int x = x1, y = y1;
	int a = y2 - y1, b = x1 - x2;
	float d = a - b / 2.0;
	glBegin(GL_POINTS);
	glColor3f(0, 0, 1);
	for(;x <= x2;x++) {
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
void midLine4(int x1, int y1, int x2, int y2) {
	int x = x1, y = y1;
	int a = y2 - y1, b = x1 - x2;
	float d = a / 2.0 - b;
	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	for(;x <= x2;) {
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
