/*
	Windows: -lglut32 -lglu32 -lopengl32 -lwinmm -lgdi32
	Linux: -lGL -lGLU -lglut
*/

#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <bits/stdc++.h>

#define MAX_HEIGHT 1000
#define MAX_WIDTH 1000
#define MIDDLE_X MAX_WIDTH/2
#define MIDDLE_Y MAX_HEIGHT/2
#define f(i, a, b) for(int i = a;i < b;i++)
#define MAX 100
#define MAX_BUFFER_LENGTH 500

struct Point2D {
	int x;
	int y;
};

struct Point3D {
	int x;
	int y;
	int z;
};

struct Vector3D {
	int x;
	int y;
	int z;
};

struct FaceType {
	int numPoint;
	int indexPoint[MAX];
};

struct FaceModel {
	int numVertex, numFace;
	Point3D vertex[MAX];
	FaceType face[MAX];
	float color[3];
};

struct Depth {
	int z[MAX_BUFFER_LENGTH][MAX_BUFFER_LENGTH];
} depthData;

struct Color {
	float red;
	float green;
	float blue;
};

struct Frame {
	Color color[MAX_BUFFER_LENGTH][MAX_BUFFER_LENGTH];
} frameData;

void init();

void draw();

void depthBufferMethod(FaceModel polygons[], int n);

Vector3D vectorCrossProduct(Vector3D A, Vector3D B);

using namespace std;
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
	glutCreateWindow("Depth Buffer Method");
	glutInitWindowPosition(0, 0);
	glutDisplayFunc(draw);
	init();
	glutMainLoop();
	return 0;
}

void draw() {
	// Write your code below
	// Red
	Point3D A = {20, 60, 10};
	Point3D B = {30, 60, 10};
	Point3D C = {30, 0, 200};
	Point3D D = {20, 0, 200};

	FaceModel firstPolygon = {
		4, 1, {A, B, C, D}, {{0, 1}, {1, 2}, {2, 3}, {3, 0}}, {1.0, 0.0, 0.0}
	};

	// Green
	A = {50, 60, 100};
	B = {60, 60, 100};
	C = {60, 0, 10};
	D = {50, 0, 10};
	FaceModel secondPolygon = {
		4, 1, {A, B, C, D}, {{0, 1}, {1, 2}, {2, 3}, {3, 0}}, {0.0, 1.0, 0.0}
	};

	// Blue
	A = {10, 40, 100};
	B = {10, 50, 100};
	C = {70, 40, 50};
	D = {70, 50, 50};
	FaceModel thirdPolygon = {
		4, 1, {A, B, C, D}, {{0, 1}, {1, 2}, {2, 3}, {3, 0}}, {0.0, 0.0, 1.0}
	};

	// Black
	A = {10, 20, 30};
	B = {10, 10, 30};
	C = {70, 10, 90};
	D = {70, 20, 90};
	FaceModel fourthPolygon = {
		4, 1, {A, B, C, D}, {{0, 1}, {1, 2}, {2, 3}, {3, 0}}, {0.0, 0.0, 0.0}
	};

	FaceModel f[] = {firstPolygon, secondPolygon, thirdPolygon, fourthPolygon};
	int n = sizeof(f)/sizeof(f[0]);
	depthBufferMethod(f, n);
}

// Surface equation: Ax + By + Cz + D = 0 hay A(x - x0) + B(y - y0) + C(z - z0) = 0
/*
 *	STEPS BY STEPS
 *	Duyệt từng đa giác(mặt phẳng)
 *	Duyệt từng điểm (x, y) trên hình chiếu của đa giác(thực chất là chỉ xét tung độ, hoành độ tại 1 điểm vì coi như ta chiếu lên Oxy nên z = 0)
 *	Tìm độ sâu Z của (x, y). Để cần được điều này, cần phải có vecto pháp tuyến để viết phương trình đường thẳng.
 * 	So sánh Z với độ sâu z của (x, y) trước đó.
 *	Nếu Z nhỏ hơn z(x, y) thì cập nhật độ sâu z và màu tại (x, y)
 *	Duyệt toàn bộ khung hình chữ nhật chứa các đa giác và tô màu
 */
void depthBufferMethod(FaceModel polygons[], int n) {
	// Data init
	Color background = {1.0, 1.0, 1.0}, currentColor;
	FaceModel currentFaceModel;
	Point3D currentPoint;
	int X_MIN, Y_MIN, X_MAX, Y_MAX;
	int D;
	float Z, zi;

	for(int i = 0;i < MAX_BUFFER_LENGTH;i++) {
		for(int j = 0;j < MAX_BUFFER_LENGTH;j++) {
			depthData.z[i][j] = INT_MAX;
			frameData.color[i][j] = background;
		}
	}
	
	f(k, 0, n) {
		currentFaceModel = polygons[k];
		X_MIN = INT_MAX, Y_MIN = INT_MAX, X_MAX = INT_MIN, Y_MAX = INT_MIN;

		f(i, 0, currentFaceModel.numVertex) {
			currentPoint = currentFaceModel.vertex[i];
			if (X_MIN > currentPoint.x) {
				X_MIN = currentPoint.x;
			}
			if (X_MAX < currentPoint.x) {
				X_MAX = currentPoint.x;
			}
			if (Y_MIN > currentPoint.y) {
				Y_MIN = currentPoint.y;
			}
			if (Y_MAX < currentPoint.y) {
				Y_MAX = currentPoint.y;
			}
		}

		Point3D A = currentFaceModel.vertex[0];
		Point3D B = currentFaceModel.vertex[1];
		Point3D C = currentFaceModel.vertex[2];
		
		Vector3D AB = {B.x - A.x, B.y - A.y, B.z - A.z};
		Vector3D BC = {C.x - B.x, C.y - B.y, C.z - B.z};
		// Calculate normal vector of the surface/plane
		Vector3D n = vectorCrossProduct(AB, BC);

		// Calculate D in the equation. Assume that the plane passes the A point.
		D = -n.x*A.x - n.y*A.y - n.z*A.z;
	
		zi = -1.0*(n.x*X_MIN + n.y*Y_MIN + D)/n.z;

		// Scan line
		f(i, X_MIN, X_MAX + 1) {
			f(j, Y_MIN, Y_MAX + 1) {
				Z = -1.0*(n.x*i + n.y*j + D)/n.z;
				zi = Z;
				// zi = zi - 1.0*n.y/n.z;
				if (zi < depthData.z[i][j]) {
					depthData.z[i][j] = zi;
					float *c = currentFaceModel.color;
					frameData.color[i][j] = {c[0], c[1], c[2]};
				}
			}
			// zi = zi - 1.0*n.x/n.z;
		}
		
	}
	
	f(i, 0, MAX_BUFFER_LENGTH) {
		f(j, 0, MAX_BUFFER_LENGTH) {
			glBegin(GL_POINTS);
			currentColor = frameData.color[i][j];
			glColor3f(currentColor.red, currentColor.green, currentColor.blue);
			glVertex2i(MIDDLE_X + i, MIDDLE_Y + j);
			glEnd();
		}
	}
	glFlush();
	
}

Vector3D vectorCrossProduct(Vector3D A, Vector3D B) {
	Vector3D V;
	V.x = A.y*B.z - A.z*B.y;
	V.y = -(A.x*B.z - A.z*B.x);
	V.z = (A.x*B.y - A.y*B.x);
	return V;
}

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, MAX_WIDTH, 0.0, MAX_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
}
