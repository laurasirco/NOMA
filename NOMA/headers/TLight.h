/* 
 * File:   TLight.h
 * Author: laurasirventcollado
 *
 * Created on 10 de febrero de 2014, 18:48
 */

#ifndef TLIGHT_H
#define	TLIGHT_H

#include "TEntity.h"
#include "GUIElement.h"

class TLight : public TEntity {
public:
    TLight();
    TLight(const TLight& orig);
    virtual ~TLight();
    
    void beginDraw();
    void endDraw();
    
    void setIntensity(RGBA i){ intensity = i; }
    RGBA getIntensity(){ return intensity; }

    
private:
    RGBA intensity;

};

#endif	/* TLIGHT_H */

