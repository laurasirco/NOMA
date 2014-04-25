/* 
 * File:   TResourceTexture.h
 * Author: iMac
 *
 * Created on 25 de febrero de 2014, 11:37
 */

#ifndef TRESOURCETEXTURE_H
#define	TRESOURCETEXTURE_H
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "../SOIL/include/SOIL.h"
#include "TResource.h"

class TResourceTexture : public TResource {
public:
    TResourceTexture();
    TResourceTexture(const TResourceTexture& orig);
    virtual ~TResourceTexture();
    bool loadTexture(char *filename);
    void setRepeat(int r){ repeat = r; }
    int getRepeat(){ return repeat; }
    void draw();
    GLuint getTexture() { return texture;}
private:
    GLuint texture;
    int repeat;
};

#endif	/* TRESOURCETEXTURE_H */

