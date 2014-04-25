/* 
 * File:   TResourceFont.h
 * Author: laurasirventcollado
 *
 * Created on 2 de marzo de 2014, 1:15
 */

#ifndef TRESOURCEFONT_H
#define	TRESOURCEFONT_H

#include "TResource.h"
#include "Freetype.h"
#include "BaseGameEntity.h"
#include <iostream>

class TResourceFont : public TResource {
public:
    TResourceFont();
    TResourceFont(const TResourceFont& orig);
    virtual ~TResourceFont();
    bool load(char *filename, int size);
    void print(wchar_t *text);
    Vector3f getBoundingBox(wchar_t *text);
    int getSize(){ return size; }
private:
    freetype_mod::font_data font;
    int size;
};

#endif	/* TRESOURCEFONT_H */

