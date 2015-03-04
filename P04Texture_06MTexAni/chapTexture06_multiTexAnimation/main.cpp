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

GLuint setTexture(char *filename) {
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
    
    // ^{\it 텍스처 유니트 0에 텍스처를 하나 할당}^
    glActiveTexture(GL_TEXTURE0);
    tex1 = setTexture("science.jpg");
    
    // ^{\it 텍스처 유니트 1에 텍스처를 하나 할당}^
    glActiveTexture(GL_TEXTURE1);
    tex2 = setTexture("terrain.jpg");
    
    glClearColor(0.0, 0.7, 1.0, 1.0);
    
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    
}

void myDisplay() {
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    static float angle = 0;
    angle += 1.0;
    
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex2);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(5.0, 5.0, 1.0);
    
    glBegin(GL_QUADS);
    glMultiTexCoord2f(GL_TEXTURE0, 0.0, 0.0);
    glMultiTexCoord2f(GL_TEXTURE1, 0.0, 0.0);
    glVertex3f(-0.5, 0.5, 0.0);
    glMultiTexCoord2f(GL_TEXTURE0, 0.0, 1.0);
    glMultiTexCoord2f(GL_TEXTURE1, 0.0, 1.0);
    glVertex3f(-0.5,-0.5, 0.0);
    glMultiTexCoord2f(GL_TEXTURE0, 1.0, 1.0);
    glMultiTexCoord2f(GL_TEXTURE1, 1.0, 1.0);
    glVertex3f( 0.5,-0.5, 0.0);
    glMultiTexCoord2f(GL_TEXTURE0, 1.0, 0.0);
    glMultiTexCoord2f(GL_TEXTURE1, 1.0, 0.0);
    glVertex3f( 0.5, 0.5, 0.0);
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