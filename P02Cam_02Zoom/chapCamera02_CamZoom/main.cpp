#ifdef WIN32 // window
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#else // mac
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#endif

#include <math.h>

bool  bOrthoCam = true;
float aspRatio = 1.0;
float zoomFactor = 1.0;
void setCamera(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (bOrthoCam) {
        glOrtho(-2.0*aspRatio/zoomFactor,
                2.0*aspRatio/zoomFactor,
                -2.0/zoomFactor, 2.0/zoomFactor,
                -200.0, 200.0);
    }
    else { // perspective camera
        gluPerspective(60/zoomFactor, aspRatio, 0.1, 100);
    }
}
void init(int argc, char **argv) {
    // ^{\it 윈도우 생성, 버퍼 설정}^
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(512,512);
    glutCreateWindow("Translations");
    glClearColor(0.7, 0.7, 0.7, 1.0);
    // ^{\it 카메라 투영 특성 설정 (glPerspective 사용). 이때는 GL\_PROJECTION 행렬모드여야 한다.}^
    
    // 초기화
    glColor3f(0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
}

void keyboard(unsigned char k, int x, int y) {
    switch (k) {
        case 'm': bOrthoCam = bOrthoCam?false:true; break; // ^{\it 카메라 변경}^
        case '<': zoomFactor *= 0.95; break; // ^{\it 줌 아웃}^
        case '>': zoomFactor *= 1.05; break; // ^{\it 줌 인}^
        default: break;
    }
    setCamera();
    glutPostRedisplay();
}
void reshape(int w, int h) {
    aspRatio = float(w)/float(h);
    glViewport(0, 0, w, h);
    setCamera();
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glutWireTeapot(1.0);
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    init(argc, argv);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}
    
