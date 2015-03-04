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
    glutCreateWindow("Translations & Rotation");
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

void drawLocalAxes() { drawAxes(); }

void draw() {
    glutWireTeapot(0.3);
}

void display() {
    // camera positioning
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( 2, 2, 3, 0, 0, 0, 0, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawAxes();
    
    drawLocalAxes();
    glColor4f(1, 1, 0, 0.25);
    draw();
    
    glTranslatef(1.0, 0.0, 0.0);
    drawLocalAxes();
    glColor4f(0, 1, 1, 0.25);
    draw();
    
    glRotatef(180, 0.0, 0.0, 1.0);
    glTranslatef(0.0,-1.0, 0.0);
    drawLocalAxes();
    glColor4f(1, 0, 0, 0.25);
    draw();
    
    glTranslatef(1.0, 0.0, 0.0);
    drawLocalAxes();
    glColor4f(1, 1, 1, 0.25);
    draw();
    
    glutSwapBuffers();
}


int main (int argc, char **argv) {
    init(argc, argv);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
}
