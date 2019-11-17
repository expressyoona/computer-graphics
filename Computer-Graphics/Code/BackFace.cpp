
/*
	-lGL -lGLU -lglut
*/
#include <iostream>
#include <GL/glut.h>
#include <math.h>

#define P_PI 3.14159265359 
#define K_MAT_RED 0
#define K_MAT_GREEN 1
#define K_MAT_BLUE 2
#define K_MAT_YELLOW 3
#define K_MAT_PINK 4
#define MAX 100

struct Point3D {
    int x;
    int y;
    int z;
};

struct EdgeType {
	int beginP;
	int endP;
};

struct WireFrame {
	int numVertex, numEdge;
	Point3D vertex[MAX];
	EdgeType edge[MAX];
};

struct FaceType {
	int nFace;
	int indexFace[MAX];
};

struct FaceModel {
	int numVertex, numFace;
	Point3D vertex[MAX];
	FaceType face[MAX];
};

struct Vector3D {
	int x;
	int y;
	int z;
};

void Init();

void DrawCoordinate();
void RendenScene();
void ReShape(int width, int height);

void SetMaterialColor(GLfloat ambient[4], GLfloat diff_use[4]);
void SetMaterialColor(const int& type);

GLuint drawFromWireFrame(WireFrame wf);
GLuint drawFromPolygonMesh(FaceModel faceModel, Vector3D eyesVector);

Vector3D vectorCrossProduct(Vector3D A, Vector3D B);
int vectorDotProduct(Vector3D A, Vector3D B);
float vectorLength(Vector3D A);

void DrawCoordinate();
void ReShape(int width, int height);
 
void Init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
 	
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
 
    GLfloat light_pos [] = {0.0, 0.0, 1.0, 0.0};
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
  	// 10 10 15
	Point3D eyes = {-10, 20, 15};
	Vector3D eyesVector = {eyes.x, eyes.y, eyes.z};

  	gluLookAt(eyes.x, eyes.y, eyes.z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	
	int a = 5;

	Point3D A = {0, 0, 0};	// 0
	Point3D B = {0, a, 0};	// 1
	Point3D C = {a, a, 0};	// 2
	Point3D D = {a, 0, 0};	// 3

	Point3D E = {0, 0, a};	// 4
	Point3D F = {0, a, a};	// 5
	Point3D G = {a, a, a};	// 6
	Point3D H = {a, 0, a};	// 7
	/*
	EdgeType AB = {0, 1};
	EdgeType AE = {0, 4};
	EdgeType AD = {0, 3};

	EdgeType BC = {1, 2};
	EdgeType BF = {1, 5};

	EdgeType CD = {2, 3};
	EdgeType CG = {2, 6};

	EdgeType DH = {3, 7};

	EdgeType EF = {4, 5};
	EdgeType EH = {4, 7};

	EdgeType FG = {5, 6};

	EdgeType GH = {6, 7};

	EdgeType edge[100] = {AB, AE, AD, BC, BF, CD, CG, DH, EF, EH, FG, GH};
	int edgeNum = sizeof(edge)/sizeof(edge[0]);
	*/

	Point3D vertex[] = {A, B, C, D, E, F, G, H};
	int vertexNum = sizeof(vertex)/sizeof(vertex[0]);


	FaceType f1 = {4, {0, 4, 5, 1}};
	FaceType f2 = {4, {1, 5, 6, 2}};
	FaceType f3 = {4, {6, 7, 3, 2}};
	FaceType f4 = {4, {7, 4, 0, 3}};
	FaceType f5 = {4, {7, 6, 5, 4}};
	FaceType f6 = {4, {0, 1, 2, 3}};
	int faceNum = 6;	

	// WireFrame cube = {vertexNum, edgeNum, {A, B, C, D, E, F, G, H}, {AB, AE, AD, BC, BF, CD, CG, DH, EF, EH, FG, GH}};
	FaceModel c = {
		vertexNum, faceNum, {A, B, C, D, E, F, G, H}, {f1, f2, f3, f4, f5, f6}
	};

	glPushMatrix();
	DrawCoordinate();
	SetMaterialColor(K_MAT_GREEN);
	
	// glCallList(drawFromWireFrame(cube));
	glCallList(drawFromPolygonMesh(c, eyesVector));
	
	glEnd();
	
	
	glPopMatrix();
  	glFlush();
} 
 
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB);
  	glutInitWindowSize(500, 500);
  	glutInitWindowPosition(100, 100);
  	glutCreateWindow("Computer Graphics 3D");
 
  	Init();
  	glutReshapeFunc(ReShape);
  	glutDisplayFunc(RendenScene);
 
  	glutMainLoop();
 
}

void SetMaterialColor(GLfloat ambient[4], GLfloat diff_use[4]) {
  	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
  	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);
}
 
void SetMaterialColor(const int& type) {
	GLfloat ambien[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat diff_use[] = {0.0, 0.0, 0.0, 1.0};
  	switch(type)
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

GLuint drawFromWireFrame(WireFrame wf) {
	GLuint dp_list;
	dp_list = glGenLists(1);
	glNewList(dp_list, GL_COMPILE);
	glBegin(GL_LINES);
	for(int i = 0;i < wf.numEdge;i++) {
		glVertex3f(wf.vertex[wf.edge[i].beginP].x, wf.vertex[wf.edge[i].beginP].y, wf.vertex[wf.edge[i].beginP].z);
		glVertex3f(wf.vertex[wf.edge[i].endP].x, wf.vertex[wf.edge[i].endP].y, wf.vertex[wf.edge[i].endP].z);
	}
	glEnd();
	glEndList();
	return dp_list;
}

GLuint drawFromPolygonMesh(FaceModel faceModel, Vector3D eyesVector) {
	GLuint dp_list;
	dp_list = glGenLists(1);
	glNewList(dp_list, GL_COMPILE);

	Point3D M;
	for(int i = 0;i < faceModel.numFace;i++) {
		// Back-face checking
		Point3D A = faceModel.vertex[faceModel.face[i].indexFace[0]];
		Point3D B = faceModel.vertex[faceModel.face[i].indexFace[1]];
		Point3D C = faceModel.vertex[faceModel.face[i].indexFace[2]];

		Vector3D AB = {B.x - A.x, B.y - A.y, B.z - A.z};
		Vector3D BC = {C.x - B.x, C.y - B.y, C.z - B.z};
		
		// Calculate normal vector of the plane
		Vector3D n = vectorCrossProduct(AB, BC);
		
		
		int sign = vectorDotProduct(n, eyesVector);
		// std::cout<<"Current plane: "<<i+1<<" ->"<<sign;
		if (sign >= 0) {
			// std::cout<<"(Invisible plane)";
			glBegin(GL_LINE_LOOP);
			int nV = faceModel.face[i].nFace;
			for(int j = 0;j < nV;j++) {
				M = faceModel.vertex[faceModel.face[i].indexFace[j]];
				glVertex3f(M.x, M.y, M.z);
			}
			glEnd();
		}
		std::cout<<std::endl;
	}
	glEndList();
	return dp_list;
}

Vector3D vectorCrossProduct(Vector3D A, Vector3D B) {
	Vector3D V;
	V.x = A.y*B.z - A.z*B.y;
	V.y = -(A.x*B.z - A.z*B.x);
	V.z = (A.x*B.y - A.y*B.x);
	return V;
}

int vectorDotProduct(Vector3D A, Vector3D B) {
	return A.x*B.x + A.y*B.y + A.z*B.z;
}

float vectorLength(Vector3D A) {
	return sqrt(A.x*A.x + A.y*A.y + A.z*A.z);
}

void DrawCoordinate() {
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

void ReShape(int width, int height) {
  	glViewport(0, 0, width, height);
  	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();
  	float ratio = (float)width/(float)height;
  	gluPerspective(45.0, ratio, 1, 100.0);
  	glMatrixMode(GL_MODELVIEW);
}