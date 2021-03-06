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

void SetupTexture(void) {
    int w, h, nComp;
    unsigned char *img = stbi_load("terrain.jpg", &w, &h, &nComp, 0);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h,
                 0, GL_RGB, GL_UNSIGNED_BYTE, img);
    
    stbi_image_free(img);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glEnable(GL_TEXTURE_2D);
    
}

void GLInit(void) {
    
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Texture");
    
    SetupTexture();
    
    glClearColor(0.0, 0.7, 1.0, 1.0);
    
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1.0, 0.1, 1000.0);
}

void myDisplay() {
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,2, 0,0,0, 0,1,0);
    
    // draw code
    glBegin(GL_QUADS);
    
    glTexCoord2f(0, 0);
    glVertex3f(-1,-1,0);
    
    glTexCoord2f(1, 0);
    glVertex3f(1,-1,0);
    
    glTexCoord2f(1,1);
    glVertex3f(1,1,0);
    
    glTexCoord2f(0,1);
    glVertex3f(-1,1,0);
    glEnd();
    
   
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