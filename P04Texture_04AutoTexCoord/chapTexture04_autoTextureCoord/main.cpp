#ifdef WIN32 // window
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#else // mac
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#endif

#include <stdlib.h>
#include <math.h>

#include "STBImage.h"

GLuint tex1, tex2;

GLuint SetupTexture(char *filename) {
    int w, h, nComp;
    unsigned char *img = stbi_load(filename, &w, &h, &nComp, 0);
    
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h,
                 0, GL_RGB, GL_UNSIGNED_BYTE, img);
    
    stbi_image_free(img);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    return texture;
}

void GLInit(void) {
    
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Texture");
    
    glEnable(GL_TEXTURE_2D);
    
    tex1 = SetupTexture("science.jpg");
    tex2 = SetupTexture("terrain.jpg");
    
    glClearColor(0.0, 0.7, 1.0, 1.0);
    
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1.0, 0.1, 1000.0);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void myDisplay() {
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,2, 0,0,0, 0,1,0);
    
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    
    static float angle = 0;
    angle += 1.0;
    
    glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, tex1);
    glPushMatrix();
    glTranslatef(-0.75,0.0,0.0);
    glRotatef(angle, 1, 1, 1);
    glutSolidTeapot(0.5);
    glPopMatrix();
    
    glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

    glPushMatrix();
    glTranslatef( 0.0,0.0,0.0);
    glRotatef(angle, 1, 1, 1);
    glutSolidTeapot(0.5);
    glPopMatrix();

    glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glPushMatrix();
    glTranslatef( 0.75,0.0,0.0);
    glRotatef(angle, 1, 1, 1);
    glutSolidTeapot(0.5);
    glPopMatrix();

    
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