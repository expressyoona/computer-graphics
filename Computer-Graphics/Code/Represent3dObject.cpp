#include <iostream>
#include <gl\glut.h>
#include <math.h>

#define P_PI 3.14159265359 
#define K_MAT_RED 0
#define K_MAT_GREEN 1
#define K_MAT_BLUE 2
#define K_MAT_YELLOW 3
#define K_MAT_PINK 4

struct Point3D {
    int x;
    int y;
    int z;
};

struct EdgeType {
	int  beginP;
	int endP;
};

struct WireFrame {
	int numVertex, numEdge;
	Point3D vertex[100];
	EdgeType edge[100];
};

struct FaceType {
	int nFace;
	Point3D indexFace[100];
};

struct FaceModel {
	int numVertex, numFace;
	Point3D vertex[100];
	FaceType face[100];
};

void Init();

void DrawCoordinate();
void RendenScene();
void ReShape(int width, int height);

void translation3d(Point3D P[], int tx, int ty, int tz);
void scale3d(Point3D P[], int sx, int sy, int sz);
void reflection(Point3D P[]);
void reflectionOx(Point3D P[]);
void reflectionOy(Point3D P[]);
void reflectionOz(Point3D P[]);
void reflectionOxy(Point3D P[]);
void reflectionOyz(Point3D P[]);
void reflectionOzx(Point3D P[]);
void reflectionAnyPoint(Point3D P[], Point3D A);
void rotateOx(Point3D P[], int d);
void rotateOy(Point3D P[], int d);
void rotateOz(Point3D P[], int d);

void SetMaterialColor(GLfloat ambient[4], GLfloat diff_use[4]);
void SetMaterialColor(const int& type);

GLuint MakeCube(Point3D P[]); //Hinh lap phuong
GLuint MakeWFModel(int numEdge, Point3D vertex[], EdgeType edge[]);
GLuint PolygonMeshModel(int numFace, FaceType face[]);

// Projection
Point3D projection(Point3D P, int mode);


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
  	float ratio = (float)width/(float)height;
  	gluPerspective(45.0, ratio, 1, 100.0);
  	glMatrixMode(GL_MODELVIEW);
}
 
 
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
  	
  	gluLookAt(15.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
 
 	/*Point3D A = {1, 1, -1};
 	Point3D B = {3, 1, -1};
 	Point3D C = {3, 3, -1};
 	Point3D D = {1, 3, -1};
 	Point3D E = {1, 1, -3};
 	Point3D F = {1, 3, -3};
 	Point3D G = {3, 3, -3};
 	Point3D H = {3, 1, -3};
 	Point3D P[] = {A, B, C, D, E, F, G, H};
 	Point3D I = {1, 2, 2};
 
  	glPushMatrix();
	DrawCoordinate();
	SetMaterialColor(K_MAT_RED);
	glCallList(MakeCube(P));
	glPopMatrix();
	
	glPushMatrix();
	rotateOz(P, 90);
	SetMaterialColor(K_MAT_GREEN);
	glCallList(MakeCube(P));
	glPopMatrix();*/
	
	Point3D A = {1, 1, -3};
	Point3D B = {-1, 1, -3};
	Point3D C = {-1, -1, -3};
	Point3D D = {1, -1, -3};

	Point3D E = {1, 1, 0};
	Point3D F = {-1, 1, 0};
	Point3D G = {-1, -1, 0};
	Point3D H = {1, -1, 3};

	Point3D I = {1, -1, 2};
	Point3D K = {-1, -1, 2};
	Point3D L = {1, -1, 3};
	Point3D M = {-1, -1, 3};
	
	EdgeType AE = {1, 5};
	EdgeType BF = {2, 6};
	EdgeType CM = {3, 12};
	EdgeType DL = {4 ,11};
	EdgeType EF = {5, 6};
	EdgeType FG = {6, 7};
	EdgeType GH = {7, 8};
	EdgeType HE = {8, 5};
	EdgeType IK = {9, 10};
	EdgeType LM = {11, 12};

	Point3D vertex[] = {A, B, C, D, E, F, G, H, I, K, L, M};
	EdgeType edge[] = {AE, BF, CM, DL, EF, FG, GH, HE, IK, LM};

	int vertexNum = sizeof(vertex)/sizeof(vertex[0]);
	int edgeNum = sizeof(edge)/sizeof(edge[0]);

	WireFrame chair = {vertexNum, edgeNum, {A, B, C, D, E, F, G, H, I, K, L, M}, {AE, BF, CM, DL, EF, FG, GH, HE, IK, LM}};
	/*
	WireFrame chairProjection;
	chairProjection.numEdge = edgeNum;
	chairProjection.numVertex = vertexNum;
	*/
	Point3D newVertex[vertexNum];

	for(int i = 0;i < vertexNum;i++) {
		// chairProjection.vertex[i] = projection(chair.vertex[i], 1);
		newVertex[i] = projection(chair.vertex[i], 1);
	}
	/*
	for(int i = 0;i < chair.numEdge;i++) {
		chairProjection.edge[i] = chair.edge[i];
	}
	*/
	
	// EdgeType edge[] = {AE, BF, CM, DL, EF, FG, GH, HE, IK, LM};
	
	std::cout<<"Vertexs after projection: "<<std::endl;
	for(int i = 0;i < vertexNum;i++) {
		std::cout<<newVertex[i].x<<" "<<newVertex[i].y<<" "<<newVertex[i].z<<std::endl;
	}
	std::cout<<"---------------------------\n";
	
	glPushMatrix();
	DrawCoordinate();
	SetMaterialColor(K_MAT_GREEN);
	
	// glCallList(MakeWFModel(10, vertex, edge));
	
	
	glBegin(GL_LINES);
	// glVertex3i(1, 1, 0);
	// glVertex3i(-1, 1, 0);
	
	for(int i = 0;i < edgeNum;i++) {
		Point3D A, B;
		A = newVertex[edge[i].beginP];
		B = newVertex[edge[i].endP];
		// std::cout<<A.x<<" "<<A.y<<" -> "<<B.x<<" "<<B.y<<std::endl;
		glVertex3i(A.x, A.y, A.z);
		glVertex3i(B.x, B.y, B.z);
	}
	
	glEnd();
	
	// glCallList(MakeWFModel(10, newVertex, edge));
	
	glPopMatrix();
	

	/*
	Point3D A = {1, 1, 3};
	Point3D B = {2, 0, 0};
	Point3D C = {3, 3, 0};
	Point3D D = {0, 2, 0};
	Point3D vertex[] = {A, B, C, D};
	
	FaceType BCD = {3, {B, C, D}};
	FaceType ABC = {3, {A, B, C}};
	FaceType ABD = {3, {A, B, D}};
	FaceType ACD = {3, {A, C, D}};
	FaceType face[] = {BCD, ABC, ABD, ACD};
	
	glPushMatrix();
	DrawCoordinate();
	SetMaterialColor(K_MAT_GREEN);
	glCallList(PolygonMeshModel(4, face));
	glPopMatrix();
	*/
  	glFlush();
} 
 
int main()
{
  	glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB);
  	glutInitWindowSize(500, 500);
  	glutInitWindowPosition(100, 100);
  	glutCreateWindow("Computer Graphics 3D");
 
  	Init();
  	glutReshapeFunc(ReShape);
  	glutDisplayFunc(RendenScene);
 
  	glutMainLoop();
 
}

void translation3d(Point3D P[], int tx, int ty, int tz) {
	for(int i=0;i<8;i++) {
		P[i].x = P[i].x + tx;
		P[i].y = P[i].y + ty;
		P[i].z = P[i].z + tz;
	}
}

void scale3d(Point3D P[], int sx, int sy, int sz) {
	for(int i=0;i<8;i++) {
		P[i].x = P[i].x * sx;
		P[i].y = P[i].y * sy;
		P[i].z = P[i].z * sz;
	}
}

void reflection(Point3D P[]) {
	for(int i=0;i<8;i++) {
		P[i].x = -P[i].x;
		P[i].y = -P[i].y;
		P[i].z = -P[i].z;
	}
}

void reflectionOx(Point3D P[]) {
	for(int i=0;i<8;i++) {
		P[i].x = P[i].x;
		P[i].y = -P[i].y;
		P[i].z = -P[i].z;
	}
}

void reflectionOy(Point3D P[]) {
	for(int i=0;i<8;i++) {
		P[i].x = -P[i].x;
		P[i].y = P[i].y;
		P[i].z = -P[i].z;
	}
}

void reflectionOz(Point3D P[]) {
	for(int i=0;i<8;i++) {
		P[i].x = -P[i].x;
		P[i].y = -P[i].y;
		P[i].z = P[i].z;
	}
}

void reflectionOxy(Point3D P[]) {
	for(int i=0;i<8;i++) {
		P[i].x = P[i].x;
		P[i].y = P[i].y;
		P[i].z = -P[i].z;
	}
}

void reflectionOyz(Point3D P[]) {
	for(int i=0;i<8;i++) {
		P[i].x = -P[i].x;
		P[i].y = P[i].y;
		P[i].z = P[i].z;
	}
}

void reflectionOzx(Point3D P[]) {
	for(int i=0;i<8;i++) {
		P[i].x = P[i].x;
		P[i].y = -P[i].y;
		P[i].z = P[i].z;
	}
}

void reflectionAnyPoint(Point3D P[], Point3D A) {
	translation3d(P, -A.x, -A.y, -A.z);
	reflection(P);
	translation3d(P, A.x, A.y, A.z);
}

void rotateOx(Point3D P[], int d) {
	float rad = d * (P_PI/180);
	for(int i=0;i<8;i++) {
		int y = P[i].y, z = P[i].z;
		P[i].y = y * cos(rad) - z * sin(rad);
		P[i].z = y * sin(rad) + z * cos(rad);
	}
}

void rotateOy(Point3D P[], int d) {
	float rad = d * (P_PI/180);
	for(int i=0;i<8;i++) {
		int z = P[i].z, x = P[i].x;
		P[i].z = z * cos(rad) - x * sin(rad);
		P[i].x = z * sin(rad) + x * cos(rad);
	}
}

void rotateOz(Point3D P[], int d) {
	float rad = d * (P_PI/180);
	for(int i=0;i<8;i++) {
		int x = P[i].x, y = P[i].y;
		P[i].x = x * cos(rad) - y * sin(rad);
		P[i].y = x * sin(rad) + y * cos(rad);
	}
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

GLuint MakeCube(Point3D P[]) {
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

GLuint MakeWFModel(int numEdge, Point3D vertex[], EdgeType edge[]) {
	// std::cout<<"Called"<<std::endl;
	GLuint dp_list;
	dp_list = glGenLists(1);
	glNewList(dp_list, GL_COMPILE);
	glBegin(GL_LINES);
	for(int i=0;i<numEdge;i++) {
		glVertex3f(vertex[edge[i].beginP-1].x, vertex[edge[i].beginP-1].y, vertex[edge[i].beginP-1].z);
		// std::cout<<i<<": "<<vertex[edge[i].beginP-1].x<<" "<<vertex[edge[i].beginP-1].y<<" "<<vertex[edge[i].beginP-1].z<<std::endl;
		glVertex3f(vertex[edge[i].endP-1].x, vertex[edge[i].endP-1].y, vertex[edge[i].endP-1].z);
		// std::cout<<i<<": "<<vertex[edge[i].endP-1].x<<" "<<vertex[edge[i].endP-1].y<<" "<<vertex[edge[i].endP-1].z<<std::endl;
	}
	
	glEnd();
	glEndList();
	return dp_list;
}

GLuint PolygonMeshModel(int numFace, FaceType face[]) {
	GLuint dp_list;
	dp_list = glGenLists(1);
	glNewList(dp_list, GL_COMPILE);
	
	for(int i=0;i<numFace;i++) {
		glBegin(GL_LINE_LOOP);
		for(int j=0;j<face[i].nFace;j++) {
			//glPointSize(5.0);
			glVertex3f(face[i].indexFace[j].x, face[i].indexFace[j].y, face[i].indexFace[j].z);
			std::cout<<face[i].indexFace[j].x<<" "<<face[i].indexFace[j].y<<" "<<face[i].indexFace[j].z<<std::endl;
		}
		glEnd();
	}
	
	glEndList();
	return dp_list;
}

Point3D projection(Point3D P, int mode) {
	// mode = 0 => Phoi canh, 1 => Song song
	/*
	* alpha, beta = 
	* R = OO'
	* D = khoảng cách từ 0 đến mặt quan sát
	*/
	Point3D T;
	T.z = 0;
	if (mode == 1) {
		T.x = P.x;
		T.y = P.y;	
	}
	return T;
	/*
	int alpha = 30, beta = 60;
	float R = 1, D = 4;
	int xc = 0, yc = 0;
	Point3D T;
	T.z = 0;
	float x, y, z, ap, bt;
	// convert alpha, beta to radian
	ap = M_PI*alpha/180;
	bt = M_PI*beta/180;

	x = -P.x*sin(ap) + P.y*cos(ap);
	y = -P.x*cos(ap)*cos(bt) - P.y*sin(ap)*cos(bt) - P.z*sin(bt) + R;

	if (mode) {
		z = -P.x*cos(ap)*cos(bt) - P.y*sin(ap)*cos(bt) - P.z*sin(bt) + R;
		if (D > z) {
			// std::cout<<"Zoom In"<<std::endl;
		} else {
			// std::cout<<"Zoom Out"<<std::endl;
		}
		T.x = (int) (x*D/z) + xc;
		T.y = (int) (y*D/z) + yc;
	} else {
		T.x = (int) (x*D) + xc; // + xc?
		T.y = (int) (y*D) + yc;
	}
	return T;
	*/
}