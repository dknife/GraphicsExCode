#include <stdio.h>
#include <math.h>
#include "textRead.h"
#include "texture.h"
#include "mesh.h"

#ifdef WIN32
#include <windows.h>
#include <gl/glew.h>
#include <gl/gl.h>
#include <gl/glut.h>
#else // MAC OS X
#include <OpenGL/OpenGL.h> // OpenGL core and utility lib.
#include <GLUT/GLUT.h> // OpenGL utility toolkit lib.
#endif

void setShaders();

float lightX=0.0f, lightY=0.0f;

GLuint vertexShader, fragShader, shaderProgram;
CMesh mesh;

void init(int argc, char **argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(512,512);
    glutCreateWindow("OpenGL 2.0 and shaders");
#ifdef WIN32
    glewInit();
#endif
    
    // 추가적 초기화 ...
    glClearColor(0.75, 0.75, 1.0, 1.0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1.0, 0.1, 100.0);
    
    setShaders();
    
    loadTextureAtStage("uvGrid.jpg", 0);
    loadTextureAtStage("normalmap.png", 1);
    mesh.createMesh(25,25);
    
}

void draw() {
    glColor3f(1.0, 0.0, 0.0);
    
    static float t=0.0f;
    GLuint lightLoc = glGetUniformLocation(
                                           shaderProgram, "lightDir");
    glUniform3f(lightLoc, 0.5+0.5*sin(t), 1.5, 0.5+0.5*cos(t));
    t+=0.1;
    
    GLuint texLoc;
    texLoc = glGetUniformLocation(shaderProgram, "ColorMap");
    glUniform1i(texLoc, 0);
    texLoc = glGetUniformLocation(shaderProgram, "NormalMap");
    glUniform1i(texLoc, 1);
    
    mesh.drawWithGL(shaderProgram);
}

void display() {
    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.5, 1.0, 1.0,
              0.5, 0.0, 0.5,
              0.0, 1.0, 0.0);
    
    
    glUseProgram(shaderProgram);
    draw();
    glUseProgram(NULL);
    
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
        case 'a': lightX-=0.05f; break;
        case 'd': lightX+=0.05f; break;
        case 'w': lightY+=0.05f; break;
        case 's': lightY-=0.05f; break;
        default:
            break;
    }
}


int main (int argc, char **argv) {
    
    // 시스템 수행 전에 해야할 초기화 작업 수행
    init(argc, argv);
    
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
}