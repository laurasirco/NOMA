/* 
 * File:   TFBO.h
 * Author: laurasirventcollado
 *
 * Created on 10 de abril de 2014, 18:40
 */

#ifndef TFBO_H
#define	TFBO_H
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

class TFBO {
public:
        
    TFBO();
    TFBO(const TFBO& orig);
    virtual ~TFBO();
    
    void Init(unsigned int Width, unsigned int Height);
    void BindForWriting();
    void BindForReading(GLenum TextureUnit);
    
    GLuint getFBOId(){ return fboId; }
    GLuint getTextureId(){ return textureId; }
private:
    GLuint fboId;
    GLuint depthId;
    GLuint textureId;
};

#endif	/* TFBO_H */

