/* 
 * File:   GUIButton.cpp
 * Author: laurasirventcollado
 * 
 * Created on 1 de marzo de 2014, 14:12
 */

#include "../headers/GUIButton.h"
#include "../headers/TResourceManager.h"

#define DEG2RAD 3.14159/180;

GUIButton::GUIButton(int id, Vector3f position, Alignment a, const wchar_t *label, bool enabled, std::string font, int size) {
    ID = id;
    this->font = TResourceManager::Instance()->getResourceFont(font, size);
    this->label = label;
    this->enabled = enabled;
    hover = false;

    Vector3f bbox = this->font->getBoundingBox((wchar_t *)label);
    if (a == Left) {
        upperCorner = position;
        lowerCorner = upperCorner + bbox;
    } else if (a == Center) {
        upperCorner.X = position.X - bbox.X / 2;
        upperCorner.Y = position.Y - bbox.Y / 2;
        lowerCorner = upperCorner + bbox;
        originalCenter = upperCorner;
    } else if (a == Right) {
        upperCorner.X = position.X - bbox.X;
        upperCorner.Y = position.Y;
        lowerCorner = upperCorner + bbox;
    }

    type = Text;
    color = new RGBA(0.95, 0.95, 0.95, 1.0);
    hoverColor = new RGBA(0.5, 0.5, 0.5, 1.0);
    disabledColor = new RGBA(0.5, 0.5, 0.5, 1.0);
    bboxColor = new RGBA();
    rotAngle = 0;
}

GUIButton::GUIButton(int id, Vector3f upper, Vector3f lower, Type t, bool enabled) {
    ID = id;
    upperCorner = upper;
    lowerCorner = lower;
    type = t;
    this->enabled = enabled;
    color = new RGBA(1.0, 1.0, 1.0, 1.0);
}

GUIButton::GUIButton(const GUIButton& orig) {
}

GUIButton::~GUIButton() {
}

Vector3f GUIButton::getBoundingBox() {
    Vector3f bbox = this->font->getBoundingBox((wchar_t *)label);
    return bbox;
}

bool GUIButton::checkClick(int x, int y) {

    if (type != LeftArrow && type != RightArrow) {
        if (enabled && (x > upperCorner.X && x < lowerCorner.X) && (y > upperCorner.Y && y < lowerCorner.Y)) {
            return true;
        }
    }
    else{
        if (enabled && (x > upperCorner.X - 10 && x < lowerCorner.X + 10) && (y > upperCorner.Y - 10 && y < lowerCorner.Y + 10)) {
            return true;
        }
    }

    return false;
}

void GUIButton::setHover(int x, int y) {

    if (enabled && x > upperCorner.X && x < lowerCorner.X && y > upperCorner.Y && y < lowerCorner.Y)
        hover = true;
    else
        hover = false;
}

void GUIButton::rotate(Vector3f center, float angle, float radius) {

    rotAngle = angle;

    float radians = angle*DEG2RAD;

    float centerX = center.X + radius * cos(radians);
    float centerY = center.Y + radius * sin(radians);

    Vector3f bbox = this->font->getBoundingBox((wchar_t *)label);
    upperCorner.X = centerX - bbox.X / 2;
    upperCorner.Y = centerY - bbox.Y / 2;
    lowerCorner = upperCorner + bbox;

}

void GUIButton::draw() {

    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //DRAW BOUNDING BOX
    
    /*glDisable(GL_LINE_SMOOTH);
    glColor4f(color.r, color.g, color.b, color.a);
    glLineWidth(0.5f);

    glBegin(GL_LINE_LOOP);
    glVertex2i(upperCorner.X, upperCorner.Y);
    glVertex2i(upperCorner.X, lowerCorner.Y);
    glVertex2i(lowerCorner.X, lowerCorner.Y);
    glVertex2i(lowerCorner.X, upperCorner.Y);
    glEnd();*/

    switch (type) {
        case LeftArrow:

            glEnable(GL_LINE_SMOOTH);
            glColor4f(color->r, color->g, color->b, color->a);
            glLineWidth(1.0f);

            glBegin(GL_LINE_STRIP);
            glVertex2i(upperCorner.X, lowerCorner.Y);
            glVertex2i(lowerCorner.X, (upperCorner.Y + lowerCorner.Y)*0.5f);
            glVertex2i(upperCorner.X, upperCorner.Y);
            glEnd();

            break;

        case RightArrow:

            glEnable(GL_LINE_SMOOTH);
            glColor4f(color->r, color->g, color->b, color->a);
            glLineWidth(1.0f);

            glBegin(GL_LINE_STRIP);
            glVertex2i(lowerCorner.X, upperCorner.Y);
            glVertex2i(upperCorner.X, (upperCorner.Y + lowerCorner.Y)*0.5f);
            glVertex2i(lowerCorner.X, lowerCorner.Y);
            glEnd();
            break;

        case Text:

            glDisable(GL_LINE_SMOOTH);

            if(dBBox){
                glColor4f(bboxColor->r, bboxColor->g, bboxColor->b, bboxColor->a);
                glBegin(GL_QUADS);
                    glVertex2i(upperCorner.X - 5, upperCorner.Y - 5);
                    glVertex2i(upperCorner.X - 5, lowerCorner.Y + 5);
                    glVertex2i(lowerCorner.X + 5, lowerCorner.Y + 5);
                    glVertex2i(lowerCorner.X + 5, upperCorner.Y - 5);
                glEnd();
            }

            glColor4f(color->r, color->g, color->b, color->a);
            glLineWidth(0.5f);
            
            if (hover)
                glColor4f(hoverColor->r, hoverColor->g, hoverColor->b, hoverColor->a);
            else if (!enabled)
                glColor4f(disabledColor->r, disabledColor->g, disabledColor->b, disabledColor->a);
            else
                glColor4f(color->r, color->g, color->b, color->a);

            glRasterPos2f(upperCorner.X, lowerCorner.Y);
            font->print((wchar_t *)label);

            /*    int len, i;
             * len = (int) strlen(label);
            for (i = 0; i < len; i++) {
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, label[i]);
            }*/
            break;
        default:
            break;
    }


}

