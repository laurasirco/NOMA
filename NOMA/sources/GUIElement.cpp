/* 
 * File:   GUIElement.cpp
 * Author: laurasirventcollado
 * 
 * Created on 1 de marzo de 2014, 14:07
 */

#include "../headers/GUIElement.h"
#include "../headers/TAGConnector.h"

GUIElement::GUIElement() {
}

GUIElement::GUIElement(const GUIElement& orig) {
}

GUIElement::~GUIElement() {
}

Vector3f GUIElement::getScreenCoordinates(Vector3f position){
    
    GLdouble * modelview = TAGConnector::getModelviewMatrix();
    GLdouble  * projection = TAGConnector::getProjectionMatrix();
    GLint * viewport = TAGConnector::getViewport();

    double tx, ty, tz;

    gluProject(position.X, position.Y, position.Z, modelview, projection, viewport, &tx, &ty, &tz);
    
    return Vector3f(tx,viewport[3]-ty,tz);
}
