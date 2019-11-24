#include <gl/glut.h>
#include <math.h>
#include <iostream>
#include <time.h>

const GLfloat tam_x = 40.0f;
const GLfloat tam_y = 40.0f;


// Độ dài các kim giây, phút, giờ
const GLint sy = 30;
const GLint my = 25;
const GLint hy = 20;

int hour;
int minute;
int second;

void drawCircle(GLfloat xc, GLfloat yc, GLfloat ratio) {
    const GLfloat PI_2 = 3.14169f/180.0f;
    GLint i;
    glPointSize(5.0);
    glBegin(GL_POINTS);
    // Đồng hồ 360 chia thành 12 nút -> Mỗi nút cách nhau 30 độ
    for (i = 0; i <= 360; i += 30) {
        float a = i*PI_2;
        glVertex2f(0.9*(xc + sin(a)*ratio), 0.9*(yc + cos(a)*ratio));
    }
    glEnd();
}

void paint(void) { 
    // std::cout<<hour<<":"<<minute<<":"<<second<<std::endl;
	glClear(GL_COLOR_BUFFER_BIT);

    // Tô 12 nút
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(0, 0, tam_x);

    // Cứ mỗi giây, kim giây quay thêm 6 độ
    float secondAngle = second*6;
    
    // Quay 1 góc theo trục z
    glRotatef(-secondAngle, 0.0f, 0.0f, 1.0f);

    glColor3f(1.0f, 1.0f, 1.0f);

    // Vẽ kim giây
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex2i(0, 0);
    glVertex2i(0, sy);
    glEnd();
    
    glLoadIdentity(); 

    // Kim phút cũng tăng 6 độ
    float minuteAngle = minute*6;

    glRotatef(-minuteAngle, 0.0f, 0.0f, 1.0f);

    // Vẽ kim phút
	glLineWidth(3);
    glBegin(GL_LINES); 
    glVertex2i(0, 0);
    glVertex2i(0, my);
    glEnd();
    
    glLoadIdentity();

    // Góc kim giờ = (giờ + phút/60)*30
	float hourAngle = (hour + minute/60.0)*30;

    glRotatef(-hourAngle, 0.0f, 0.0f, 1.0f);

    // Vẽ kim giờ
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2i(0, 0);
    glVertex2i(0, hy);
    glEnd();
    
    glLoadIdentity();

	glFlush();
}

void reshape(GLsizei width, GLsizei height) {
    glViewport(0, 0, width, height);    
   
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if (width <= height) {
        gluOrtho2D(-tam_x, tam_x, -tam_y*height/width, tam_y*height/width);
    } else
       gluOrtho2D(-tam_x*width/height, tam_x*width/height, -tam_y, tam_y);
       
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void move(int n) {
    time_t agora = time(0);
    struct tm *datahora = localtime(&agora);
     
    hour = datahora->tm_hour;
    minute = datahora->tm_min;
    second = datahora->tm_sec;
     
    glutPostRedisplay();
    glutTimerFunc(1000, move, 0);
}

void init(void) {   
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
    glutInitWindowPosition(1920/2, 1080/2);
	glutCreateWindow("Clock");
	glutDisplayFunc(paint);
	glutReshapeFunc(reshape);
	glutTimerFunc(1000, move, 0);
	init();
	glutMainLoop();
	return 0;
}