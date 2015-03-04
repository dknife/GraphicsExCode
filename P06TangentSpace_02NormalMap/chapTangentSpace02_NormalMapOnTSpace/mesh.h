#ifndef _simpleMeshTemp_2013_h
#define _simpleMeshTemp_2013_h

#ifdef WIN32
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#else // MAC OS X
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h> // OpenGL utility toolkit
#endif

struct CVec3 {
    float x, y, z;
};
struct CVec2 {
    float u, v;
};
struct CFace {
    int v1, v2, v3;
};
class CMesh {
    int nVertices;
    int nFaces;
    
    CVec3 *verts;
    CVec3 *normals;
    CVec3 *tangents;
    CVec3 *binormals;
    CVec2 *texCoords;
    
    CFace *faces;
private:
    void initializeMemory(void);
    void computeNormals(void);
    void drawTangentSpace(int idx);
    
public:
    CMesh();
    void createMesh(int nVRow, int nVCol);
    void drawWithGL(GLuint shaderProgram);
};
#endif