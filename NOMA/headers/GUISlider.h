/* 
 * File:   GUISlider.h
 * Author: laurasirventcollado
 *
 * Created on 11 de marzo de 2014, 11:38
 */

#ifndef GUISLIDER_H
#define	GUISLIDER_H
#include "GUIElement.h"
#include "BaseGameEntity.h"

class GUISlider : public GUIElement {
public:
    GUISlider(int id, Vector3f upper, Vector3f lower, float min, float max, float start);
    GUISlider(const GUISlider& orig);
    void setDragging(int x, int y);
    float getValue(){ return value; }
    virtual ~GUISlider();
    void draw();
private:
    int ID;
    float minValue;
    float maxValue;
    float value;
    float length;
    float center;
    bool dragging;
    Vector3f upperCorner;
    Vector3f lowerCorner;
};

#endif	/* GUISLIDER_H */

