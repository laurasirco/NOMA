/* 
 * File:   TMatrix4x4.cpp
 * Author: laurasirventcollado
 * 
 * Created on 10 de febrero de 2014, 12:34
 */

#include "../headers/TMatrix4x4.h"

TMatrix4x4::TMatrix4x4() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = 0;
        }
    }
}

TMatrix4x4::TMatrix4x4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44) {

    matrix[0][0] = m11;
    matrix[0][1] = m12;
    matrix[0][2] = m13;
    matrix[0][3] = m14;
    matrix[1][0] = m21;
    matrix[1][1] = m22;
    matrix[1][2] = m23;
    matrix[1][3] = m24;
    matrix[2][0] = m31;
    matrix[2][1] = m32;
    matrix[2][2] = m33;
    matrix[2][3] = m34;
    matrix[3][0] = m41;
    matrix[3][1] = m42;
    matrix[3][2] = m43;
    matrix[3][3] = m44;
}

TMatrix4x4::TMatrix4x4(const TMatrix4x4& orig) {
}

TMatrix4x4::~TMatrix4x4() {
}

void TMatrix4x4::multiplyMatrix(TMatrix4x4* m) {
    TMatrix4x4 *aux = new TMatrix4x4();
    
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            for(int x = 0; x < 4; x++){
                aux->setPosition(i,j,aux->getPosition(i,j)+matrix[i][x]*m->getPosition(x,j));
            }
        }
    }
    
    for(int i=0; i < 4; i++){
        for(int j=0; j < 4; j++){
            matrix[i][j] = aux->getPosition(i,j);
        }
    }
}

std::vector<float> TMatrix4x4::multiplyVector(std::vector<float> v) {
    std::vector<float> aux;
    for (int i = 0; i < 4; i++) {
        float value = 0;
        for (int j = 0; j < 4; j++) {
            value += matrix[i][j] * v[j];
        }
        aux.push_back(value);
    }
    
    return aux;
}

TMatrix4x4 * TMatrix4x4::traspose() {
    TMatrix4x4 * traspose = new TMatrix4x4();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            traspose->setPosition(j, i, matrix[i][j]);
        }
    }
    return traspose;
}
