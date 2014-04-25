/* 
 * File:   GUISlider.cpp
 * Author: laurasirventcollado
 * 
 * Created on 11 de marzo de 2014, 11:38
 */

#include "../headers/GUISlider.h"
#include <iostream>
using namespace std;

GUISlider::GUISlider(int id, Vector3f upper, Vector3f lower, float min, float max, float start) {
    ID = id;
    upperCorner = upper;
    lowerCorner = lower;
    minValue = min;
    maxValue = max;
    value = start;
    color = new RGBA(1.0, 1.0, 1.0, 1.0);
    length = lowerCorner.X - upperCorner.X;
    dragging = false;
    center = upperCorner.X + (value * length) / maxValue;
}

GUISlider::GUISlider(const GUISlider& orig) {
}

GUISlider::~GUISlider() {
}

void GUISlider::setDragging(int x, int y) {

    
    if (y >= upperCorner.Y - 10 && y <= lowerCorner.Y + 10 && x > upperCorner.X && x < lowerCorner.X) {
        
        dragging = true;     
        center = x;
        
    } else {
        dragging = false;
    }
    if(center > lowerCorner.X - 5) { center = lowerCorner.X - 5;}
    if(center < upperCorner.X + 5){ center = upperCorner.X;}

    value = (maxValue * (center - upperCorner.X)) / length;
}

void GUISlider::draw() {

    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(2.0f);

    glBegin(GL_LINE_STRIP);
    glColor4f(color->r, color->g, color->b, 0.7);
    glVertex2i(upperCorner.X, upperCorner.Y);
    glVertex2i(center + 5, upperCorner.Y);
    glColor4f(color->r, color->g, color->b, 0.2);
    glVertex2i(center + 5, upperCorner.Y);
    glVertex2i(lowerCorner.X, lowerCorner.Y);
    glEnd();

    glColor4f(color->r, color->g, color->b, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(center - 5, upperCorner.Y - 10);
    glVertex2i(center - 5, lowerCorner.Y + 10);
    glVertex2i(center + 5, lowerCorner.Y + 10);
    glVertex2i(center + 5, upperCorner.Y - 10);
    glEnd();

}

