/* 
 * File:   TShaderProgram.h
 * Author: Laura Sirvent Collado
 *
 * Created on 14 de marzo de 2014, 19:45
 */

#ifndef TSHADERPROGRAM_H
#define	TSHADERPROGRAM_H
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <iostream>
#include <stdio.h>

class TShaderProgram {
public:
    GLuint *UniformLocations;
    GLuint *AttribLocations;
    TShaderProgram();
    TShaderProgram(const TShaderProgram& orig);
    virtual ~TShaderProgram();
    operator GLuint ();
    bool Load(char *VertexShaderFileName, char *FragmentShaderFileName);
    bool Link();
    void Destroy();
    GLuint program(){ return Program; }
private:
protected:
    GLuint VertexShader;
    GLuint FragmentShader;
    GLuint Program;
    
    GLuint LoadShader(char *FileName, GLenum Type);
    void setDefaults();

};

#endif	/* TSHADERPROGRAM_H */

