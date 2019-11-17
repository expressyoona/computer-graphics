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

// For rectangle window
int MIN_X=50, MAX_X=100, MIN_Y=100, MAX_Y=400;

// Prototype
void initGL1();

void drawLine();

void midPointAlgorithm(Point A, Point B);
void midLine1(Point A, Point B); // 0 < m < 1
void midLine2(Point A, Point B); // m > 1
void midLine3(Point A, Point B); // -1 < m < 0
void midLine4(Point A, Point B); // m < -1

void bresenhamAlgorithm(Point A, Point B);
void bresLine1(Point A, Point B); // 0 < m < 1
void bresLine2(Point A, Point B); // m > 1
void bresLine3(Point A, Point B); // -1 < m < 0
void bresLine4(Point A, Point B); // m < -1

void customLine(int x1, int x2);
double f(double x);

void drawCircle();
void midPointCircle(Point I, int radius);
void bresenhamCircle(Point I, int radius);

void drawEllipse();
void midPointEllipse(Point I, int r1, int r2);
void bresenhamEllipse(Point I, int r1, int r2);

void clip();
void cohenSutherlandAlgorithm(Point A, Point B);
int code(Point A);

int main2(int argc, char** argv) {
	glutInit(&argc, argv);
	glutCreateWindow("Drawing Line, Circle & Ellipse Program");
	glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
	glutInitWindowPosition(0, 0);
	
	glutDisplayFunc(drawLine);
	// glutDisplayFunc(drawCircle);
	// glutDisplayFunc(drawEllipse);
	// glutDisplayFunc(clip);
	
	initGL1();
	// std::cout<<"OpenGL version: "<<glGetString(GL_VERSION);
	glutMainLoop();
	return 0;
}

// Definition

void clip() {
	Point A = {0, 400};
	Point B = {200, -200};
	glClear(GL_COLOR_BUFFER_BIT);
	cohenSutherlandAlgorithm(A, B);
	
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(2.0);
	
	glBegin(GL_LINE_LOOP);
	glVertex2i(MIDDLE_X + MIN_X, MIDDLE_Y + MIN_Y);
	glVertex2i(MIDDLE_X + MAX_X, MIDDLE_Y + MIN_Y);
	glVertex2i(MIDDLE_X + MAX_X, MIDDLE_Y + MAX_Y);
	glVertex2i(MIDDLE_X + MIN_X, MIDDLE_Y + MAX_Y);
	
	glEnd();
		
	glBegin(GL_POINTS);
	glPointSize(4.0);
	glVertex2i(MIDDLE_X + A.x, MIDDLE_Y + A.y);
	glVertex2i(MIDDLE_X + B.x, MIDDLE_Y + B.y);
	for(int y = -MIDDLE_Y;y <= MIDDLE_Y;y++) {
		glVertex2i(MIDDLE_X, MIDDLE_Y + y);
		glVertex2i(MIDDLE_Y + y, MIDDLE_X);
	}
	glEnd();
	glFlush();
}

int code(Point M) {
	int code = 0;
	// std::cout<<"Code ("<<M.x<<", "<<M.y<<")"<<std::endl;
	if (M.x < MIN_X) {
		// std::cout<<"\t< MIN X"<<std::endl;
		code |= 1;
	}
	if (M.x > MAX_X) {
		// std::cout<<"\t> MAX X"<<std::endl;
		code |= 2;
	}
	if (M.y < MIN_Y) {
		// std::cout<<"\t< MIN Y"<<std::endl;
		code |= 4;
	}
	if (M.y > MAX_Y) {
		// std::cout<<"\t> MAX Y"<<std::endl;
		code |= 8;
	}
	return code;
}

// Cohen-Sutherland
void cohenSutherlandAlgorithm(Point A, Point B) {
	std::cout<<"Before: ("<<A.x<<", "<<A.y<<") - ("<<B.x<<", "<<B.y<<")"<<std::endl;
	bool exit=false, draw=true;
	double m;
	// std::cout<<code(A)<<" ? "<<code(B)<<std::endl;
		
	while(!exit) {
		if ((code(A) | code(B)) == 0) {
			// Both A & B are inside the window
			std::cout<<"AB"<<std::endl;
			exit = true;
		} else {
			std::cout<<"Current: ("<<A.x<<", "<<A.y<<") - ("<<B.x<<", "<<B.y<<")"<<std::endl;
			if ((code(A) & code(B)) != 0) {
				// AB & window = empty
				std::cout<<"Empty";
				exit = true;
				draw = false;
			} else {
				std::cout<<"Need modify => ";
				if (code(A) == 0) {
					// Swap A and B
					Point temp = A;
					A = B;
					B = temp;
				}
				if (A.x == B.x) {
					if (A.y > MAX_Y) {
						A.y = MAX_Y;
					} else {
						A.y = MIN_Y;
					}
				} else {
					m = (double) (B.y - A.y)/(B.x - A.x);
					if (A.x < MIN_X) {
						A.y = A.y + (MIN_X - A.x)*m;
						A.x = MIN_X;
					} else {
						if (A.x > MAX_X) {
							A.y = A.y + (MAX_X - A.x)*m;
							A.x = MAX_X;
						} else {
							if (A.y > MAX_Y) {
								A.x = A.x + (MAX_Y - A.y)/m;
								A.y = MAX_Y;
							}
						}
					}
				}
			}
		}
	}
	std::cout<<"After: ("<<A.x<<", "<<A.y<<") - ("<<B.x<<", "<<B.y<<")"<<std::endl;
	
	if (draw) {
		bresenhamAlgorithm(A, B);
	}
}

void initGL1() {
	glClearColor( 1.0, 1.0, 1.0, 0.0 );	//get white background color
  	glColor3f( 0.0f, 0.0f, 0.0f );	//set drawing color
	glPointSize( 2.0 );	//a dot is 4x4
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();	//replace current matrix with identity matrix
	gluOrtho2D( 0.0, MAX_WIDTH, 0.0, MAX_HEIGHT);
}

void drawEllipse() {
	Point I = {0, 50};
	int r1 = 400;
	int r2 = 250;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
		bresenhamEllipse(I, r1, r2);
		// midPointEllipse(I, r1, r2);
	glEnd();
	glFlush();
}

void midPointEllipse(Point I, int r1, int r2) {
	/*
	*
	*/
	float init = r2*r2 - r1*r1*r2 + r1*r1/4.0;
	float p = init;
	
	float xQ = (float) r1 * r1 / sqrt(r1 * r1 + r2 * r2);
	float yQ = (float) r2 * r2 / sqrt(r1 * r1 + r2 * r2);
	
	int translationX = I.x + MIDDLE_X;
	int translationY = I.y + MIDDLE_Y;
	
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

void bresenhamEllipse(Point I, int r1, int r2) {
	
	float p = 2.0 * r2 * r2 / (r1 * r1) - 2 * r2 + 1;
	// Q
	float xQ = (float) r1 * r1 / sqrt(r1 * r1 + r2 * r2);
	float yQ = (float) r2 * r2 / sqrt(r1 * r1 + r2 * r2);
	
	int translationX = I.x + MIDDLE_X;
	int translationY = I.y + MIDDLE_Y;
	
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
	Point I = {-50, -50};
	int radius = 300;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0, 0);
	glBegin(GL_POINTS);
		midPointCircle(I, radius);
		// bresenhamCircle(I, radius);
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
	if (I.x * I.y >= 0) {
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
	if (I.x * I.y >= 0) {
		// Both of a and b are the same sign
		translationX = I.x + MIDDLE_X;
	} else {
		translationX = MIDDLE_X - I.x;
	}
	translationY = I.y + MIDDLE_Y;
	
	glVertex2i(translationX, translationY);
	
	for(;x <= x2;x++) {
		// std::cout<<x<<", "<<y<<" - d = "<<d<<"\n";
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
	Point points[] = {
		{0, 0}, {100, 1000},
		{0, 0}, {400, 10},
		{0, 400}, {100, 0},
		{0, 100}, {400, 0}
	};
	
	glClear(GL_COLOR_BUFFER_BIT);
	/*
	Point A = {0, 400};
	Point B = {200, -200};
	bresenhamAlgorithm(A, B);
	*/
	customLine(-100, 100);
	/*
	int N = sizeof(points)/sizeof(points[0]);
	for(int i = 0;i < N;i += 2) {
		if (points[i].x <= points[i+1].x) {
			bresenhamAlgorithm(points[i], points[i+1]);
			// midPointAlgorithm(points[i], points[i+1], points[i+2], points[i+3]);	
		} else {
			// Swap two points
			bresenhamAlgorithm(points[i+1], points[i]);
			//midPointAlgorithm(points[i+2], points[i+3], points[i], points[i+1]);
		}
	}
	*/
	/*
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(2.0);
	glBegin(GL_POINTS);
	glVertex2i(MIDDLE_X + A.x, MIDDLE_Y + A.y);
	glVertex2i(MIDDLE_X + B.x, MIDDLE_Y + B.y);
	for(int y = -MIDDLE_Y;y <= MIDDLE_Y;y++) {
		glVertex2i(MIDDLE_X, MIDDLE_Y + y);
		glVertex2i(MIDDLE_Y + y, MIDDLE_X);
	}
	glEnd();
	*/
	
	glFlush();
}

void bresenhamAlgorithm(Point A, Point B) {
	if (A.x > B.x) {
		Point temp = A;
		A = B;
		B = temp;
	}
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

// 0 < m < 1
void bresLine1(Point A, Point B) {
	int deltaX = B.x - A.x;
	int deltaY = B.y - A.y;
	float b = A.y - A.x*deltaY/deltaX;
	// float d = 2*A.y*deltaX + deltaX - 2*A.x*deltaY - 2*deltaY - 2*b* deltaX;
	float d = deltaX*(2*A.y - 2*b + 1) - 2*deltaY*(A.x + 1);
	int x = A.x, y = A.y; 
	glColor3f(1, 0, 0);
	glBegin(GL_POINTS);
	for(;x <= B.x;x++) {
		glVertex2i(MIDDLE_X + x, MIDDLE_Y + y);
		if (d >= 0) {
			d = d - 2*deltaY;
		} else {
			d = d + 2*(deltaX - deltaY);
			y++;
		}
		
	}
	glEnd();
}

// m > 1
void bresLine2(Point A, Point B) {
	int deltaX = B.x - A.x;
	int deltaY = B.y - A.y;
	float b = A.y - A.x*deltaY/deltaX;
	// float d = 2 * y1 * deltaX + deltaX - 2 * x1 * deltaY - 2 * deltaY - 2 * b * deltaX;
	float d = deltaX*(2*A.y - 2*b + 1) - 2*deltaY*(A.x + 1);
	int x = A.x, y = A.y;
	//glPointSize(1);
	//glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	glColor3f(0, 1, 0);
	for(;x <= B.x;) {
		glVertex2i(MIDDLE_X + x, MIDDLE_Y + y);
		if (d >= 0) {
			d = d + 2*(deltaX - deltaY);
			x++;
		} else {
			d = d + 2*deltaX;
		}
		y++;
	}
	glEnd();
}

// -1 < m < 0
void bresLine3(Point A, Point B) {
	int deltaX = B.x - A.x;
	int deltaY = B.y - A.y;
	std::cout<<"delta X="<<deltaX<<" delta Y="<<deltaY<<std::endl;
	float b = (float)A.y - A.x*deltaY*1.0/deltaX;
	std::cout<<"B = "<<b<<std::endl;
	float d = 2 * A.y * deltaX + deltaX - 2 * A.x * deltaY - 2 * deltaY - 2 * b * deltaX;
	// float d = deltaX*(2*A.y - 2*b + 1) - 2*deltaY*(A.x + 1);
	int x = A.x, y = A.y;
	glBegin(GL_POINTS);
	glColor3f(0, 0, 1);
	int tfX, tfY;
	for(;x <= B.x;x++) {
		// std::cout<<x<<", "<<y<<" -> "<<d<<std::endl;
		
		glVertex2i(MIDDLE_X + x, MIDDLE_Y + y);
		// glVertex2i(tfX, tfY);
		std::cout<<x<<", "<<y<<" -> "<<d<<std::endl;
		if (d >= 0) {
			d = d + 2*(deltaX - deltaY);
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
	float b = A.y - A.x*deltaY/deltaX;
	// float d = 2 * y1 * deltaX + deltaX - 2 * x1 * deltaY - 2 * deltaY - 2 * b * deltaX;
	float d = deltaX*(2*A.y - 2*b + 1) - 2*deltaY*(A.x + 1);
	int x = A.x, y = A.y;
	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	for(;x <= B.x;) {
		glVertex2i(MIDDLE_X + x, MIDDLE_Y + y);
		if (d >= 0) {
			d = d - 2*deltaX;
		} else {
			d = d - 2*(deltaX + deltaY);
			x++;
		}
		y--;
		
	}
	glEnd();
}

void midPointAlgorithm(Point A, Point B) {
	std::cout<<"\nMid Point";
	float m = (float) (B.y - A.y)/(B.x - A.x);
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
	float d = a - b/2.0;
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
	float d = a/2.0 - b;
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

void customLine(int x1, int x2) {
	int x = x1;
	float deltaX = (x2 - x1)/100;
	do {
		Point A = {x, f(x)};
		Point B = {x + deltaX, f(x + deltaX)};
		midPointAlgorithm(A, B);
		x += deltaX;
	}
	while (x <= x2);
}

// Custom Line y = f(x)
double f(double x) {
	// y = -3x
	return -50*x*x*x + 30*x*x + 20*x - 40;
}
