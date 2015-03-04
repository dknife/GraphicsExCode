/*
 *  Mesh.cpp
 *  Camera
 *
 *  Created by 1J519-00 on 2014. 11. 19..
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#include "Mesh.h"

#ifdef WIN32
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#else
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BIGNUMBER 100000000000000000000000.0

CMesh::CMesh() : nV(0), nF(0), v(NULL), f(NULL), n(NULL),
minx( BIGNUMBER), miny( BIGNUMBER), minz( BIGNUMBER),
maxx(-BIGNUMBER), maxy(-BIGNUMBER), maxz(-BIGNUMBER)
{ }

CMesh::~CMesh() {
    if(v) delete[] v;
    if(f) delete[] f;
}

void CMesh::loadMesh(char *meshFileName) {
    FILE *fptr = fopen(meshFileName, "r");
    if(!meshFileName || !fptr) {
        printf("file open error\n"); exit(0);
    }
    
    fscanf(fptr, "%d", &nV);
    v = new cvertex[nV];
    for (int i=0; i<nV; i++) {
        fscanf(fptr, "%f", &v[i].x);
        fscanf(fptr, "%f", &v[i].y);
        fscanf(fptr, "%f", &v[i].z);
    }
    fscanf(fptr, "%d", &nF);
    f = new cface[nF];
    for (int i=0; i<nF; i++) {
        fscanf(fptr, "%d", &f[i].v0);
        fscanf(fptr, "%d", &f[i].v1);
        fscanf(fptr, "%d", &f[i].v2);
    }
    
    n = new cvertex[nV]; // allocate memory to normal array
    computeNormals();
    
}

void CMesh::computeNormals(void) { // private method
    
    for(int i=0;i<nV;i++) {
        n[i].x = n[i].y = n[i].z = 0.0;
    }
    
    for(int i=0; i<nF; i++) {
        // compute normal for each face
        cvertex p0, p1, p2;
        cvertex v0, v1; cvertex faceN;
        int vert0, vert1, vert2;
        vert0 = f[i].v0; vert1 = f[i].v1; vert2 = f[i].v2;
        p0 = v[vert0];
        p1 = v[vert1];
        p2 = v[vert2];
        v0.x = p1.x-p0.x; v0.y = p1.y-p0.y; v0.z = p1.z-p0.z;
        v1.x = p2.x-p0.x; v1.y = p2.y-p0.y; v1.z = p2.z-p0.z;
        
        faceN.x = v0.y*v1.z-v0.z*v1.y;
        faceN.y = v0.z*v1.x-v0.x*v1.z;
        faceN.z = v0.x*v1.y-v0.y*v1.x;
        
        // add the computed normal to normals of vertices in the face
        n[vert0].x += faceN.x; n[vert0].y += faceN.y; n[vert0].z += faceN.z;
        n[vert1].x += faceN.x; n[vert1].y += faceN.y; n[vert1].z += faceN.z;
        n[vert2].x += faceN.x; n[vert2].y += faceN.y; n[vert2].z += faceN.z;
    }
    
    for(int i=0;i<nV;i++) {
        // normalize n[i]
        float len = sqrt(n[i].x*n[i].x+n[i].y*n[i].y+n[i].z*n[i].z);
        n[i].x /= len; n[i].y /= len; n[i].z /= len;
    }
    
}

void CMesh::drawMesh(void) {
    
    if(!v || !f) return;
    glBegin (GL_TRIANGLES) ;
    for(int i=0;i<nF;i++) {
        // normal vector should be specified here
        cvertex p0, p1, p2;
        int vert0, vert1, vert2;
        vert0 = f[i].v0; vert1 = f[i].v1; vert2 = f[i].v2;
        p0 = v[vert0];
        p1 = v[vert1];
        p2 = v[vert2];
        glNormal3f(n[vert0].x, n[vert0].y, n[vert0].z);
        glVertex3f( p0.x, p0.y, p0.z);
        glNormal3f(n[vert1].x, n[vert1].y, n[vert1].z);
        glVertex3f( p1.x, p1.y, p1.z);
        glNormal3f(n[vert2].x, n[vert2].y, n[vert2].z);
        glVertex3f( p2.x, p2.y, p2.z);
    }
    glEnd() ;
    
}