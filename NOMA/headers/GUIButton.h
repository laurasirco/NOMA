/* 
 * File:   GUIButton.h
 * Author: laurasirventcollado
 *
 * Created on 1 de marzo de 2014, 14:12
 */

#ifndef GUIBUTTON_H
#define	GUIBUTTON_H
#include "GUIElement.h"
#include <iostream>
#include <string>
#include "BaseGameEntity.h"
#include "TResourceFont.h"

class GUIButton : public GUIElement {
public:
    
    enum Type{ Text, LeftArrow, RightArrow };
    enum Alignment { Left, Center, Right };
    
    GUIButton(int id, Vector3f position, Alignment a, const wchar_t *label, bool enabled, std::string font, int size);
    GUIButton(const GUIButton& orig);
    GUIButton(int id, Vector3f upper, Vector3f lower, Type t, bool enabled);
    virtual ~GUIButton();
    void draw();
    bool checkClick(int x, int y);
    void setHover(int x, int y);
    void setEnabled(bool e){ enabled = e; }
    void rotate(Vector3f center, float angle, float radius);
    Vector3f getBoundingBox();
    void setCenter(Vector3f pos){ upperCorner.X = pos.X; lowerCorner.Y = pos.Y; }
    Vector3f getOriginalCenter(){ return originalCenter; }
    void incrementRotationAngle(float i){ rotAngle+=i; }
    float getRotationAngle(){ return rotAngle; }
    void setDrawBoundingBox(bool d){ dBBox = d; }
    void setBoundingBoxColor(RGBA * c){ bboxColor = c; }
    void setHoverColor(RGBA *c){ hoverColor = c; }
    void setDisabledColor(RGBA * c){ disabledColor = c; }
    
public:
    TResourceFont *font;
    const wchar_t *label;
    Vector3f upperCorner;
    Vector3f lowerCorner;
    Vector3f originalCenter;
    bool enabled;
    bool hover;
    Type type;
    float rotAngle;
    bool dBBox;
    
    RGBA * hoverColor;
    RGBA * disabledColor;
    RGBA * bboxColor;
};

#endif	/* GUIBUTTON_H */

