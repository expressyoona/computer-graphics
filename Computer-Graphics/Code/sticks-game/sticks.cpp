/*
 *  Windows: -lglut32 -lglu32 -lopengl32 -lwinmm -lgdi32
 *  Linux: -lGL -lGLU -lglut
 */
#include <GL/glut.h>
#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <time.h>

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

const int MAX_WIDTH = 1000;
const int MAX_HEIGHT = 1000;

const int N = 10; // Số thanh đầu game
const int TIME_REFRESH = 5; // Thời gian tối thiểu(s) để thêm thanh mới
const int MAX_STICKS = 20; // Số lượng thanh tối đa
const int MAX_DEPTH = 10; // Độ sâu tối đa của 1 thanh

int currentStick = N;
Rectangle arr[MAX_STICKS];
/*
 * Rules - Luật chơi
 * Khởi đầu sẽ có N thanh hình chữ nhật nằm đè lên nhau
 * Mỗi thanh sẽ có độ sâu z, thanh có z nhỏ hơn sẽ nằm đè lên thanh có z lớn hơn
 * Nếu người chơi click vào 1 thanh không bị đè bởi bất kỳ thanh nào. Thanh đó sẽ biến mất
 * Nếu người chơi không làm biến mất được 1 thanh nào trong vào T(s), sẽ có 1 thanh được sinh ra ngẫu nhiên
 * Điều kiện game kết thúc: Không còn thanh nào trên màn hình hoặc số thanh đạt đến số lượng MAX_STICKS(MAX_STICKS > N)
 */

/*
 * Quy ước cách sinh ngẫu nhiên 1 thanh:
 * Đầu tiên sinh ngẫu nhiên 1 cặp tọa độ (x, y) với x, y < 500. Đây là tọa độ góc dưới bên trái của thanh hình chữ nhật.
 * Sinh tiếp ngẫu nhiên chiều dài(l) và chiều rộng(r) của thanh. Đảm bảo rằng l+y và r+x < MAX_WIDTH/MAX_HEIGHT(không bị tràn)
 * Sinh lần lượt 3 số m, n, p ngẫu nhiên trong đoạn [0, 255]. Sau đó chia từng số cho 255. Dùng glColor3f với các số sau khi chia để có mã màu ngẫu nhiên. Có thể dùng thẳng glColor3i(chưa thử)
 * Sinh ngẫu nhiên độ sâu z trong đoạn [0, MAX_DEPTH]
 * Vẽ hình chữ nhật với các đỉnh (x, y), (x, y + l), (x+r, y), (x+r, y+l) và màu như trên. Đảm bảo rằng hình chữ nhật sẽ đè những thanh có độ sâu cao hơn hay bị đè bởi những thanh có độ sâu nhỏ hơn
 */

void initGl();
void paint();
void onMouseClick(int button, int state, int x, int y);
bool clickedRectangle(Point2D A);
Rectangle generateStick();
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
    glutMainLoop();
    return 0;
}

void onMouseClick(int button, int state, int x, int y) {
    // In ra tọa độ được click, (0, 0) là góc trên bên trái
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // std::cout<<x<<", "<<y<<std::endl;
        std::cout<<clickedRectangle({x, MAX_WIDTH - y})<<std::endl;
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
    
    int x, y, r, l, transpose, z = 0;
    float red, green, blue;
    f(i, 0, N) {
        glBegin(GL_QUADS);
        x = std::rand() % (MAX_WIDTH/2);
        y = std::rand() % (MAX_HEIGHT/2);

        red = (std::rand() % 255)/255.0;
        green = (std::rand() % 255)/255.0;
        blue = (std::rand() % 255)/255.0;

        glColor3f(red, green, blue);
        transpose = rand() % 2;
        // 0 is landscape, 1 is portrait
        if (transpose == 0) {
            r = 20;
            l = 400 + (std::rand() % (MAX_HEIGHT/2 - y));
        } else {
            l = 20;
            r = 400 + (std::rand() % (MAX_WIDTH/2 - x));
        }
        arr[i] = {{x, y}, r, l, 0, {red, green, blue}};
        std::cout<<i<<" -> ";
        printRectangle(arr[i]);
        glVertex2i(x, y);
        glVertex2i(x, y+l);
        glVertex2i(x+r, y+l);
        glVertex2i(x+r, y);
        glEnd();

        // Draw border
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2i(x, y);
        glVertex2i(x, y+l);
        glVertex2i(x+r, y+l);
        glVertex2i(x+r, y);
        glEnd();
    }    
    glFlush();
}

bool clickedRectangle(Point2D A) {
    int minX, maxX, minY, maxY;
    std::cout<<"("<<A.x<<", "<<A.y<<") ";
    f(i, 0, currentStick) {
        minX = arr[i].vertex.x;
        minY = arr[i].vertex.y;
        maxX = minX + arr[i].r;
        maxY = minY + arr[i].l;
        
        if (minX <= A.x && A.x <= maxX && minY <= A.y && A.y <= maxY) {
            std::cout<<i<<std::endl;
            return true;
        }
    }
    std::cout<<std::endl;
    return false;
}

Rectangle generateStick() {
    // Generate a random rectanle
}