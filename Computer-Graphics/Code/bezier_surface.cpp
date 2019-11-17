#include <iostream>
#include <gl/glut.h>

#define MAX_HEIGHT 1000
#define MAX_WIDTH 1000
#define MIDDLE_X MAX_WIDTH/2
#define MIDDLE_Y MAX_HEIGHT/2


struct Point {
    int x;
    int y;
};


void init();
void draw();

long long factorial(int n);
float pow(float a, int n);
float BernStein(float t, int n, int k);
Point Puv(Point P[][10], float u, float v, int m, int n);
void drawBezierSurface(int m, int n, Point P[][10]);

using namespace std;
int main(int argc, char **argv) {
    glutInit(&argc, argv);
	glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
	glutCreateWindow("Curve");
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
    
    Point P[10][10] = {
        {
            {100, 100},
            {150, 300},
            {300, 280},
            {400, 100}
        },
        {
            {-300, 100},
            {-350, -120},
            {-300, -180},
            {-240, -200}
        }
        
    };
    
    // Point P[10][10];
    int m = 2;
    int n = 4;
    drawBezierSurface(2, 4, P);
}

long long factorial(int n) {
    long long P = 1;
    for(int i = 1;i <= n;i++) {
        P *= i;
    }
    return P;
}

float pow(float a, int n) {
    float P = 1;
    for(int i = 1;i <= n;i++) {
        P *= a;
    }
    // cout<<a<<"^"<<n<<" = "<<P<<endl;
    return P;
}

float BernStein(float t, int n, int k)  {
    // cout<<"n = "<<n<<" "<<k<<endl;
    float cKn, kq;
    cKn = (float) 1.0*factorial(n)/(factorial(k)*factorial(n - k));
    kq = cKn*pow(1 - t, n - k)*pow(t, k);
    return kq;
}
/*
Point TPt(Point P[], float t, int n) {
    Point Pt;
    float B;
    int k;
    Pt.x = 0;
    Pt.y = 0;
    for(k = 0;k < n;k++) {
        B = BernStein(t, n-1, k);
        // cout<<B<<endl;
        Pt.x = Pt.x + P[k].x*B;
        Pt.y = Pt.y + P[k].y*B;
    }
    return Pt;
}
*/

Point Puv(Point P[10][10], float u, float v, int m, int n) {
    Point pt;
    float B1, B2;
    pt.x = 0;
    pt.y = 0;
    for(int i = 0;i < m;i++) {
        for(int j = 0;j < n;j++) {
            B1 = BernStein(u, m-1, i);
            B2 = BernStein(v, n-1, j);
            pt.x = pt.x + P[i][j].x*B1*B2;
            pt.y = pt.x + P[i][j].y*B1*B2;
        }
    }
    return pt;
}

void drawBezierSurface(int m, int n, Point P[][10]) {
    Point Pt;
    float delta, u, v, c;
    int i;
    u = v = 0;
    c = 1000;
    delta = 1.0/c;
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex2i(MIDDLE_X + P[0][0].x, MIDDLE_Y + P[0][0].y);
    // cout<<"First Point: "<<P[0].x<<" "<<P[0].y<<endl;
    for(int i = 0;i <= c;i++) {
        // m-1 n-1
        Pt = Puv(P, u, v, m, n);
        glVertex2i(MIDDLE_X + Pt.x, MIDDLE_Y + Pt.y);
        cout<<Pt.x<<" "<<Pt.y<<endl;
        u += delta;
        v += delta;
    }
            
    
    /*
    for(int i = 1;i <= c;i++) {
        Pt = TPt(P, t, n);
        //  cout<<Pt.x<<" "<<Pt.y<<endl;
        glVertex2i(MIDDLE_X + Pt.x, MIDDLE_Y + Pt.y);
        t += dt;
    }
    */
    glVertex2i(MIDDLE_X + P[m-1][n-1].x, MIDDLE_Y + P[m-1][n-1].y);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glPointSize(5.0);
    
    for(int i = 0;i < m;i++) {
        for(int j = 0;j < n;j++) {
            glVertex2i(MIDDLE_X + P[i][j].x, MIDDLE_Y + P[i][j].y);
        }
    }
    
    
        
    glEnd();

    glFlush();
}