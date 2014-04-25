/* 
 * File:   FlockingBehaviors.cpp
 * Author: laurasirventcollado
 * 
 * Created on 4 de noviembre de 2013, 20:48
 */

#include "../headers/FlockingBehaviors.h"
#include "../headers/SteeringBehaviors.h"
#include "../headers/MovingEntity.h"
using namespace std;

FlockingBehaviors::FlockingBehaviors() {
}

FlockingBehaviors::FlockingBehaviors(const FlockingBehaviors& orig) {
}

FlockingBehaviors::~FlockingBehaviors() {
}

FlockingBehaviors * FlockingBehaviors::pinstance = 0;

FlockingBehaviors * FlockingBehaviors::Instance(){
   
    if(pinstance == 0){
        pinstance = new FlockingBehaviors;
    }
    return pinstance;
}

Vector3f FlockingBehaviors::calculateFlockingForces(BaseGameEntity* self, std::vector<BaseGameEntity *> neighbors, float maxForce, float sFactor, float aFactor, float cFactor){
    
    Vector3f force = Vector3f(0,0,0);
    
    force = force + (separation(self, neighbors, maxForce))*sFactor;
    force = force + (alignment(self, neighbors, maxForce))*aFactor;
    force = force + (cohesion(self, neighbors, maxForce))*cFactor;
    
    return force;
}

Vector3f FlockingBehaviors::alignment(BaseGameEntity* self, EntitiesVector neighbors, float maxForce){
    
    Vector3f alignmentForce;
    
    for(EntitiesVectorIterator it = neighbors.begin(); it != neighbors.end(); ++it){     
        MovingEntity *n = (MovingEntity *)*it;
        //if (n != self) {
                alignmentForce = alignmentForce + n->getVelocity();
        //}
    }
    
    alignmentForce = alignmentForce/neighbors.size();
    
    return alignmentForce.truncate(maxForce);
}

Vector3f FlockingBehaviors::separation(BaseGameEntity* self, EntitiesVector neighbors, float maxForce){
    
    Vector3f separationForce = Vector3f(0,0,0);
    
    for(EntitiesVectorIterator it = neighbors.begin(); it != neighbors.end(); ++it){
        
        BaseGameEntity *n = *it;
        //if(n != self){
            Vector3f to = n->getPosition() - self->getPosition();
            separationForce = separationForce + to.normalize()/to.magnitude();
        //}
    }
    
    return separationForce.truncate(maxForce);
}

Vector3f FlockingBehaviors::cohesion(BaseGameEntity* self, EntitiesVector neighbors, float maxForce){
    
    Vector3f cohesionForce, centerOfMass;
    for(EntitiesVectorIterator it = neighbors.begin(); it != neighbors.end(); ++it){
        BaseGameEntity *n = *it;
        //if (n != self) {
                centerOfMass = centerOfMass + n->getPosition();
        //}
    }
    centerOfMass = centerOfMass/neighbors.size();
    //cohesionForce = SteeringBehaviors::Instance()->seek(centerOfMass).linear;
    cohesionForce = centerOfMass - self->getPosition();
    cohesionForce = cohesionForce.normalize();
        
    return cohesionForce.truncate(maxForce);
    
}

