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
    glOrtho(-10,10,-5,15,-20,20);
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

void drawArm() {
    glPushMatrix();
    glScalef(1.0, 4.0, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
}

void drawHand() {
    glPushMatrix();
    glScalef(1.0, 2.0, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
}

void display() {
    
    // The location of camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 15, 0, 0, 0, 0, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    drawAxes(); // ^{\it 축을 그림}^
    
    glTranslated(0.0, 2.0, 0.0);
    drawAxes();
    drawArm();
    
    glTranslated(0.0, 2.0, 0.0);
    glRotatef(-45, 0.0, 0.0, 1.0);
    glTranslated(0.0, 2.0, 0.0);
    drawAxes();
    drawArm();
    
    glPushMatrix();
    glTranslated(0.0, 2.0, 0.0);
    glRotatef(-45, 0.0, 0.0, 1.0);
    glTranslated(0.0, 1.0, 0.0);
    drawAxes();
    drawHand();
    glPopMatrix();
    
    glTranslated(0.0, 2.0, 0.0);
    glRotatef(45, 0.0, 0.0, 1.0);
    glTranslated(0.0, 1.0, 0.0);
    drawAxes();
    drawHand();
    
    glutSwapBuffers();
}

int main (int argc, char **argv) {
    init(argc, argv);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
}
