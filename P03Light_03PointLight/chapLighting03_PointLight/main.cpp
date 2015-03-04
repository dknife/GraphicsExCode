#ifdef WIN32 // window
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#else // mac
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#endif
#include <math.h>

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
GLfloat lit_position[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // light position

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
    glutCreateWindow("Point Light");
    
    SetLight();
    
    glClearColor(0.0, 0.7, 1.0, 1.0);
    glPointSize(5);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1.0, 0.1, 100.0);
}

void myDisplay() {
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0, 15, 0,0,0, 0,1,0);
    // light position setting
    static float t = 0.0; t+=0.01;
    lit_position[0] = 5.0*sin(t); lit_position[2] = 5.0*cos(t);
    glLightfv(GL_LIGHT0, GL_POSITION, lit_position);
    
    for(int i=0;i<10;i++) {
        for(int j=0;j<10;j++) {
            glPushMatrix();
            glTranslatef(i-4.5,j-4.5,0);
            glutSolidSphere(0.5, 30, 30);
            glPopMatrix();
        }
    }
    
    //drawing light
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(lit_position[0], lit_position[1], lit_position[2]);
    glColor3fv(lit_diffuse);
    glutSolidSphere(0.1, 10,10);
    glPopMatrix();
    glEnable(GL_LIGHTING);
    
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