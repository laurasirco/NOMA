/* 
 * File:   TTransformation.h
 * Author: laurasirventcollado
 *
 * Created on 10 de febrero de 2014, 12:11
 */

#ifndef TTRANSFORMATION_H
#define	TTRANSFORMATION_H

#include "TEntity.h"
#include "Matrices.h"
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>


class TTransformation : public TEntity {
public:
    TTransformation();
    TTransformation(float a11, float a12, float a13, float a14, float a21, float a22, float a23, float a24, float a31, float a32, float a33, float a34, float a41, float a42, float a43, float a44) { matrix = Matrix4(a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44); }
    TTransformation(const TTransformation& orig);
    virtual ~TTransformation();
    void beginDraw();
    void endDraw();
    
    void identity() {matrix.identity(); }
    void loadMatrix(Matrix4 m) {matrix = m;}
    Matrix4 getMatrix() {return matrix;}
    void setMatrix(float a11, float a12, float a13, float a14, float a21, float a22, float a23, float a24, float a31, float a32, float a33, float a34, float a41, float a42, float a43, float a44) { matrix.set(a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44); }
    Vector3 getPosition() { return Vector3(matrix[3], matrix[7], matrix[11]);}
    void translate(float tx, float ty, float tz) {matrix.translate(tx,ty,tz); }
    void rotate(float angle, float x, float y, float z) {matrix.rotate(angle,x,y,z);}
    void rotateX(float angle) {matrix.rotateX(angle);}
    void rotateY(float angle) {matrix.rotateY(angle);}
    void rotateZ(float angle) {matrix.rotateZ(angle);}
    void scale(float sx, float sy, float sz) {matrix.scale(sx,sy,sz);}
    void scale(float s) {matrix.scale(s);}
    void transpose() { matrix.transpose(); }
    void invert() { matrix.invert(); }
    
    void absoluteRotateY(float angle);
private:
    Matrix4 matrix;
    
};

#endif	/* TTRANSFORMATION_H */

