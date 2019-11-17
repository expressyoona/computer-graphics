/*
*	Filling Shape
*/
#include <vector>
#include<bits/stdc++.h>
#include <iostream>
#include <GL/glut.h>

#define MAX_WIDTH 1000
#define MAX_HEIGHT 1000
#define MIDDLE_X MAX_WIDTH / 2
#define MIDDLE_Y MAX_HEIGHT / 2

struct Point {
	int x;
	int y;
};

void init();

void drawShape(Point p[], int N);

void boundaryFill(Point p[]);
void fill_recursive(Point p);

void jordanFill(Point p[], int N);
void scanLineFill(Point p[], int N);
void fill();

using namespace std;
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutCreateWindow("Filling Shape");
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);
	glutDisplayFunc(fill);
	init();
	glutMainLoop();
	return 0;
}

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, MAX_WIDTH, 0.0, MAX_HEIGHT);
}

int count(int x, int y, Point p[], int N) {
	int s = 0;
	for(int i = 0;i < N;i++) {
		int j = (i < N - 1) ? i + 1 : 0;
		int k = (i == 0) ? N - 1 : i - 1;
		int minX = (p[i].x < p[j].x) ? p[i].x : p[j].x;
		int maxX = (p[i].x >= p[j].x) ? p[i].x : p[j].x;
		float yC = (float) (p[j].y - p[i].y)*(x - p[i].x)/(p[j].x - p[i].x) + p[i].y;
		if ((minX < x) && (x < maxX) && (y < yC)) {
			s++;
		}
		minX = (p[j].x < p[k].x) ? p[j].x : p[k].x;
		maxX = (p[j].x >= p[k].x) ? p[j].x : p[k].x;
		if ((x == p[i].x) && (minX < x) && (x < maxX) && (y < p[i].y)) {
			s++;
		}
	}
	return s;
}

void fill() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	Point p[] = {
		{-200, 200},
		{0, 400},
		{200, 0},
		{400, -200},
		{0, -100},
		{-400, -200}
		
	};
	
	Point shape[] = {
		{0, 200},
		{200, -	400},
		{-200, -200}
	};
	
	/*
	Point shape[] = {
		{0, 300},
		{300, 300},
		{300, 0},
		{0, 0}
			
		
	};
	*/
	int N = sizeof(shape)/sizeof(shape[0]);
	// jordanFill(p, N);
	scanLineFill(shape, N);
	
	drawShape(shape, N);
	/*
	float boundaryColor[] = {0, 0, 0};
	float backgroundColor[] = {1, 1, 1};
	
	Point X = {100, 400};
	glPointSize(3.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
		glVertex2i(MIDDLE_X + X.x, MIDDLE_Y + X.y);
	glEnd();
	glFlush();
	
	float color[3];
	glReadPixels(X.x, X.y, 1.0, 1.0, GL_RGB, GL_FLOAT, &color);
	// cout<<r<<", "<<g<<", "<<b<<endl;
	if ((color[0] - boundaryColor[0] < 0.0001) && (color[1] - boundaryColor[1] < 0.0001) && (color[2] - boundaryColor[2] < 0.001)) {
		cout<<"Vien"<<endl;
	} else if ((color[0] == backgroundColor[0]) && (color[1] == backgroundColor[1]) && (color[2] == backgroundColor[2])) {
		cout<<"Nen"<<endl;
	}
	
	/*
	for(int i = 0;i <= 20;i++) {
		for(int j = 250;j <= 400;j++) {
			unsigned char pixel[4];
			glReadPixels(MIDDLE_X + i, MIDDLE_Y + j, 1000, 1000, GL_RGB, GL_UNSIGNED_BYTE, pixel);
			glVertex2i(MIDDLE_X + i, MIDDLE_Y + j);
			
		}
		
	}
	glEnd();
	glFlush();
	*/
	
	/*
	glBegin(GL_POINTS);
		glColor3f(0.0, 255, 0.0);
		boundaryFill(shape);
	glEnd();
	glFlush();
	*/
}

void drawShape(Point p[], int N) {
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	for(int i = 0;i < N;i++) {
		glVertex2i(MIDDLE_X + p[i].x, MIDDLE_Y + p[i].y);
	}
	glEnd();
	glFlush();
}

void boundaryFill(Point p[]) {
	fill_recursive({200, 200});
	cout<<"Done!";
}

void fill_recursive(Point p) {
	cout<<"Checking "<<p.x<<" "<<p.y<<": ";
	glVertex2i(p.x,p.y);
	unsigned char pixel[4];
	glReadPixels(p.x, p.y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
	int r = (int) pixel[0];
	int g = (int) pixel[1];
	int b = (int) pixel[2];
	cout<<r<<", "<<g<<", "<<b<<endl;
	if ((r != 0) && (g != 0) && (b != 0)) {
		cout<<"To "<<p.x<<" "<<p.y<<endl;
		glVertex2i(MIDDLE_X + p.x, MIDDLE_Y + p.y);
		fill_recursive({MIDDLE_X + p.x + 1, MIDDLE_Y + p.y});
		fill_recursive({MIDDLE_X + p.x - 1, MIDDLE_Y + p.y});
		fill_recursive({MIDDLE_X + p.x, MIDDLE_Y + p.y + 1});
		fill_recursive({MIDDLE_X + p.x + 1, MIDDLE_Y + p.y - 1});
	}
}

void jordanFill(Point p[], int N) {
	glPointSize(1.0);
	// Filling shape by blue color
	glColor3f(0.0, 0.0, 1.0);
	int minX = INT_MAX, minY = INT_MAX;
	int maxX = INT_MIN, maxY = INT_MIN;
	
	for(int i = 0;i < N;i++) {
		// std::cout<<"["<<p[i].x<<" "<<p[i].y<<"]"<<std::endl;
		// (x, y) = (points[i], points[i+1])
		if (p[i].x < minX) {
			minX = p[i].x;
		}
		if (p[i].x > maxX) {
			maxX = p[i].x;
		}
		if (p[i].y < minY) {
			minY = p[i].y;
		}
		if (p[i].y > maxY) {
			maxY = p[i].y;
		}
	}
	std::cout<<"x = ["<<minX<<","<<maxX<<"]\n";
	std::cout<<"y = ["<<minY<<","<<maxY<<"]\n";
	glBegin(GL_POINTS);
	for(int x = minX;x <= maxX;x++) {
		for(int y = minY;y <= maxY;y++) {
			int c = count(x, y, p, N);
			if ((c != 0) && (c % 2 != 0)) {
				glVertex2i(MIDDLE_X + x, MIDDLE_Y + y);
			}
		}
	}
	glEnd();
	glFlush();
}

void count2(Point p[], int N, int y0) {
	// j -> i -> k
	std::vector<int> pts;
	int x;
	for(int i = 0;i < N;i++) {
		int j = (i == 0) ? N - 1 : i - 1;
		int k = (i == N - 1) ? 0 : i + 1;
		if (((p[i].y <= y0) && (y0 <= p[k].y)) || ((p[i].y >= y0) && (y0 >= p[k].y))) {
			cout<<"[0] Duong thang"<<"("<<p[i].x<<", "<<p[i].y<<")"<<", ("<<p[k].x<<", "<<p[k].y<<")"<<endl;
			// Tim giao diem P[i]P[k] voi duong thang y = y0: x(?, y0)
			int deltaX = p[k].x - p[i].x, deltaY = p[k].y - p[i].y;
			if (deltaX == 0) {
				cout<<"[0]"<<"Them: "<<p[k].x<<endl;
				pts.push_back(p[k].x);
			} else {
				
				float m = (float) deltaY/deltaX;
				float b = p[i].y - p[i].x*m;
				x = (y0 - b)/m;
				cout<<"Them x = "<<x<<endl;
				// cout<<"Hoanh do: "<<x<<"\n";
				pts.push_back(x);
				
			}
			
		}
		/*
		if ((y0 == p[i].y) && (((p[j].y <= y0) && (y0 >= p[k].y)) || ((p[j].y >= y0) && (y0 <= p[k].y)))) {
			// Them x vao mang
			cout<<"x2"<<endl;
			pts.push_back(x);
		}
		*/
		if (y0 == p[i].y) {
			cout<<"[1] Diem gap: "<<j<<" -> "<<i<<" -> "<<k<<endl;
			int deltaX = p[k].x - p[i].x, deltaY = p[k].y - p[i].y;
			float m = (float) deltaY/deltaX;
			float b = p[i].y - p[i].x*m;
			x = (y0 - b)/m;
			pts.push_back(x);
			cout<<"Them x = "<<x<<endl;
			if ((((p[j].y <= y0) && (y0 >= p[k].y)) || ((p[j].y >= y0) && (y0 <= p[k].y)))) {
				cout<<"x2"<<endl;
				cout<<"--> Them x = "<<x<<endl;
				pts.push_back(x);
			}
		}
	}
	
	sort(pts.begin(), pts.end());
	
	cout<<"Hoanh do giao diem: ";
	for(int i = 0;i < pts.size();i++) {
		cout<<pts[i]<<" ";
	}
	cout<<endl;
	
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	for(int i = 0;i < pts.size();i += 2) {
		glVertex2i(MIDDLE_X + pts[i], MIDDLE_Y + y0);
		glVertex2i(MIDDLE_X + pts[i + 1], MIDDLE_Y + y0);
	}
	glEnd();
}

void scanLineFill(Point p[], int N) {
	glPointSize(1.0);
	// Filling shape by blue color
	glColor3f(0.0, 0.0, 1.0);
	int minX = INT_MAX, minY = INT_MAX;
	int maxX = INT_MIN, maxY = INT_MIN;
	
	for(int i = 0;i < N;i++) {
		// std::cout<<"["<<p[i].x<<" "<<p[i].y<<"]"<<std::endl;
		// (x, y) = (points[i], points[i+1])
		if (p[i].x < minX) {
			minX = p[i].x;
		}
		if (p[i].x > maxX) {
			maxX = p[i].x;
		}
		if (p[i].y < minY) {
			minY = p[i].y;
		}
		if (p[i].y > maxY) {
			maxY = p[i].y;
		}
	}
	bool test = false;
	if (test) {
		
		
		count2(p, N, -400);
	} else {
		for(int i = minY;i <= maxY;i++)	{
			count2(p, N, i);
		}	
	}
	
	
}
