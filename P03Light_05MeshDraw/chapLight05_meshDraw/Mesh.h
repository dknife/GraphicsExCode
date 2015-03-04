#ifndef _mesh_sms_hh_
#define _mesh_sms_hh_

class cvertex {
public:
    float x;
    float y;
    float z;
};

class cface {
public:
    int v0; int v1; int v2;
};

class CMesh {
    int nV;  // number of vertices
    int nF;  // number of faces
    cvertex *v; // vertex array
    cface   *f; // face array
    cvertex *n;
    
public:
    float minx, miny, minz;
    float maxx, maxy, maxz;
    
public:
    CMesh();  // constructor
    ~CMesh(); // destructor
    
    // Mesh Data Handling Methods
    void loadMesh(char *meshFileName);
    void drawMesh(void);
    void computeNormals(void);
};

#endif