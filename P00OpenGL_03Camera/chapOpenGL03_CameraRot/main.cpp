#ifdef WIN32 // window
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#else // mac
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#endif

#include <math.h>

void init(int argc, char **argv) {
    // ^{\it 윈도우 생성, 버퍼 설정}^
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(512,512);
    glutCreateWindow("Camera Rotation");
    glClearColor(0.7, 0.7, 0.7, 1.0);
    // ^{\it 카메라 투영 특성 설정 (glPerspective 사용). 이때는 GL\_PROJECTION 행렬모드여야 한다.}^
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1.0, 0.1, 100.0);
}

void drawScene() {
    //^{\it 앞서 사용한 코드 \ref{code:OGL_opengl:simpleScene}의 그리기 코드를 여기에 넣는다. (단, glFlush는 여기서 사용하지 않는다)}^
    // ^{\it 색상의 지정}^
    glColor3f(0.0, 1.0, 0.0);
    
    // ^{\it 삼각형 그리기로 지정}^
    glBegin(GL_TRIANGLES);
    // mountain 1
    glVertex2f(-0.75, -0.25);
    glVertex2f(0.0, 0.25);
    glVertex2f(0.25, -0.25);
    // mountain 2 - ^{\it 그리기 색상 변경}^
    glColor3f(0.5, 0.5, 0.1);
    glVertex2f(-0.25, -0.25);
    glVertex2f(0.75, 0.25);
    glVertex2f(1.0, -0.25);
    glEnd();
    
    // ^{\it 사각형 그리기로 지정}
    glBegin(GL_QUADS);
    // roof ^{\it 파란색으로 색상 변경}^
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(-1.0, 0.25);
    glVertex2f(-0.75, 0.5);
    glVertex2f(-0.25, 0.5);
    glVertex2f(0.0, 0.25);
    // house ^{\it 노란색으로 색상 변경}^
    glColor3f(1.0, 1.0, 0.0);
    glVertex2f(-0.75, 0.25);
    glVertex2f(-0.75, -0.25);
    glVertex2f(-0.25, -0.25);
    glVertex2f(-0.25, 0.25);
    
    // tree ^{\it 갈색으로 변경}^
    glColor3f(0.7, 0.5, 0.0);
    glVertex2f(0.5, 0.25);
    glVertex2f(0.75, 0.25);
    glVertex2f(0.75, -0.25);
    glVertex2f(0.5, -0.25);
    glEnd();
    
    // ^{\it 입력된 정점을 모두 이용하는 다각형 그리기로 지정}^
    glBegin(GL_POLYGON);
    // vertices information
    int n=20;
    float radius=0.1;
    glColor3f(1.0, 1.0, 0.0);
    float angle = 0.0; float step=(3.14159*2.0)/n;
    // ^{\it 반복문 내에서 여러 개의 정점 좌표를 계산한 뒤에 지정하는 방식}^
    // ^{\it 여기서는 원을 이루는 정점들을 계산하고 있음}^
    while (angle<3.14159*2.0) {
        glVertex2f(radius*cos(angle), radius*sin(angle)+0.75);
        angle += step;
    }
    glEnd();
    
    // ^{\it 원의 중심을 옮기고 반지름을 바꾼 뒤에 다시 그림}^
    glBegin(GL_POLYGON);
    // vertices information
    n=20;
    radius=0.25;
    glColor3f(0.0, 1.0, 0.0);
    angle = 0.0; step=(3.14159*2.0)/n;
    while (angle<3.14159*2.0) {
        glVertex2f(radius*cos(angle)+0.625, radius*sin(angle)+0.25);
        angle += step;
    }
    glEnd();
}
void drawAxes() {
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);   glVertex3f(1.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);  glVertex3f(0.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);  glVertex3f(0.0, 0.0, 1.0);
    glEnd();
}

void display() {
    static float t=0.0;
    // ^{\it 카메라의 위치와 방향을 설정한다. 이때는 GL\_MODELVIEW 행렬 모드여야 한다.}^
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( 2.0*sin(t), 1, 2.0*cos(t), 0, 0, 0,  0, 1, 0);
    t+=0.001;
    glClear(GL_COLOR_BUFFER_BIT);
    drawScene();
    glLineWidth(5);
    drawAxes();
    glLineWidth(1);
    glFlush();
};

int main (int argc, char **argv) {
    init(argc, argv);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
}
