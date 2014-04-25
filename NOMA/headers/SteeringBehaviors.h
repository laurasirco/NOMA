/* 
 * File:   SteeringBehaviors.h
 * Author: laurasirventcollado
 *
 * Created on 25 de octubre de 2013, 10:50
 */

#ifndef STEERINGBEHAVIORS_H
#define	STEERINGBEHAVIORS_H

#include "BaseGameEntity.h"
#include "MovingEntity.h"
#include "PGraph.h"
#include "Path.h"
#include <iostream>
#include <vector>

typedef std::vector<BaseGameEntity *> EntitiesVector3f;
typedef std::vector<BaseGameEntity *>::iterator EntitiesVector3fIterator;

struct SteeringOutput {
    Vector3f linear;
    float angular;
};

//typedef Vector3f SteeringOutput;

class SteeringBehaviors {
public:
    SteeringBehaviors();
    SteeringBehaviors(const SteeringBehaviors& orig);
    virtual ~SteeringBehaviors();
    static SteeringBehaviors * Instance();

    SteeringOutput seek(Vector3f to);
    SteeringOutput flee(Vector3f from);
    SteeringOutput arrive(Vector3f to);
    SteeringOutput followPath(MovingEntity *s, Path *path, float r);
    SteeringOutput calculate(MovingEntity *s, BaseGameEntity *t);
    float getNewOrientation(float currentOrientation, Vector3f velocity);
    float getRadius(){ return radius; }

private:
    static SteeringBehaviors *pinstance;
    MovingEntity * self;
    BaseGameEntity * target;
    float radius;

};

#endif	/* STEERINGBEHAVIORS_H */

