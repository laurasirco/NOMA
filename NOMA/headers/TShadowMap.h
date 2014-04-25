/* 
 * File:   TShadowMap.h
 * Author: laurasirventcollado
 *
 * Created on 9 de abril de 2014, 11:40
 */

#ifndef TSHADOWMAPFBO_H
#define	TSHADOWMAPFBO_H
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "Matrices.h"
#include "TShaderProgram.h"

class TShadowMapFBO {
public:
    TShadowMapFBO();
    TShadowMapFBO(const TShadowMapFBO& orig);
    virtual ~TShadowMapFBO();
    
    void Init(unsigned int WindowWidth, unsigned int WindowHeight);
    void BindForWriting();
    void BindForReading(GLenum TextureUnit);
    
    GLuint getFBOId(){ return fboId; }
    GLuint getDepthTextureId(){ return depthTextureId; }
    GLuint getShader(){ return shader->program(); }
    TShaderProgram * getShaderObject(){ return shader; }
    GLuint getShadowMapUniform(){ return shadowMapUniform; }
    GLuint getTextureUniform(){ return textureUniform; }
    
private:
    GLuint fboId;
    GLuint depthTextureId;
    
    GLuint shadowMapUniform;
    GLuint textureUniform;

    TShaderProgram * shader;
};


#endif	/* TSHADOWMAPFBO_H */

