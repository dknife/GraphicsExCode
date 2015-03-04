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
    glClearColor(0.7, 0.7, 0.7, 1.0);
    // ^{\it 카메라 투영 특성 설정 (glPerspective 사용). 이때는 GL\_PROJECTION 행렬모드여야 한다.}^
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1.0, 0.1, 500.0);
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

void draw(float radius, float r, float g, float b) {
    glColor3f(r,g,b);
    glutWireSphere(radius, 10, 10);
}
void display() {
    
    static float t=10;     t+=1.0;
    
    // The location of camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(15, 15, 15, 0, 0, 0, 0, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    drawAxes(); // ^{\it 축을 그림}^
    
    
    draw(1, 1.0, 0.5, 0.0); //^{\it 태양}^
    
    glPushMatrix();
    glRotated(t, 0.0, 1.0, 0.0);
    glTranslated(3.0, 0.0, 0.0);
    draw(0.2, 0.5, 0.8, 1.0);  // ^{\it 수성}^
    glPopMatrix(); // ^{\it 수성 영향권 끝}^
    
    glPushMatrix();
    glRotated(t*1.5, 0.0, 1.0, 0.0);
    glTranslated(5.0, 0.0, 0.0);
    draw(0.2, 1.0, 1.0, 0.0); // ^{\it 금성}^
    glPopMatrix(); // ^{\it 금성 영향권 끝}^
    
    glPushMatrix();
    glRotated(t*0.8, 0.0, 1.0, 0.0);
    glTranslated(7.0, 0.0, 0.0);
    draw(0.2, 0.2, 0.2, 1.0); // ^{\it 지구}^
    glPushMatrix();
    glRotated(t*10.0, 0.0, 1.0, 0.0);
    glTranslated(0.5, 0.0, 0.0);
    draw(0.05, 1.0, 1.0, 1.0); // ^{\it 지구의 영향권 내에 달을 그림}^
    glPopMatrix(); // ^{\it 달의 영향권 끝}^
    glPopMatrix(); // ^{\it 지구의 영향권 끝}^
    
    glPushMatrix();
    glRotated(t*0.5, 0.0, 1.0, 0.0);
    glTranslated(10.0, 0.0, 0.0);
    draw(0.25, 1.0, 0.5, 0.4); // ^{\it 화성}^
    glPopMatrix(); // ^{\it 화성 영향권 끝}^
    
    glPushMatrix(); // ^{\it 목성 영향권의 시작}^
    glRotated(t*0.7, 0.0, 1.0, 0.0);
    glTranslated(14.0, 0.0, 0.0);
    draw(0.5, 1.0, 0.5, 0.4); // ^{\it 목성}^
    glPushMatrix();
    glRotated(t*10.0, 0.0, 1.0, 0.0);
    glTranslated(0.8, 0.0, 0.0);
    draw(0.05, 1.0, 1.0, 1.0); // ^{\it 목성 위성 1번}^
    glPopMatrix(); // ^{\it 목성 위성 1번의 영향권 끝}^
    glPushMatrix();
    glRotated(t*12.0, 0.0, 1.0, 0.0);
    glTranslated(0.9, 0.0, 0.0);
    draw(0.07, 1.0, 1.0, 1.0); // ^{\it 목성 위성 2번}^
    glPopMatrix(); // ^{\it 목성 위성 2번의 영향권 끝}^
    glPushMatrix();
    glRotated(t*13.0, 0.0, 1.0, 0.0);
    glTranslated(0.7, 0.0, 0.0);
    draw(0.03, 1.0, 1.0, 1.0); // ^{\it 목성 위성 3번}^
    glPopMatrix(); //  ^{\it 목성 위성 2번의 영향권 끝}^
    glPopMatrix(); //  // ^{\it 목성의 영향권 끝}^
    
    glutSwapBuffers();
}


int main (int argc, char **argv) {
    init(argc, argv);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
}
