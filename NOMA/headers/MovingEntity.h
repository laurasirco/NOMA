/* 
 * File:   MovingEntity.h
 * Author: laurasirventcollado
 *
 * Created on 25 de octubre de 2013, 10:38
 */

#ifndef MOVINGENTITY_H
#define	MOVINGENTITY_H

#include "BaseGameEntity.h"

class MovingEntity : public BaseGameEntity {
public:
    MovingEntity();
    MovingEntity(float, float, float);
    MovingEntity(const MovingEntity& orig);
    virtual ~MovingEntity();
    
    float getMaxSpeed(){ return maxSpeed; }
    float getMaxForce(){ return maxForce; }
    float getMass(){ return mass; }
    Vector3f getVelocity(){ return velocity; }
    float getRotation(){ return rotation; }
    
    void setVelocity(float vX, float vY, float vZ){ velocity.X = vX; velocity.Y = vY; velocity.Z = vZ; }
    void setVelocity(Vector3f v){ velocity = v; }
    void setRotation(float r){ rotation = r;}    
        
private:

protected:
    float maxSpeed;
    float maxForce;
    float mass;
    Vector3f velocity;
    float rotation;
    
};

#endif	/* MOVINGENTITY_H */

