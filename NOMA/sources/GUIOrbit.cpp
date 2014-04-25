/* 
 * File:   GUIOrbit.cpp
 * Author: laurasirventcollado
 * 
 * Created on 5 de marzo de 2014, 12:27
 */

#include "../headers/GUIOrbit.h"
#include "../headers/GraphicEngine.h"
#include <cmath>

#define DEG2RAD 3.14159/180;

GUIOrbit::GUIOrbit(float r, Vector3f c, float cutHeight) {

    radius = r;
    center = c;
    cutAngle = atan((cutHeight / 2) / radius) * 180 / 3.14159;
    displacement = 0;
}

GUIOrbit::GUIOrbit(const GUIOrbit& orig) {
}

GUIOrbit::~GUIOrbit() {
}

void GUIOrbit::draw() {

    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(1.5f);
    glBegin(GL_LINE_STRIP);

    int backgroundH = GraphicEngine::Instance()->getHeight() - 20;
    int backgroundW = GraphicEngine::Instance()->getWidth() - 20;

    for (int i = cutAngle + displacement; i < 360 - cutAngle + displacement; i++) {

        float degInRad = i*DEG2RAD;
        float posX = center.X + cos(degInRad) * radius;
        float posY = center.Y + sin(degInRad) * radius;

        glColor4f(color->r, color->g, color->b, color->a);
        
        if (posY < 20 || posY > backgroundH || posX < 20 || posX > backgroundW) {
            
            if (posY < 20)
                posY = 20;
            if (posY > backgroundH)
                posY = backgroundH;
            if (posX < 20)
                posX = 20;
            if (posX > backgroundW)
                posX = backgroundW;
            
            glColor4f(color->r, color->g, color->b, 0.0);
        }

        glVertex2f(posX, posY);
    }

    glEnd();
}

