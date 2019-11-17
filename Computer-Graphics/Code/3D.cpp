/*
    -lglut32 -lglu32 -lopengl32 -lwinmm -lgdi32
*/
#include <iostream>
#include <GL/glut.h>

const int MAX_WIDTH = 1000;
const int MAX_HEIGHT = 1000;

void init();
void draw();

using namespace std;
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
    glutCreateWindow("OpenGL 3D");
    glutInitWindowPosition(0, 0);
    glutDisplayFunc(draw);
    init();
    glutMainLoop();
    return 0;
}

void draw() {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.5, 0.0, 0.0);

        
        glVertex3f(0.0, 0.5, 0.0);

        
        glVertex3f(0.0, 0.0, 0.5);
    glEnd();
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glTranslatef(0.0, 0.0, -0.7);
    glRotatef()
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}