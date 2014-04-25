/* 
 * File:   GUIText.cpp
 * Author: laurasirventcollado
 * 
 * Created on 22 de marzo de 2014, 13:47
 */

#include "../headers/GUIText.h"
#include "../headers/TResourceManager.h"
#include "../headers/TAGConnector.h"
#include <string>

using namespace std;

GUIText::GUIText(Vector3f anchorPoint, Alignment a, float maxWidth, const wchar_t * text, std::string font, int size, Space s) {

    this->font = TResourceManager::Instance()->getResourceFont(font, size);
    this->maxWidth = maxWidth;
    this->text = (wchar_t*)text;
    drawBBox = false;
    bBoxColor = new RGBA(0, 0, 0, 0);
    space = s;

    color = new RGBA(1.0, 1.0, 1.0, 1.0);
    originalAnchorPoint = anchorPoint;
    alignment = a;

    bbox = this->font->getBoundingBox(this->text);

    switch (a) {
        case Left:
            upperCorner = originalAnchorPoint;
            lowerCorner = upperCorner + bbox;
            break;
        case Center:
            upperCorner.X = originalAnchorPoint.X - bbox.X / 2;
            upperCorner.Y = originalAnchorPoint.Y;
            lowerCorner = upperCorner + bbox;
            break;
        case Right:
            upperCorner.X = originalAnchorPoint.X - bbox.X;
            upperCorner.Y = originalAnchorPoint.Y;
            lowerCorner = upperCorner + bbox;
            break;
    }
    
    editable = false;
    onFocus = false;
}

GUIText::GUIText(const GUIText& orig) {
}

GUIText::~GUIText() {
}

bool GUIText::checkClick(int x, int y){
    if (editable && (x > upperCorner.X && x < lowerCorner.X) && (y > upperCorner.Y && y < lowerCorner.Y)) {
        return true;
    }
}

void GUIText::setText(const wchar_t* t, ...) {

    text = new wchar_t[256];

    va_list ap;
    va_start(ap, t);
    vswprintf(text, 256, t, ap);
    va_end(ap);
    recalculateCorners();

}

void GUIText::recalculateCorners() {

    bbox = this->font->getBoundingBox(text);
    switch (alignment) {
        case Left:
            upperCorner = originalAnchorPoint;
            lowerCorner = upperCorner + bbox;
            break;
        case Center:
            upperCorner.X = originalAnchorPoint.X - bbox.X / 2;
            upperCorner.Y = originalAnchorPoint.Y;
            lowerCorner = upperCorner + bbox;
            break;
        case Right:
            upperCorner.X = originalAnchorPoint.X - bbox.X;
            upperCorner.Y = originalAnchorPoint.Y;
            lowerCorner = upperCorner + bbox;
            break;
    }
}

void GUIText::draw() {

    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_LINE_SMOOTH);

    if (space == TwoD) {

        if (drawBBox) {
            glColor4f(bBoxColor->r, bBoxColor->g, bBoxColor->b, bBoxColor->a);
            glBegin(GL_QUADS);
            glVertex2i(upperCorner.X - 5, upperCorner.Y - 5);
            glVertex2i(upperCorner.X - 5, lowerCorner.Y + 5);
            glVertex2i(lowerCorner.X + 5, lowerCorner.Y + 5);
            glVertex2i(lowerCorner.X + 5, upperCorner.Y - 5);
            glEnd();
        }
        
        glColor4f(color->r, color->g, color->b, color->a);
        glRasterPos2f(upperCorner.X, lowerCorner.Y);
        
    } 
    
    else if (space == ThreeD) {

        Vector3f screen = getScreenCoordinates(point3D);
        
        if(bbox.X > maxWidth){
            
        }
        else{
            
        }

        if (drawBBox) {
            glColor4f(bBoxColor->r, bBoxColor->g, bBoxColor->b, bBoxColor->a);
            glBegin(GL_QUADS);
            glVertex2i(screen.X - bbox.X / 2 - 5, screen.Y - bbox.Y - 5);
            glVertex2i(screen.X - bbox.X / 2 - 5, screen.Y + bbox.Y + 2.5);
            glVertex2i(screen.X + bbox.X / 2 + 5, screen.Y + bbox.Y + 2.5);
            glVertex2i(screen.X + bbox.X / 2 + 5, screen.Y - bbox.Y - 5);
            glEnd();
        }
        
        glColor4f(color->r, color->g, color->b, color->a);
        glRasterPos2f(screen.X - bbox.X / 2, screen.Y);
    }
    font->print(text);


}

