/* 
 * File:   SteeringBehaviors.cpp
 * Author: laurasirventcollado
 * 
 * Created on 25 de octubre de 2013, 10:50
 */

#include "../headers/SteeringBehaviors.h"
#include <iostream>
#include <cmath>
using namespace std;

SteeringBehaviors::SteeringBehaviors() {
}

SteeringBehaviors::SteeringBehaviors(const SteeringBehaviors& orig) {
}

SteeringBehaviors::~SteeringBehaviors() {
}

SteeringBehaviors * SteeringBehaviors::pinstance = 0;

SteeringBehaviors * SteeringBehaviors::Instance(){
   
    if(pinstance == 0){
        pinstance = new SteeringBehaviors;
    }
    return pinstance;
}

SteeringOutput SteeringBehaviors::calculate(MovingEntity* s, BaseGameEntity* t){
    
    self = (MovingEntity *)s;
    target = (BaseGameEntity *)t;
    
    //SteeringOutput total = seek(target->getPosition());
    SteeringOutput total;
    total = flee(target->getPosition());
    
    return total;
}

SteeringOutput SteeringBehaviors::seek(Vector3f to){
    
    //Vector3f desiredVelocity = (to - self->getPosition());
    
    //desiredVelocity = desiredVelocity.normalize()*self->getMaxSpeed();
    //Vector3f velocity = arrive(to);
    SteeringOutput output = arrive(to);
    //output.linear = velocity;
    //output.angular = getNewOrientation(self->getOrientation(), velocity);
    
    return output;
    
}

SteeringOutput SteeringBehaviors::flee(Vector3f from){
    SteeringOutput output;
    Vector3f toTarget = from - self->getPosition();
    float dist = toTarget.magnitude();
    
    if(dist > 10){
        return output;
    }
    
    Vector3f desiredVelocity = (self->getPosition() - from);
    desiredVelocity = desiredVelocity.normalize()*self->getMaxSpeed();
    output.linear = desiredVelocity - self->getVelocity();
    output.angular = getNewOrientation(self->getOrientation(), output.linear);
    output.linear.Y = 0;
    return output;
}

SteeringOutput SteeringBehaviors::arrive(Vector3f to){
    
    Vector3f toTarget = to - self->getPosition();
    float dist = toTarget.magnitude();
    SteeringOutput output;
    
   
    if(dist <= radius){
        float speed = dist/radius;
        Vector3f desiredVelocity = toTarget.normalize()*speed*self->getMaxSpeed();
        output.linear = desiredVelocity - self->getVelocity();
        //output.linear.Y = output.linear.Y *10;
        //output.angular = getNewOrientation(self->getOrientation(), output.linear);
        return output;
    }
    else{
        Vector3f desiredVelocity = toTarget.normalize()*self->getMaxSpeed();
        output.linear = desiredVelocity - self->getVelocity();
        //output.angular = getNewOrientation(self->getOrientation(), output.linear);
        //output.linear.Y = output.linear.Y *10;
        return output;
    }
    
    return output;
    
}

SteeringOutput SteeringBehaviors::followPath(MovingEntity * s, Path *path, float r){
    
    self = s;
    SteeringOutput output;
    radius = r;
    
    //Check if need to seek next waypoint
    Vector3f dist = path->currentWayPoint()->getPosition() - self->getPosition();
    
    
    if(dist.magnitude() < radius){
        if(!path->nextWayPoint())
           path->setDone(true);
    }
    
    //Seek to the next waypoint if is not the last one
    if(!path->isPathDone()){
        output = seek(path->currentWayPoint()->getPosition());
    }
    
    //Arrive to the next waypoint if it is the last one
    else{
        output = arrive(path->currentWayPoint()->getPosition());
    }
        
    //cout<<"Output: "; output.linear.print(); 
    //cout<<endl;
    return output;
    
}

float SteeringBehaviors::getNewOrientation(float currentOrientation, Vector3f velocity){
    
    if(velocity.magnitude() > 0)
        return atan2(velocity.X, velocity.Z);
    else
        return currentOrientation;
    
}
