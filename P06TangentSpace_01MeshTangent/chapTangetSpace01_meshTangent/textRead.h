#ifndef _TEXTFILEREADER_H2013
#define _TEXTFILEREADER_H2013

#ifdef WIN32
#include <windows.h>
#include <gl/glew.h>
#include <gl/gl.h>
#include <gl/glut.h>
#else // MAC OS X
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h> // OpenGL utility toolkit
#endif


void printShaderInfoLog(GLuint shader);
void printProgramInfoLog(GLuint obj);

char* textRead(char* filename);

#endif