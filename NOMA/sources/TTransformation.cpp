/* 
 * File:   TTransformation.cpp
 * Author: laurasirventcollado
 * 
 * Created on 10 de febrero de 2014, 12:11
 */

#include "../headers/TTransformation.h"
#include <math.h>
#define PI 3.14159265

TTransformation::TTransformation() {
    matrix = Matrix4();
    matrix.identity();
}

TTransformation::TTransformation(const TTransformation& orig) {
}

TTransformation::~TTransformation() {
}

void TTransformation::beginDraw() {
   glPushMatrix(); //Set the current matrix on the stack
   glMultMatrixf(matrix.getTranspose()); //Multiply actual matrix and TransformMatrix
}

void TTransformation::endDraw() {
    glPopMatrix(); // Pop the old matrix without the transformations.
}

void TTransformation::absoluteRotateY(float angle){
    float c = cos(angle*3.14159/180);
    float s = sin(angle*3.14159/180);
    matrix[0] = c;
    matrix[1] = 0;
    matrix[2] = s;
    matrix[4] = 0;
    matrix[5] = 1;
    matrix[6] = 0;
    matrix[8] = -s;
    matrix[9] = 0;
    matrix[10] = c;
    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = 0;
    matrix[15] = 1;
}

