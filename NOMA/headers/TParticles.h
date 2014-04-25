/* 
 * File:   TParticles.h
 * Author: iMac
 *
 * Created on 18 de abril de 2014, 12:59
 */

#ifndef TPARTICLES_H
#define	TPARTICLES_H
#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "TResourceTexture.h"



typedef struct {
    float Position[3];
    float TexCoord[2];
    float Color[4];
} Vertex;

class TParticles {
public:
    TParticles();
    TParticles(const TParticles& orig);
    virtual ~TParticles();
    
    void prepareOpengl();
    void drawTriangleStripBillBoard();
    void drawPointSpriteBillboard();
    void drawRect();
private:

};

#endif	/* TPARTICLES_H */

