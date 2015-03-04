#include <stdio.h>
#include <math.h>
#include "textRead.h"
#include "texture.h"

#ifdef WIN32
#include <windows.h>
#include <gl/glew.h>
#include <gl/gl.h>
#include <gl/glut.h>
#else // MAC OS X
#include <OpenGL/OpenGL.h> // OpenGL core and utility lib.
#include <GLUT/GLUT.h> // OpenGL utility toolkit lib.
#endif

enum IPMode {
    NONE, BRIGHT, CONTRAST, SATURATION, SMOOTHING, NOISEREDUCTION, EDGEDETECT, NEGALAPLACIAN, SHARPEN
};

int  processingMode = NONE;
int  imgW = 0;
int  imgH = 0;

void setShaders();

GLuint vertexShader, fragShader, shaderProgram;

void init(int argc, char **argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1024,768);
    glutCreateWindow("OpenGL 2.0 and shaders");
#ifdef WIN32
    glewInit();
#endif
    
    // 추가적 초기화 ...
    glClearColor(0.5, 0.5, 1.0, 1.0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1.0, 0.1, 100.0);
    
    glShadeModel(GL_FLAT);
    
    setShaders();
    
    GLuint texHandle = setTexture("baboon.jpg", &imgW, &imgH);
    
    
    glEnable(GL_TEXTURE_2D);
}

void draw() {
    
    GLuint samplerLoc = glGetUniformLocation(shaderProgram, "texture");
    glUniform1i(samplerLoc, 0);
    
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1.0, 1.0, 0.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-1.0,-1.0, 0.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f( 1.0,-1.0, 0.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f( 1.0, 1.0, 0.0);
    glEnd();
}

void display() {
    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.0, 0.0, 3.0,
              1.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    
    
    glUseProgram(shaderProgram);
    
    GLuint modeLoc = glGetUniformLocation(shaderProgram, "mode");
    glUniform1i(modeLoc, processingMode);
    
    glUniform1i(glGetUniformLocation(shaderProgram, "imgW"), imgW);
    glUniform1i(glGetUniformLocation(shaderProgram, "imgH"), imgH);
    
    
    draw();
    glUseProgram(NULL);
    glTranslated(2.0, 0.0, 0.0);
    draw();
    
    glutSwapBuffers();
    
};


void setShaders() {
    char *vs = NULL,*fs = NULL;// *fs2 = NULL;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    vs = textRead("shader.vert");
    fs = textRead("shader.frag");
    
    
    const char * vv = vs;
    const char * ff = fs;
    
    glShaderSource(vertexShader, 1, &vv,NULL);
    glShaderSource(fragShader, 1, &ff,NULL);
    
    
    
    delete[] vs;
    delete[] fs;
    
    
    glCompileShader(vertexShader);
    glCompileShader(fragShader);
    printShaderInfoLog(vertexShader);
    printShaderInfoLog(fragShader);
    
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragShader);
    glLinkProgram(shaderProgram);
    printProgramInfoLog(shaderProgram);
}


void keyboard(unsigned char c, int x, int y) {
    switch (c) {
        case '0': processingMode = NONE; break;
        case '1': processingMode = BRIGHT; break;
        case '2': processingMode = CONTRAST; break;
        case '3': processingMode = SATURATION; break;
        case '4': processingMode = SMOOTHING; break;
        case '5': processingMode = NOISEREDUCTION; break;
        case '6': processingMode = EDGEDETECT; break;
        case '7': processingMode = NEGALAPLACIAN; break;
        case '8': processingMode = SHARPEN; break;
    }
    glutPostRedisplay();
}

int main (int argc, char **argv) {
    
    // 시스템 수행 전에 해야할 초기화 작업 수행
    init(argc, argv);
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}