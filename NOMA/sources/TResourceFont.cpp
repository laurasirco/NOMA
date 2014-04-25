/* 
 * File:   TResourceFont.cpp
 * Author: laurasirventcollado
 * 
 * Created on 2 de marzo de 2014, 1:15
 */

#include "../headers/TResourceFont.h"
#include "../headers/BaseGameEntity.h"

TResourceFont::TResourceFont() {
}

TResourceFont::TResourceFont(const TResourceFont& orig) {
}

TResourceFont::~TResourceFont() {
}

bool TResourceFont::load(char* filename, int size){
    
    font.init(filename, size);
    this->size = size;
    return true;
}

void TResourceFont::print(wchar_t *text){
    
    freetype_mod::print(font, text);
}

Vector3f TResourceFont::getBoundingBox(wchar_t *text){
    
    Vector3f bbox;
    
    bbox.X = freetype_mod::getWidth(font, text);
    bbox.Y = freetype_mod::getHeight(font, text);

    return bbox;
}

