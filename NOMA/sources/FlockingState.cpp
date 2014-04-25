/* 
 * File:   FlockingState.cpp
 * Author: laurasirventcollado
 * 
 * Created on 9 de enero de 2014, 11:55
 */

#include "../headers/FlockingState.h"
#include "../headers/SteeringBehaviors.h"
#include "../headers/FlockingBehaviors.h"
#include "../headers/GameState.h"
#include "../headers/Game.h"
#include "../headers/PRoute.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <time.h>

FlockingState::FlockingState() {
    index = Flocking;
}

FlockingState::FlockingState(const FlockingState& orig) {
}

FlockingState::~FlockingState() {
}

void FlockingState::update(Citizen* me) {

    SteeringOutput acceleration;
    acceleration.linear = Vector3f();
    
    if (me->getTo() != me->getPath()->getTo()) {
        me->getPath()->setTo(me->getTo());
        me->getPath()->setFrom(me->getFrom());
        me->getPath()->setDone(false);
        PRoute *route = new PRoute();
        me->getPath()->setWaypoints(route->calculateRoute(GameState::Instance()->getCurrentWorld()->getWayPoints(), GameState::Instance()->getCurrentWorld()->getWayPoints()->getPNode(me->getFrom()), GameState::Instance()->getCurrentWorld()->getWayPoints()->getPNode(me->getTo())));
    }
    
    acceleration = SteeringBehaviors::Instance()->followPath(me, me->getPath(), 15);
    acceleration.linear = acceleration.linear * 5;

    //FLOCKING BEHAVIOR
    SteeringOutput flockingForces;
    std::vector<BaseGameEntity *> neighborhood = me->getNeighborhood(GameState::Instance()->getEntities(), 10);


    if (neighborhood.size() > 0) {
        flockingForces.linear = FlockingBehaviors::Instance()->calculateFlockingForces(me, neighborhood, 1, 1, 0, 0.9);
        //flockingForces.linear = flockingForces.linear.truncate(maxForce); //Truncate to max
        flockingForces.linear.Y = 0.0;
        acceleration.linear = acceleration.linear + flockingForces.linear;
    }

    flockingForces.angular = 0.0f;
    
    acceleration.linear = acceleration.linear + SteeringBehaviors::Instance()->calculate(me, GameState::Instance()->getNoma()).linear;
    
    me->avoidPenetrationWithNeighbors(neighborhood, 2, 5, 10);
    
    //Calculate acceleration = forces/mass
    acceleration.linear = acceleration.linear / me->getMass();

    //Update velocity = acceleration * elapsedTime (truncate to max velocity if so)
    me->setVelocity(me->getVelocity() + acceleration.linear * FPS);

    me->setRotation(acceleration.angular * FPS);

    me->setVelocity(me->getVelocity().truncate(me->getMaxSpeed()));
    
    me->setRotation(atan2(me->getVelocity().X, me->getVelocity().Z));

    //cout<<"rotation: "<<rotation<<endl;
    me->setOrientation(me->getRotation());
}

