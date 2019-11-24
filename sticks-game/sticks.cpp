/*
 *  Windows: -lglut32 -lglu32 -lopengl32 -lwinmm -lgdi32
 *  Linux: -lGL -lGLU -lglut
 */
#include <GL/glut.h>
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#define f(i, a, b) for(int i = a;i < b;i++)

struct Point2D {
    int x;
    int y;
};

struct Rectangle {
    Point2D vertex;
    int r;
    int l;
    int depth;
    float color[3];
};

bool sortDepth (Rectangle i,Rectangle j) {
	return (i.depth > j.depth);
}

const int MAX_WIDTH = 1000;
const int MAX_HEIGHT = 1000;

const int N = 10;
const int TIME_REFRESH = 3;
const int MAX_STICKS = 20;
const int MAX_DEPTH = 200;
const int MIN_LENGTH = 400;
const int MIN_WIDTH = 20;

bool started = false;
bool click = false;

std::vector<Rectangle> listSticks;

void initGl();
void paint();
void onMouseClick(int button, int state, int x, int y);
void timer(int value);
bool clickedRectangle(Point2D A);
Rectangle generateStick();
int random(int a, int b);
void drawStick(Rectangle r);
void printRectangle(Rectangle r) {
    std::cout<<r.vertex.x<<" -> "<<r.vertex.x+r.r<<", "<<r.vertex.y<<" -> "<<r.vertex.y+r.l<<std::endl;
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
    glutCreateWindow("Sticks Game - Try Hard Mouse Skill");
    glutDisplayFunc(paint);
    glutMouseFunc(onMouseClick);
    initGl();
    glutTimerFunc(TIME_REFRESH*1000, timer, 0);
    glutMainLoop();
    return 0;
}

void onMouseClick(int button, int state, int x, int y) {
    // In ra tọa độ được click, (0, 0) là góc trên bên trái
    // Gốc tọa độ khi thao tác chuột != gốc tọa độ khi vẽ --> Cần trừ 1 khoảng tương ứng
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // std::cout<<x<<", "<<y<<std::endl;
        click = true;
        std::cout<<clickedRectangle({x, MAX_WIDTH - y})<<std::endl;
        glutPostRedisplay();
    }
    
}

void timer(int value) {
    if (!listSticks.empty()) {
        // listSticks.push_back(generateStick());
        glutPostRedisplay();
        glutTimerFunc(TIME_REFRESH*1000, timer, 0);
    }	
}

void initGl() {
    srand(time(NULL));

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, MAX_WIDTH, 0, MAX_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
}

void paint() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (!started) {
        f(i, 0, N) {
            listSticks.push_back(generateStick());
        }
        sort(listSticks.begin(), listSticks.end(), sortDepth);
        started = true;
    } else {
        if(!click) {
			listSticks.push_back(generateStick());
        	sort(listSticks.begin(), listSticks.end(), sortDepth);
		}
		else {
			click = false;
		}
    }
    if (listSticks.size() == MAX_STICKS) {
		std::cout<<"You lose!"<<std::endl;
		exit(0);
	}
    // std::cout<<"------------------------------------"<<std::endl;
    f(i, 0, listSticks.size()) {
        /*
        std::cout<<"["<<i<<"/"<<listSticks.size()<<"]: ";
        printRectangle(listSticks[i]);
        */
        drawStick(listSticks[i]);
    }   
    glFlush();
}

bool clickedRectangle(Point2D A) {
    int minX, maxX, minY, maxY;
    std::cout<<"("<<A.x<<", "<<A.y<<") ";
    for(int i=listSticks.size()-1;i>=0;i--) {
        minX = listSticks[i].vertex.x;
        minY = listSticks[i].vertex.y;
        maxX = minX + listSticks[i].r;
        maxY = minY + listSticks[i].l;
        
        if (minX <= A.x && A.x <= maxX && minY <= A.y && A.y <= maxY) {
            // std::cout<<i<<std::endl;
            Point2D r1, l1, r2, l2;
            bool check = false;
            r1 = {listSticks[i].vertex.x + listSticks[i].r, listSticks[i].vertex.y};
            l1 = {listSticks[i].vertex.x, listSticks[i].vertex.y + listSticks[i].l};
            for(int j=listSticks.size()-1;j>i;j--) {
            	r2 = {listSticks[j].vertex.x + listSticks[j].r, listSticks[j].vertex.y};
            	l2 = {listSticks[j].vertex.x, listSticks[j].vertex.y + listSticks[j].l};
            	if (l1.x > r2.x || l2.x > r1.x) {
            		continue;
            	}
            	if (l1.y < r2.y || l2.y < r1.y) {
            		continue;
            	}
            	return false;
        	}
            listSticks.erase(listSticks.begin()+i);
            if (listSticks.empty()) {
                // Game over
                std::cout<<"You win!"<<std::endl;
                exit(0);
            } /*else {
                f(i, 0, listSticks.size()) {
                    std::cout<<i<<" -> ";
                    printRectangle(listSticks[i]);
                }
            }
            */
            return true;
        }
    }
    // std::cout<<std::endl;
    return false;
}

Rectangle generateStick() {
    int x, y, r, l, transpose, z;
    float red, green, blue;
    
    x = random(0, MAX_WIDTH/2);
    y = random(0, MAX_HEIGHT - MIN_WIDTH);

    red = (random(0, 255))/255.0;
    green = (random(0, 255))/255.0;
    blue = (random(0, 255))/255.0;

    transpose = std::rand() % 2;
    // 0 is landscape, 1 is portrait
    if ((transpose == 0) || (y > MAX_HEIGHT/2)) {
        l = MIN_WIDTH;
        r = random(MIN_LENGTH, MAX_HEIGHT - x);
    } else {
        r = MIN_WIDTH;
        l = random(MIN_LENGTH, MAX_WIDTH - y);
    }
    z = random(0, MAX_DEPTH);
    Rectangle rectangle = {{x, y}, r, l, z, {red, green, blue}};
    return rectangle;
}

int random(int a, int b) {
    int result = (std::rand() % (b - a)) + a;
    // std::cout<<"("<<a<<", "<<b<<") = "<<result<<std::endl;
    return result;
}

void drawStick(Rectangle r) {
    glBegin(GL_QUADS);
    glColor3f(r.color[0], r.color[1], r.color[2]);

    glVertex2i(r.vertex.x, r.vertex.y);
    glVertex2i(r.vertex.x, r.vertex.y + r.l);
    glVertex2i(r.vertex.x + r.r, r.vertex.y + r.l);
    glVertex2i(r.vertex.x + r.r, r.vertex.y);
    glEnd();

    // Draw border
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(r.vertex.x, r.vertex.y);
    glVertex2i(r.vertex.x, r.vertex.y + r.l);
    glVertex2i(r.vertex.x + r.r, r.vertex.y + r.l);
    glVertex2i(r.vertex.x + r.r, r.vertex.y);
    glEnd();

    // Highlight lowest vertex
    /*
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
    */
}
