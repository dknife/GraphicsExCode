
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
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(512,512);
    glutCreateWindow("DEPTH BUFFER");
    glClearColor(0.7, 0.7, 0.7, 1.0);
    // ^{\it 깊이 버퍼 검사를 활성화한다.}
    glEnable(GL_DEPTH_TEST);
    // ^{\it 카메라 투영 특성 설정 (glPerspective 사용). 이때는 GL\_PROJECTION 행렬모드여야 한다.}^
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1.0, 0.1, 100.0);
}

void drawScene() {
    // drawing code
    glBegin(GL_QUADS);
    // ^{\it 천정}^
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f( 0.5, 0.5, -0.5);
    glVertex3f( 0.5, 0.5,  0.5);
    glVertex3f(-0.5, 0.5,  0.5);
    // ^{\it 바닥}^
    glColor3f(0.0,1.0,1.0);
    glVertex3f(-0.5,-0.5, -0.5);
    glVertex3f( 0.5,-0.5, -0.5);
    glVertex3f( 0.5,-0.5,  0.5);
    glVertex3f(-0.5,-0.5,  0.5);
    // ^{\it 왼쪽 벽}^
    glColor3f(0.0,1.0,0.0);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5,  0.5);
    glVertex3f(-0.5,-0.5,  0.5);
    glVertex3f(-0.5,-0.5, -0.5);
    // ^{\it 오른쪽 벽}^
    glColor3f(1.0,1.0,1.0);
    glVertex3f( 0.5, 0.5, -0.5);
    glVertex3f( 0.5, 0.5,  0.5);
    glVertex3f( 0.5,-0.5,  0.5);
    glVertex3f( 0.5,-0.5, -0.5);
    glEnd();
}
void drawAxes() {
    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);   glVertex3f(1.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);  glVertex3f(0.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);  glVertex3f(0.0, 0.0, 1.0);
    glEnd();
}

void draw() {
    drawScene();
    drawAxes();
}

void display() {
    static float t=0.0;
    // ^{\it 카메라의 위치와 방향을 설정한다. 이때는 GL\_MODELVIEW 행렬 모드여야 한다.}^
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( 2.0*sin(t), 1, 2.0*cos(t), 0, 0, 0,  0, 1, 0);
    t+=0.001;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    draw();
    glutSwapBuffers();
};

int main (int argc, char **argv) {
    init(argc, argv);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
}
