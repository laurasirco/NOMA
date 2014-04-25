/* 
 * File:   TShadowMapFBO.cpp
 * Author: laurasirventcollado
 * 
 * Created on 9 de abril de 2014, 11:40
 */

#include "../headers/TShadowMap.h"
#include <stdio.h>

TShadowMapFBO::TShadowMapFBO() {
    fboId = 0;
    depthTextureId = 0;
    shader = new TShaderProgram();
}

TShadowMapFBO::TShadowMapFBO(const TShadowMapFBO& orig) {
}

TShadowMapFBO::~TShadowMapFBO() {
    if (fboId != 0) {
        glDeleteFramebuffers(1, &fboId);
    }

    if (depthTextureId != 0) {
        glDeleteTextures(1, &depthTextureId);
    }
}

void TShadowMapFBO::Init(unsigned int WindowWidth, unsigned int WindowHeight) {
    int shadowMapWidth = WindowWidth;
    int shadowMapHeight = WindowHeight;

    //GLfloat borderColor[4] = {0,0,0,0};

    GLenum FBOstatus;

    // Try to use a texture depth component
    glGenTextures(1, &depthTextureId);
    glBindTexture(GL_TEXTURE_2D, depthTextureId);

    // GL_LINEAR does not make sense for depth texture. However, next tutorial shows usage of GL_LINEAR and PCF
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Remove artefact on the edges of the shadowmap
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    //glTexParameterfv( GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor );

    // No need to force GL_DEPTH_COMPONENT24, drivers usually give you the max precision if available 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

    // create a framebuffer object
    glGenFramebuffersEXT(1, &fboId);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboId);

    // attach the texture to FBO depth attachment point
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, depthTextureId, 0);

    // Instruct openGL that we won't bind a color texture with the currently binded FBO
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);


    // check FBO status
    FBOstatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
    if (FBOstatus != GL_FRAMEBUFFER_COMPLETE_EXT)
        printf("GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO\n");

    // switch back to window-system-provided framebuffer
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    
    //Load shader
    shader = new TShaderProgram();
    //shader->Load((char *)"VertexShader.c", (char *)"FragmentShader.c"); 

    //shadowMapUniform = glGetUniformLocation(shader->program(), "ShadowMap");
    //textureUniform = glGetUniformLocation(shader->program(), "Texture");
    

}

void TShadowMapFBO::BindForWriting() {
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboId);
    glDrawBuffers(0, NULL); 
    glReadBuffer(GL_NONE);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, depthTextureId, 0);
}

void TShadowMapFBO::BindForReading(GLenum TextureUnit) {
    glActiveTexture(GL_TEXTURE0 + TextureUnit); 
    glBindTexture(GL_TEXTURE_2D, depthTextureId);
}


