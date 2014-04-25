/* 
 * File:   Compass.h
 * Author: laurasirventcollado
 *
 * Created on 9 de marzo de 2014, 17:15
 */

#ifndef HUD_H
#define	HUD_H

#include "GUIElement.h"
#include "TResourceFont.h"
#include <iostream>
#include <cmath>

class HUD : public GUIElement {
public:
    HUD(float r);
    HUD(const HUD& orig);
    virtual ~HUD();
    void draw();
    void setRotation(float r){ rotation = r; }
    
private:
    int screenWidth;
    float rotation;
    TResourceFont *font;
    std::vector<const wchar_t *> texts;
};

#endif	/* COMPASS_H */

