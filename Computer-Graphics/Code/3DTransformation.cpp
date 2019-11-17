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
	int x;
	int y;
	int z;
};

void Init();

void DrawCoordinate();
void RendenScene();
void ReShape(int width, int height);

void translation3d(Point3D P[], int tx, int ty, int tz);
void scale3d(Point3D P[], int sx, int sy, int sz);

void SetMaterialColor(GLfloat ambient[4], GLfloat diff_use[4]);
void SetMaterialColor(const int &type);

GLuint MakeCube(Point3D P[]); //Hinh lap phuong

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

	Point3D A = {-1, -1, 1};
	Point3D B = {1, -1, 1};
	Point3D C = {1, 1, 1};
	Point3D D = {-1, 1, 1};
	Point3D E = {-1, -1, -1};
	Point3D F = {-1, 1, -1};
	Point3D G = {1, 1, -1};
	Point3D H = {1, -1, -1};
	Point3D P[] = {A, B, C, D, E, F, G, H};

	gluLookAt(10.0, 10.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glPushMatrix();
	DrawCoordinate();
	SetMaterialColor(K_MAT_RED);
	glCallList(MakeCube(P));
	glPopMatrix();

	glPushMatrix();
	translation3d(P, 2, 2, -2);
	SetMaterialColor(K_MAT_YELLOW);
	glCallList(MakeCube(P));
	glPopMatrix();

	glFlush();
}

int main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Computer Graphics 3D");

	Init();
	glutReshapeFunc(ReShape);
	glutDisplayFunc(RendenScene);

	glutMainLoop();
}

void translation3d(Point3D P[], int tx, int ty, int tz)
{
	for (int i = 0; i < 8; i++)
	{
		P[i].x = P[i].x + tx;
		P[i].y = P[i].y + ty;
		P[i].z = P[i].z + tz;
	}
}

void scale3d(Point3D P[], int sx, int sy, int sz)
{
	for (int i = 0; i < 8; i++)
	{
		P[i].x = P[i].x * sx;
		P[i].y = P[i].y * sy;
		P[i].z = P[i].z * sz;
	}
}

void reflection(Point3D Point[]) {
	
}

void SetMaterialColor(GLfloat ambient[4], GLfloat diff_use[4])
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);
}

void SetMaterialColor(const int &type)
{
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

GLuint MakeCube(Point3D P[])
{
	GLuint dp_list;
	dp_list = glGenLists(1);
	glNewList(dp_list, GL_COMPILE);
	glBegin(GL_QUADS);
	// Front Face
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(P[0].x, P[0].y, P[0].z);
	glVertex3f(P[1].x, P[1].y, P[1].z);
	glVertex3f(P[2].x, P[2].y, P[2].z);
	glVertex3f(P[3].x, P[3].y, P[3].z);
	// Back Face
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(P[4].x, P[4].y, P[4].z);
	glVertex3f(P[5].x, P[5].y, P[5].z);
	glVertex3f(P[6].x, P[6].y, P[6].z);
	glVertex3f(P[7].x, P[7].y, P[7].z);
	// Top Face
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(P[5].x, P[5].y, P[5].z);
	glVertex3f(P[3].x, P[3].y, P[3].z);
	glVertex3f(P[2].x, P[2].y, P[2].z);
	glVertex3f(P[6].x, P[6].y, P[6].z);
	// Bottom Face
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(P[0].x, P[0].y, P[0].z);
	glVertex3f(P[1].x, P[1].y, P[1].z);
	glVertex3f(P[7].x, P[7].y, P[7].z);
	glVertex3f(P[4].x, P[4].y, P[4].z);
	// Right face
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(P[1].x, P[1].y, P[1].z);
	glVertex3f(P[2].x, P[2].y, P[2].z);
	glVertex3f(P[6].x, P[6].y, P[6].z);
	glVertex3f(P[7].x, P[7].y, P[7].z);
	// Left Face
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(P[0].x, P[0].y, P[0].z);
	glVertex3f(P[3].x, P[3].y, P[3].z);
	glVertex3f(P[5].x, P[5].y, P[5].z);
	glVertex3f(P[4].x, P[4].y, P[4].z);

	glEnd();
	glEndList();
	return dp_list;
}
