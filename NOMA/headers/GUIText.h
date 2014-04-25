/* 
 * File:   GUIText.h
 * Author: laurasirventcollado
 *
 * Created on 22 de marzo de 2014, 13:47
 */

#ifndef GUITEXT_H
#define	GUITEXT_H

#include "BaseGameEntity.h"
#include "GUIElement.h"
#include "TResourceFont.h"
#include <iostream>

class GUIText : public GUIElement {
public:
    
    enum Alignment { Left, Center, Right };
    enum Space { TwoD, ThreeD };
    
    GUIText(Vector3f anchorPoint, Alignment a, float maxWidth, const wchar_t * text, std::string font, int size, Space s = TwoD);
    GUIText(const GUIText& orig);
    virtual ~GUIText();
    void setText(const wchar_t * t, ...);
    void recalculateCorners();
    void draw();
    void setDrawBBox(bool s){ drawBBox = s; }
    void setSpace(Space s){ space = s; }
    void set3DPoint(Vector3f pos){ point3D = pos;  }
    void setBBoxColor(RGBA * c){ bBoxColor = c; }
    
    bool isOnFocus(){ return onFocus; }
    void setEditable(bool e){ editable = e; }
    bool isEditable(){ return editable; }
    bool checkClick(int x, int y);
private:
    TResourceFont *font;
    wchar_t * text;
    Vector3f upperCorner;
    Vector3f lowerCorner;
    Vector3f originalAnchorPoint;
    Vector3f bbox;
    Alignment alignment;
    float maxWidth;
    bool drawBBox;
    RGBA * bBoxColor;
    Space space;
    
    Vector3f point3D;
    
    bool editable;
    bool onFocus;
};

#endif	/* GUITEXT_H */

