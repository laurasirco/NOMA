/* 
 * File:   TColor.h
 * Author: laurasirventcollado
 *
 * Created on 10 de febrero de 2014, 18:45
 */

#ifndef TCOLOR_H
#define	TCOLOR_H

class TColor {
public:
    TColor();
    TColor(float r, float g, float b, float a){ red = r; green = g; blue = b; alpha = a; }
    TColor(const TColor& orig);
    virtual ~TColor();
    float getRed(){ return red; }
    float getGreen(){ return green; }
    float getBlue(){ return blue; }
    float getAlpha(){ return alpha; }
    void setRed(float r){ red = r; }
    void setGreen(float g){ green = g; }
    void setBlue(float b){ blue = b; }
    void setAlpha(float a){ alpha = a; }
private:
    float red;
    float green;
    float blue;
    float alpha;
};

#endif	/* TCOLOR_H */

