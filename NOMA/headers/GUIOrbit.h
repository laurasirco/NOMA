/* 
 * File:   GUIOrbit.h
 * Author: laurasirventcollado
 *
 * Created on 5 de marzo de 2014, 12:27
 */

#ifndef GUIORBIT_H
#define	GUIORBIT_H
#include "BaseGameEntity.h"
#include "GUIElement.h"

class GUIOrbit : public GUIElement {
public:
    GUIOrbit(float r, Vector3f c, float cutHeight);
    GUIOrbit(const GUIOrbit& orig);
    virtual ~GUIOrbit();
    void draw();
    float getRadius(){ return radius; }
    void setDisplacement(float d){ displacement = d; }
    void incrementDisplacement(float i){ displacement += i; }
private:
    float radius;
    Vector3f upperCorner;
    Vector3f center;
    float cutAngle;
    float displacement;
};

#endif	/* GUIORBIT_H */

