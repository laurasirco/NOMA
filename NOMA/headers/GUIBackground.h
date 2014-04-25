/* 
 * File:   GUIBackground.h
 * Author: laurasirventcollado
 *
 * Created on 5 de marzo de 2014, 11:38
 */

#ifndef GUIBACKGROUND_H
#define	GUIBACKGROUND_H

#include "GUIElement.h"
#include "BaseGameEntity.h"
#include "../SOIL/include/SOIL.h"

class GUIBackground : public GUIElement {
public:
    GUIBackground(Vector3f upper, Vector3f lower, RGBA * color);
    GUIBackground(Vector3f upper, Vector3f lower, RGBA * uColor, RGBA * lColor);
    GUIBackground(Vector3f upper, Vector3f lower, char * backgroundImage);
    GUIBackground(const GUIBackground& orig);
    virtual ~GUIBackground();
    void draw();
private:
    Vector3f upperCorner;
    Vector3f lowerCorner;
    GLuint texture;
    int repeat;
    
    RGBA * upperColor;
    RGBA * lowerColor;
};

#endif	/* GUIBACKGROUND_H */

