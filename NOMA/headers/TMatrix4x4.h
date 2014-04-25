/* 
 * File:   TMatrix4x4.h
 * Author: laurasirventcollado
 *
 * Created on 10 de febrero de 2014, 12:34
 */

#ifndef TMATRIX4X4_H
#define	TMATRIX4X4_H
#include <iostream>
#include <vector>

class TMatrix4x4 {
public:
    TMatrix4x4();
    TMatrix4x4(const TMatrix4x4& orig);
    TMatrix4x4(float m11, float m12, float m13, float m14,
               float m21, float m22, float m23, float m24,
               float m31, float m32, float m33, float m34,
               float m41, float m42, float m43, float m44);
    float getPosition(int i, int j) { return matrix[i][j]; }
    void setPosition(int i, int j, float value) { matrix[i][j] = value; }
    virtual ~TMatrix4x4();
    void multiplyMatrix (TMatrix4x4 * m);
    std::vector<float> multiplyVector (std::vector<float> v);
    TMatrix4x4 * traspose();
private:
    float matrix[4][4];
};

#endif	/* TMATRIX4X4_H */

