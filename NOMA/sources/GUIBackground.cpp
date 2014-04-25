/* 
 * File:   GUIBackground.cpp
 * Author: laurasirventcollado
 * 
 * Created on 5 de marzo de 2014, 11:38
 */

#include "../headers/GUIBackground.h"

GUIBackground::GUIBackground(Vector3f upper, Vector3f lower, RGBA * color) {
    upperCorner = upper;
    lowerCorner = lower;
    this->color = color;
    upperColor = color;
    lowerColor = color;
    texture = 0;
}

GUIBackground::GUIBackground(Vector3f upper, Vector3f lower, RGBA * uColor, RGBA * lColor) {
    upperCorner = upper;
    lowerCorner = lower;
    this->color = color;
    upperColor = uColor;
    lowerColor = lColor;
    texture = 0;
}

GUIBackground::GUIBackground(Vector3f upper, Vector3f lower, char* backgroundImage) {
    upperCorner = upper;
    lowerCorner = lower;
    glGenTextures(1, &texture);
    texture = SOIL_load_OGL_texture
            (
            backgroundImage,
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y
            );
    repeat = 1;
    color = new RGBA(0, 0, 0, 0);
}

GUIBackground::GUIBackground(const GUIBackground& orig) {
}

GUIBackground::~GUIBackground() {
}

void GUIBackground::draw() {

    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_QUADS);

    glColor4f(upperColor->r, upperColor->g, upperColor->b, upperColor->a);
    glVertex2i(upperCorner.X, upperCorner.Y);
    glColor4f(lowerColor->r, lowerColor->g, lowerColor->b, lowerColor->a);
    glVertex2i(upperCorner.X, lowerCorner.Y);

    glColor4f(lowerColor->r, lowerColor->g, lowerColor->b, lowerColor->a);
    glVertex2i(lowerCorner.X, lowerCorner.Y);
    glColor4f(upperColor->r, upperColor->g, upperColor->b, upperColor->a);
    glVertex2i(lowerCorner.X, upperCorner.Y);
    glEnd();

}

