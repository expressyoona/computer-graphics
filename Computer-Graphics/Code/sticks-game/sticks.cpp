/*
 *  Windows: -lglut32 -lglu32 -lopengl32 -lwinmm -lgdi32
 *  Linux: -lGL -lGLU -lglut
 */
#include <GL/glut.h>
#include <bits/stdc++.h>
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
const int MIN_LENGTH = 400; // Chiều dài/rộng tối thiểu của 1 thanh nằm ngang/dọc
const int MIN_WIDTH = 20; // Chiều rộng/dài tối thiểu của 1 thanh nằm ngang/dọc

// int currentStick = N; // Nếu dùng vector, thì dùng listSticks.size() thay cho currentStick
Rectangle arr[MAX_STICKS];
bool started = false;

std::vector<Rectangle> listSticks;
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
void timer(int value);
bool clickedRectangle(Point2D A);
Rectangle generateStick();
int random(int a, int b); // Random number x: a <= x <= b
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
        std::cout<<clickedRectangle({x, MAX_WIDTH - y})<<std::endl;
        // Cần xóa thanh ra khỏi vector trước khi vẽ lại
        // glutPostRedisplay();
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
    std::cout<<"Paint method"<<std::endl;
    glClear(GL_COLOR_BUFFER_BIT);
    if (!started) {
        f(i, 0, N) {
            listSticks.push_back(generateStick());
        }
        started = true;
    } else {
        listSticks.push_back(generateStick());
    }

    f(i, 0, listSticks.size()) {
        std::cout<<"["<<i<<"/"<<listSticks.size()<<"]: ";
        printRectangle(listSticks[i]);
        glBegin(GL_QUADS);
        glColor3f(listSticks[i].color[0], listSticks[i].color[1], listSticks[i].color[2]);
        glVertex2i(listSticks[i].vertex.x, listSticks[i].vertex.y);
        glVertex2i(listSticks[i].vertex.x, listSticks[i].vertex.y + listSticks[i].l);
        glVertex2i(listSticks[i].vertex.x + listSticks[i].r, listSticks[i].vertex.y + listSticks[i].l);
        glVertex2i(listSticks[i].vertex.x + listSticks[i].r, listSticks[i].vertex.y);
        glEnd();

        // Draw border
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2i(listSticks[i].vertex.x, listSticks[i].vertex.y);
        glVertex2i(listSticks[i].vertex.x, listSticks[i].vertex.y + listSticks[i].l);
        glVertex2i(listSticks[i].vertex.x + listSticks[i].r, listSticks[i].vertex.y + listSticks[i].l);
        glVertex2i(listSticks[i].vertex.x + listSticks[i].r, listSticks[i].vertex.y);
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
    glFlush();
}

bool clickedRectangle(Point2D A) {
    int minX, maxX, minY, maxY;
    std::cout<<"("<<A.x<<", "<<A.y<<") ";
    f(i, 0, listSticks.size()) {
        minX = listSticks[i].vertex.x;
        minY = listSticks[i].vertex.y;
        maxX = minX + listSticks[i].r;
        maxY = minY + listSticks[i].l;
        
        if (minX <= A.x && A.x <= maxX && minY <= A.y && A.y <= maxY) {
            std::cout<<i<<std::endl;
            listSticks.erase(listSticks.begin()+i);
            if (listSticks.empty()) {
                // Game over
                std::cout<<"You win!"<<std::endl;
            } else {
                f(i, 0, listSticks.size()) {
                    std::cout<<i<<" -> ";
                    printRectangle(listSticks[i]);
                }
            }
            
            return true;
        }
    }
    std::cout<<std::endl;
    return false;
}

Rectangle generateStick() {
    int x, y, r, l, transpose, z = 0;
    float red, green, blue;
    
    x = std::rand() % MAX_WIDTH/2;
    y = std::rand() % MAX_HEIGHT/2;

    red = (std::rand() % 255)/255.0;
    green = (std::rand() % 255)/255.0;
    blue = (std::rand() % 255)/255.0;

    transpose = rand() % 2;
    // 0 is landscape, 1 is portrait
    if (transpose == 0) {
        l = MIN_WIDTH;
        r = random(MIN_LENGTH, MAX_HEIGHT - x);
    } else {
        r = MIN_WIDTH;
        l = random(MIN_LENGTH, MAX_WIDTH - y);
    }
    Rectangle rectangle = {{x, y}, r, l, 0, {red, green, blue}};
    return rectangle;
}

int random(int a, int b) {
    int result = (std::rand() % (b - a)) + a;
    std::cout<<"("<<a<<", "<<b<<") = "<<result<<std::endl;
    return result;
}