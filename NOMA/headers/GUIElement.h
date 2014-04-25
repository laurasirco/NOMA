/* 
 * File:   GUIElement.h
 * Author: laurasirventcollado
 *
 * Created on 1 de marzo de 2014, 14:07
 */

#ifndef GUIELEMENT_H
#define	GUIELEMENT_H
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "BaseGameEntity.h"

struct RGBA{
    float r;
    float g;
    float b;
    float a;
    RGBA(float r=0, float g=0, float b=0, float a=0) : r(r), g(g), b(b), a(a) {}
};

class GUIElement {
public:
    GUIElement();
    GUIElement(const GUIElement& orig);
    virtual ~GUIElement();
    virtual void draw() = 0;
    int getID(){ return ID; }
    void setID(int i){ ID = i; }
    void setColor(RGBA * c){ color = c; }
    Vector3f getScreenCoordinates(Vector3f position);
protected:
    int ID;
    RGBA * color;
};

#endif	/* GUIELEMENT_H */

