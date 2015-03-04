#ifndef _simpleMeshTemp_2013_h
#define _simpleMeshTemp_2013_h

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
public:
    CMesh();
    void createMesh(int nVRow, int nVCol);
    void drawTangentSpace(int idx);
    void drawWithGL(void);
};
#endif