/* 
 * File:   TResourceMesh.h
 * Author: iMac
 *
 * Created on 17 de febrero de 2014, 22:24
 */

#ifndef TRESOURCEMESH_H
#define	TRESOURCEMESH_H
#include <iostream>
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <vector>
#include <string>
#include "BaseGameEntity.h"
#include "TResourceTexture.h"
#include "TResource.h"

#include "GUIElement.h" //RGBA struct

typedef struct {
    int v1, v2, v3;
    int vn1, vn2, vn3;
    int vt1, vt2, vt3;
}
Face;


class TResourceMesh : public TResource {
public:
    TResourceMesh();
    TResourceMesh(const TResourceMesh& orig);
    virtual ~TResourceMesh();

    void setTexture(TResourceTexture *t) {
        texture = t;
    }
    
    void setNormalsMap(TResourceTexture *n){
        normalsMap = n;
    }

    void setRepeatTexture(int r) {
        texture->setRepeat(r);
    }
    
    void setRepeatNormalsMap(int r){
        normalsMap->setRepeat(r);
    }
    
    bool load(char *filename);
    void draw();

    int getNumberOfFaces() {
        return faces.size();
    }
    vector<Vector3f> getTriangle(int index);

    void setColor(RGBA * c) {
        color = c;
    }
    
private:
    vector<Vector3f> vertices;
    vector<Vector3f> normals;
    vector<Face> faces;
    vector<Vector3f> UVs;
    
    TResourceTexture *texture;
    TResourceTexture *normalsMap;

    void parseLine(char *line);

    void parseVertex(char *line);
    void parseNormal(char *line);
    void parseFace(char *line);
    void parseUV(char *line);

    RGBA * color;
    
};

#endif	/* TRESOURCEMESH_H */

