/* 
 * File:   FlockingBehaviors.h
 * Author: laurasirventcollado
 *
 * Created on 4 de noviembre de 2013, 20:48
 */

#ifndef FLOCKINGBEHAVIORS_H
#define	FLOCKINGBEHAVIORS_H

#include "BaseGameEntity.h"
#include <iostream>
#include <vector>

class FlockingBehaviors {
    
    typedef std::vector<BaseGameEntity *> EntitiesVector;
    typedef std::vector<BaseGameEntity *>::iterator EntitiesVectorIterator;
public:
    FlockingBehaviors();
    FlockingBehaviors(const FlockingBehaviors& orig);
    virtual ~FlockingBehaviors();
    static FlockingBehaviors * Instance();
    Vector3f calculateFlockingForces(BaseGameEntity *self, EntitiesVector neighbors, float maxForce, float sFactor = 0.5, float aFactor = 0.5, float cFactor = 0.5);
    
private:
    static FlockingBehaviors *pinstance;
    Vector3f separation(BaseGameEntity *self, EntitiesVector neighbors, float maxForce);
    Vector3f alignment(BaseGameEntity *self, EntitiesVector neighbors, float maxForce);
    Vector3f cohesion(BaseGameEntity *self, EntitiesVector neighbors, float maxForce);
    
};

#endif	/* FLOCKINGBEHAVIORS_H */

