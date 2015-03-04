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
    glutCreateWindow("Translations");
    glClearColor(0.8, 0.8, 0.8, 1.0);
    // ^{\it 카메라 투영 특성 설정 (glPerspective 사용). 이때는 GL\_PROJECTION 행렬모드여야 한다.}^
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1.0, 0.1, 100.0);
}


void drawAxes() {
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);   glVertex3f(1.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);  glVertex3f(0.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);  glVertex3f(0.0, 0.0, 1.0);
    glEnd();
    glLineWidth(1.0);
}

void draw() {
    glutWireSphere(0.5, 30, 30); // ^{it 반지름 0.5의 구를 원점을 중심으로 그림}^
}

void display() {
    
    // The location of camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    drawAxes(); // ^{\it 축을 그림}^
    
    glColor3f(1, 1, 0);
    draw(); // ^{\아무런 변환 없이 원점에 구를 그림}^
    
    glTranslatef(1.0, 0.0, 0.0); //^{\it $(1,0,0)$ 벡터만큼 이동을 함}^
    glColor3f(0, 1, 1);
    draw(); //^{\적용된 변환을 이용하여 구를 그림}^
    glTranslatef(-0.5, 1.0, 0.0); //^{\it $(-0.5,1,0)$ 벡터만큼 이동을 함}^
    glColor3f(1, 0, 0);
    draw(); //^{\적용된 변환을 이용하여 옮겨진 구름 그림}^
    
    glutSwapBuffers();
}

int main (int argc, char **argv) {
    init(argc, argv);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
}
