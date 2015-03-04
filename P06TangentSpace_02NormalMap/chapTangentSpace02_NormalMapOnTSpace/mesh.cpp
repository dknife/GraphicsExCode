/*
 *  mesh.cpp
 *  ShaderProject
 *
 *  Created by young-min kang on 4/25/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "mesh.h"
#include <stdio.h>
#include <math.h>



void normalize(CVec3 &v) {
    float l = sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
    v.x /= l;
    v.y /= l;
    v.z /= l;
}

void cross(CVec3 u, CVec3 v, CVec3 &r) {
    r.x = u.y*v.z-v.y*u.z;
    r.y = u.z*v.x-v.z*u.x;
    r.z = u.x*v.y-v.x*u.y;
}



CMesh::CMesh()
: verts(0), normals(0), tangents(0), binormals(0), texCoords(0)
{}

void CMesh::initializeMemory(void) {
    if(verts)     delete[] verts;
    if(normals)   delete[] normals;
    if(tangents)  delete[] tangents;
    if(binormals) delete[] binormals;
    if(texCoords) delete[] texCoords;
    verts     = NULL;
    normals   = NULL;
    binormals = NULL;
    tangents  = NULL;
    texCoords = NULL;
}
void CMesh::createMesh(int nVRow, int nVCol) {
    initializeMemory();
    nVertices = nVRow * nVCol;
    nFaces    = (nVRow-1)*(nVCol-1)*2;
    verts = new CVec3[nVertices];
    normals = new CVec3[nVertices];
    binormals = new CVec3[nVertices];
    tangents = new CVec3[nVertices];
    texCoords = new CVec2[nVertices];
    
    faces = new CFace[nFaces];
    
    float xStep = 1.0/float(nVCol-1);
    float zStep = 1.0/float(nVRow-1);
    
    for (int i=0; i<nVertices; i++) {
        verts[i].x = xStep*(i%nVCol);
        
        verts[i].z = zStep*(i/nVCol);
        //verts[i].y = 0.05*sin(20.0f*(verts[i].x*verts[i].x+verts[i].z*verts[i].z));
        verts[i].y = 0.1*sin(10.0*verts[i].x)*cos(10.0*verts[i].z);
        
        texCoords[i].u = verts[i].x;
        texCoords[i].v = 1.0-verts[i].z;
    }
    
    int idx = 0;
    for (int i=0; i<nVRow-1; i++) {
        for (int j=0; j<nVCol-1; j++) {
            faces[idx].v1 = j+i*nVCol;
            faces[idx].v2 = j+(i+1)*nVCol;
            faces[idx].v3 = j+1+i*nVCol;
            idx++;
            faces[idx].v1 = j+(i+1)*nVCol;
            faces[idx].v2 = j+1+(i+1)*nVCol;
            faces[idx].v3 = j+1+i*nVCol;
            idx++;
        }
    }
    
    this->computeNormals();
}

void CMesh::computeNormals(void) {
    for (int i=0; i<nVertices; i++) {
        normals[i].x   = normals[i].y   = normals[i].z   = 0.0;
        binormals[i].x = binormals[i].y = binormals[i].z = 0.0;
        tangents[i].x  = tangents[i].y  = tangents[i].z  = 0.0;
    }
    
    CVec3 T, B, N;
    float v31, v21, u21, u31;
    float px21, px31, py21, py31, pz21, pz31;
    
    for (int i=0; i<nFaces; i++) {
        int v1, v2, v3;
        v1 = faces[i].v1;
        v2 = faces[i].v2;
        v3 = faces[i].v3;
        px21 = verts[v2].x-verts[v1].x;
        py21 = verts[v2].y-verts[v1].y;
        pz21 = verts[v2].z-verts[v1].z;
        px31 = verts[v3].x-verts[v1].x;
        py31 = verts[v3].y-verts[v1].y;
        pz31 = verts[v3].z-verts[v1].z;
        
        v31 = texCoords[v3].v-texCoords[v1].v;
        u31 = texCoords[v3].u-texCoords[v1].u;
        v21 = texCoords[v2].v-texCoords[v1].v;
        u21 = texCoords[v2].u-texCoords[v1].u;
        
        T.x = (v31*px21-v21*px31)/(u21*v31-v21*u31);
        T.y = (v31*py21-v21*py31)/(u21*v31-v21*u31);
        T.z = (v31*pz21-v21*pz31)/(u21*v31-v21*u31);
        
        B.x = (u31*px21-u21*px31)/(v21*u31-u21*v31);
        B.y = (u31*py21-u21*py31)/(v21*u31-u21*v31);
        B.z = (u31*pz21-u21*pz31)/(v21*u31-u21*v31);
        
        tangents[v1].x += T.x;
        tangents[v1].y += T.y;
        tangents[v1].z += T.z;
        
        tangents[v2].x += T.x;
        tangents[v2].y += T.y;
        tangents[v2].z += T.z;
        
        tangents[v3].x += T.x;
        tangents[v3].y += T.y;
        tangents[v3].z += T.z;
        
        binormals[v1].x += B.x;
        binormals[v1].y += B.y;
        binormals[v1].z += B.z;
        
        binormals[v2].x += B.x;
        binormals[v2].y += B.y;
        binormals[v2].z += B.z;
        
        binormals[v3].x += B.x;
        binormals[v3].y += B.y;
        binormals[v3].z += B.z;
    }
    
    for (int i=0; i<nVertices; i++) {
        normalize(tangents[i]);
        normalize(binormals[i]);
        
        cross(tangents[i], binormals[i], normals[i]);
        normalize(normals[i]);
        
        printf("%f %f %f\n", tangents[i].x, tangents[i].y, tangents[i].z);
        printf("%f %f %f\n", binormals[i].x, binormals[i].y, binormals[i].z);
        printf("%f %f %f\n", normals[i].x, normals[i].y, normals[i].z);
        
    }
    
    
}

void CMesh::drawTangentSpace(int idx) {
    glDisable(GL_TEXTURE_2D);
    float s = 0.025;
    glBegin(GL_LINES);
    for (int i=0; i<nVertices; i++) {
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(verts[i].x, verts[i].y, verts[i].z);
        glVertex3f(verts[i].x+tangents[i].x*s, verts[i].y+tangents[i].y*s, verts[i].z+tangents[i].z*s);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(verts[i].x, verts[i].y, verts[i].z);
        glVertex3f(verts[i].x+binormals[i].x*s, verts[i].y+binormals[i].y*s, verts[i].z+binormals[i].z*s);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(verts[i].x, verts[i].y, verts[i].z);
        glVertex3f(verts[i].x+normals[i].x*s, verts[i].y+normals[i].y*s, verts[i].z+normals[i].z*s);
    }
    glEnd();
    glEnable(GL_TEXTURE_2D);
}

void CMesh::drawWithGL(GLuint shaderProgram) {
    GLuint Tangent;
    GLuint Binormal;
    
    Tangent =  glGetAttribLocation(	shaderProgram, "Tangent");
    Binormal = glGetAttribLocation( shaderProgram, "Binormal");
    
    glBegin(GL_TRIANGLES);
    for (int i=0; i<nFaces; i++) {
        int idx1 = faces[i].v1;
        int idx2 = faces[i].v2;
        int idx3 = faces[i].v3;
        CVec3 v1 = verts[idx1];
        CVec3 v2 = verts[idx2];
        CVec3 v3 = verts[idx3];
        
        glNormal3f(normals[idx1].x, normals[idx1].y, normals[idx1].z);
        glVertexAttrib3f(Tangent, tangents[idx1].x, tangents[idx1].y, tangents[idx1].z);
        glVertexAttrib3f(Binormal, binormals[idx1].x, binormals[idx1].y, binormals[idx1].z);
        glTexCoord2f(texCoords[idx1].u, texCoords[idx1].v);
        glVertex3f(v1.x, v1.y, v1.z);
        
        glNormal3f(normals[idx2].x, normals[idx2].y, normals[idx2].z);
        glVertexAttrib3f(Tangent, tangents[idx2].x, tangents[idx2].y, tangents[idx2].z);
        glVertexAttrib3f(Binormal, binormals[idx2].x, binormals[idx2].y, binormals[idx2].z);
        glTexCoord2f(texCoords[idx2].u, texCoords[idx2].v);
        glVertex3f(v2.x, v2.y, v2.z);
        
        glNormal3f(normals[idx3].x, normals[idx3].y, normals[idx3].z);
        glVertexAttrib3f(Tangent, tangents[idx3].x, tangents[idx3].y, tangents[idx3].z);
        glVertexAttrib3f(Binormal, binormals[idx3].x, binormals[idx3].y, binormals[idx3].z);
        glTexCoord2f(texCoords[idx3].u, texCoords[idx3].v);
        glVertex3f(v3.x, v3.y, v3.z);
    }
    glEnd();
    
    glUseProgram(NULL);
    for (int i=0; i<nVertices; i++) {
        //drawTangentSpace(i);
    }
}
