/* 
 * File:   TCamera.h
 * Author: laurasirventcollado
 *
 * Created on 10 de febrero de 2014, 18:42
 */

#ifndef TCAMERA_H
#define	TCAMERA_H

#include "TEntity.h"

class TCamera : public TEntity {
public:
    TCamera();
    TCamera(const TCamera& orig);
    virtual ~TCamera();
    
    void beginDraw();
    void endDraw();
private:
    bool isPerspective;
    float near;
    float far;
 
};

#endif	/* TCAMERA_H */

