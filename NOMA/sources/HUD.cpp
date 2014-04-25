/* 
 * File:   Compass.cpp
 * Author: laurasirventcollado
 * 
 * Created on 9 de marzo de 2014, 17:15
 */

#include "../headers/HUD.h"
#include "../headers/GraphicEngine.h"

using namespace std;

HUD::HUD(float r) {
    rotation = r;
    color = new RGBA(1.0, 1.0, 1.0, 1.0);
    font = TResourceManager::Instance()->getResourceFont("Nexa Light.otf", 12);
    texts.push_back(L"E");
    texts.push_back(L"N");
    texts.push_back(L"O");
    texts.push_back(L"S");
    texts.push_back(L"E");
    texts.push_back(L"N");
    texts.push_back(L"O");
    texts.push_back(L"S");
    texts.push_back(L"E");
}

HUD::HUD(const HUD& orig) {
}

HUD::~HUD() {
}

void HUD::draw() {

    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glColor4f(color->r, color->g, color->b, color->a);
    glLineWidth(2.0f);

    int screenWidth2 = GraphicEngine::Instance()->getWidth() / 2;

    //Horizontal line
    glBegin(GL_LINE_STRIP);
    glColor4f(color->r, color->g, color->b, 0.0);
    glVertex2i(screenWidth2 - 100, 40);
    glColor4f(color->r, color->g, color->b, 1.0);
    glVertex2i(screenWidth2 - 0, 40);
    glVertex2i(screenWidth2 + 0, 40);
    glColor4f(color->r, color->g, color->b, 0.0);
    glVertex2i(screenWidth2 + 100, 40);
    glEnd();

    //EAST COAST
    int c = 0;
    for (int i = -360; i <= 360; i += 90) {
        
        int position = screenWidth2 + rotation + i;
        
        
        if (position < screenWidth2 + 100 && position > screenWidth2 - 100) {
            
            glBegin(GL_LINES);
            if(position >= screenWidth2 + 50){
                float alpha = 1-(((position)-(screenWidth2 + 50))*0.03);
                glColor4f(color->r, color->g, color->b, alpha);
            }
            else if(position <= screenWidth2 - 50){
                float alpha = 1-(((screenWidth2 - 50)-(position))*0.03);
                glColor4f(color->r, color->g, color->b, alpha);
            }
            else
                glColor4f(color->r, color->g, color->b, 1.0);
            
            glVertex2i(position, 30);
            glVertex2i(position, 50);
            glEnd();

            Vector3f bbox = this->font->getBoundingBox((wchar_t *)texts[c]);
            glRasterPos2f(position - bbox.X / 2, 20);
            font->print((wchar_t*)texts[c]);
        }
        c++;
    }

}

