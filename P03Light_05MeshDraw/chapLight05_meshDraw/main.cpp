#ifdef WIN32 // window
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#else // mac
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#endif

#include <math.h>

#include "Mesh.h"

CMesh myMesh1;
CMesh myMesh2;

// material data
GLfloat mat_diffuse[] =  { 1.0f, 1.0f, 0.0f, 1.0f }; // diffuse material
GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // specular material
GLfloat mat_ambient[] =  { 0.0f, 0.0f, 0.0f, 1.0f }; // ambient material
GLfloat mat_shininess[] ={ 127.0 };
// light data
GLfloat lit_diffuse[] =  { 1.0f, 1.0f, 1.0f, 1.0f }; // diffuse light
GLfloat lit_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // specular light
GLfloat lit_ambient[] =  { 0.0f, 0.0f, 0.0f, 0.0f }; // ambient light

// light position
GLfloat lit_position[] = { 1.0f, 1.0f, 1.0f, 0.0f }; // light position

void SetLight() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    // set material properties
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
    // set light properties
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lit_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lit_specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lit_ambient);
}

void GLInit(void) {
    
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Light");
    
    myMesh1.loadMesh("female1.sms");
    myMesh2.loadMesh("sleeveless.sms");
    
    SetLight();
    
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.0, 0.7, 1.0, 1.0);
    
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1.0, 0.1, 1000.0);
}

void myDisplay() {
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(20, 40, 50, 0,50,0, 0,1,0);
    // light position setting
    glLightfv(GL_LIGHT0, GL_POSITION, lit_position);
    
    // draw code
    glColor3f(1.0, 1.0, 0.5);
    myMesh1.drawMesh();
    glColor3f(0.0, 0.5, 1.0);
    myMesh2.drawMesh();
    
    glutSwapBuffers();
}

int main (int argc, char * argv[]) {
    
    // window initialization with glut
    glutInit(&argc, argv);
    
    GLInit();
    
    // register callbacks
    glutDisplayFunc(myDisplay);
    glutIdleFunc(myDisplay);
    // enter the event loop
    glutMainLoop();
    
    return 0;
}