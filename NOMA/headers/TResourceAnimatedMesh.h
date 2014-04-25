/* 
 * File:   TResourceAnimatedMesh.h
 * Author: MAC
 *
 * Created on 12 de marzo de 2014, 16:16
 */

#ifndef TRESOURCEANIMATEDMESH_H
#define	TRESOURCEANIMATEDMESH_H
#include "TResource.h"
#include <iostream>
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "TResourceMesh.h"
#include <vector>

class TResourceAnimatedMesh : public TResource {
public:
    // constructor/destructor
    TResourceAnimatedMesh(void);
    ~TResourceAnimatedMesh(void);
    bool load(char *filename, TResourceTexture* texture);
    void draw();
    
    bool setFrame(float f);
    int getNumberOfFrames(){ return animation.size(); }
private:
    std::vector<TResourceMesh *> animation;
    float frame;
    
};

#endif 