#ifdef WIN32 // window
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#else // mac
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#endif

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.5, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.5, 0.0);
    glEnd();
    glFlush();
}

int main (int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Hello Triangle!");  // ^{\it 윈도우 생성}^
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glutDisplayFunc(myDisplay);	// ^{\it 디스플레이 콜백 등록}^
    glutMainLoop();				// ^{\it 이벤트 루프로}^
    return 0;
}