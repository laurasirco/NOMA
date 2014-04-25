/* 
 * File:   TResourceTexture.cpp
 * Author: iMac
 * 
 * Created on 25 de febrero de 2014, 11:37
 */

#include "../headers/TResourceTexture.h"
#include <iostream>

using namespace std;

TResourceTexture::TResourceTexture() {
    name = "";
}

TResourceTexture::TResourceTexture(const TResourceTexture& orig) {
}

TResourceTexture::~TResourceTexture() {
    
}

bool TResourceTexture::loadTexture(char* filename) {
    
    glGenTextures(1, &texture);
    texture = SOIL_load_OGL_texture
            (
            filename,
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y
            );
    repeat = 1;
    //glBindTexture(GL_TEXTURE_2D, texture);


    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


}

void TResourceTexture::draw() {
    //glBindTexture(GL_TEXTURE_2D, texture);
}