/* 
 * File:   TFBO.cpp
 * Author: laurasirventcollado
 * 
 * Created on 10 de abril de 2014, 18:40
 */

#include "../headers/TFBO.h"
#include <stdio.h>

TFBO::TFBO() {
    fboId = 0;
    textureId = 0;
}

TFBO::TFBO(const TFBO& orig) {
}

TFBO::~TFBO() {
    if (fboId != 0) {
        glDeleteFramebuffers(1, &fboId);
    }

    if (textureId != 0) {
        glDeleteTextures(1, &textureId);
    }
}

void TFBO::Init(unsigned int Width, unsigned int Height) {

    GLenum FBOstatus;

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glBindTexture(GL_TEXTURE_2D, 0);

    // create a framebuffer object
    glGenFramebuffersEXT(1, &fboId);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboId);

    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);

    glGenRenderbuffersEXT(1, &depthId);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depthId);
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, Width, Height);
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depthId);


    // check FBO status
    FBOstatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
    if (FBOstatus != GL_FRAMEBUFFER_COMPLETE_EXT)
        printf("GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO\n");

    // switch back to window-system-provided framebuffer
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

}

void TFBO::BindForWriting() {
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboId);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, textureId, 0);
}

void TFBO::BindForReading(GLenum TextureUnit) {

    glActiveTextureARB(GL_TEXTURE0 + TextureUnit);
    glBindTexture(GL_TEXTURE_2D, textureId);

}
