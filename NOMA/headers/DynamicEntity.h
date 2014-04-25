/* 
 * File:   DynamicEntity.h
 * Author: laurasirventcollado
 *
 * Created on 14 de febrero de 2014, 17:56
 */

#ifndef DYNAMICENTITY_H
#define	DYNAMICENTITY_H
#include "BaseGameEntity.h"
#include "../Bullet/src/btBulletDynamicsCommon.h"
#include <cmath>

struct Quaternion{
    
    float X;
    float Y;
    float Z;
    float W;
    Quaternion(float X=0, float Y=0, float Z=0, float W=0) : X(X), Y(Y), Z(Z), W(W) {}
    
};

class DynamicEntity : public BaseGameEntity {
public:
    DynamicEntity(Vector3f pos);
    DynamicEntity(const DynamicEntity& orig);
    virtual ~DynamicEntity();
    void update();
    Quaternion getOrientation();
    
private:
    btRigidBody * body;
    Vector3f orientation;
};

#endif	/* DYNAMICENTITY_H */

