#include <iostream>
#include <gl\glut.h>
#include <math.h>

#define P_PI 3.14159265359
#define K_MAT_RED 0
#define K_MAT_GREEN 1
#define K_MAT_BLUE 2
#define K_MAT_YELLOW 3
#define K_MAT_PINK 4

struct Point3D
{
	float x;
	float y;
	float z;
};

void Init();

void DrawCoordinate();
void RendenScene();
void ReShape(int width, int height);

long long factorial(int n);
float pow(float a, int n);
float BernStein(float t, int n, int k);
Point3D Puv(Point3D P[][10], float u, float v, int m, int n);
void drawBezierSurface(int m, int n, Point3D P[][10]);

void DrawCoordinate()
{
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 10.0);
	glEnd();

	glEnable(GL_LIGHTING);
}

void ReShape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float ratio = (float)width / (float)height;
	gluPerspective(45.0, ratio, 1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void Init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat light_pos[] = {0.0, 0.0, 1.0, 0.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	GLfloat ambient[] = {1.0, 1.0, 0.0, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);

	GLfloat diff_use[] = {0.5, 0.5, 0.0, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);

	GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

	GLfloat shininess = 50.0f;
	glMateriali(GL_FRONT, GL_SHININESS, shininess);
}

void RendenScene()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// gluLookAt(10.0, 10.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    gluLookAt(10.0, 10.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// glPushMatrix();
	DrawCoordinate();
    /*
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
        glVertex3f(0.7, 0.5, 0.1);
        glVertex3f(0.3, -0.3, 0.8);
        glVertex3f(0.5, 0.1, 0.5);
    */
    // glEnd();

    Point3D P[][10] = {
        {
            {3, 2, 5},
            {4, 4, 5},
			{5, 5, 5}
        },
		{
            {3, 5, 5},
			{4, 5, 5},
            {5, 5, 5}
        }
    };
    int m = 2;
    int n = 3;
    drawBezierSurface(m, n, P);
	// glFlush();
    
}

using namespace std;

int main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Bezier Surface");

	Init();
	glutReshapeFunc(ReShape);
	glutDisplayFunc(RendenScene);

	glutMainLoop();
}

void SetMaterialColor(GLfloat ambient[4], GLfloat diff_use[4])
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);
}

void SetMaterialColor(const int &type) {
	GLfloat ambien[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat diff_use[] = {0.0, 0.0, 0.0, 1.0};
	switch (type)
	{
	case K_MAT_RED:
	{
		ambien[0] = 1.0f;
		diff_use[0] = 1.0f;
	}
	break;
	case K_MAT_GREEN:
	{
		ambien[1] = 1.0f;
		diff_use[1] = 1.0f;
	}
	break;
	case K_MAT_BLUE:
	{
		ambien[2] = 1.0f;
		diff_use[2] = 1.0f;
	}
	break;
	case K_MAT_YELLOW:
	{
		ambien[0] = 1.0f;
		ambien[1] = 1.0f;
		diff_use[0] = 1.0f;
		diff_use[1] = 1.0f;
	}
	break;
	case K_MAT_PINK:
	{
		ambien[0] = 1.0f;
		ambien[2] = 1.0f;
		diff_use[0] = 1.0f;
		diff_use[1] = 1.0f;
	}
	break;
	default:
	{
		ambien[0] = 1.0f;
		ambien[1] = 1.0f;
		ambien[2] = 1.0f;
		diff_use[0] = 1.0f;
		diff_use[1] = 1.0f;
		diff_use[2] = 1.0f;
	}
	break;
	}

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambien);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);
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

Point3D Puv(Point3D P[][10], float u, float v, int m, int n) {
    Point3D pt;
    float B1, B2;
    pt.x = 0;
    pt.y = 0;
    pt.z = 0;
    for(int i = 0;i < m;i++) {
		B1 = BernStein(u, m-1, i);
        for(int j = 0;j < n;j++) {
            B2 = BernStein(v, n-1, j);
            pt.x = pt.x + P[i][j].x*B1*B2;
            pt.y = pt.x + P[i][j].y*B1*B2;
            pt.z = pt.z + P[i][j].z*B1*B2;
        }
    }
    return pt;
}

void drawBezierSurface(int m, int n, Point3D P[][10]) {
    Point3D Pt;
    float delta, u, v, c;
    int i;
    u = v = 0;
    c = 1000;
    delta = 1.0/c;
    glColor3f(1.0, 0.0, 0.0);
	glPointSize(2.0);
    glBegin(GL_LINE_STRIP);
	// glBegin(GL_POINTS);
    glVertex3f(P[0][0].x, P[0][0].y, P[0][0].z);
    // cout<<"First Point: "<<P[0].x<<" "<<P[0].y<<endl;
    for(int i = 0;i <= c;i++) {
        // m-1 n-1
        Pt = Puv(P, u, v, m, n);
        glVertex3f(Pt.x, Pt.y, Pt.z);
        cout<<Pt.x<<" "<<Pt.y<<" "<<Pt.z<<endl;
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
    glVertex3f(P[m-1][n-1].x, P[m-1][n-1].y, P[m-1][n-1].z);
    glEnd();
	glFlush();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    glPointSize(5.0);
    
    for(int i = 0;i < m;i++) {
        for(int j = 0;j < n;j++) {
            glVertex3f(P[i][j].x, P[i][j].y, P[i][j].z);
        }
	}
    glEnd();
    glFlush();
	cout<<"Done!";
}
