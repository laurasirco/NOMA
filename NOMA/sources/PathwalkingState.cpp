/* 
 * File:   PathwalkingState.cpp
 * Author: laurasirventcollado
 * 
 * Created on 9 de enero de 2014, 11:23
 */

#include "../headers/PathwalkingState.h"
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

PathwalkingState::PathwalkingState() {
    index = Pathwalking;
}

PathwalkingState::PathwalkingState(const PathwalkingState& orig) {
}

PathwalkingState::~PathwalkingState() {
}

void PathwalkingState::update(Citizen * me){
    
    //Do your things
    SteeringOutput acceleration;

    //********* ENTREGABLE 8 **********//
    
    if (me->getPath()->isPathDone() && (Game::Instance()->getDemoMode() != 1)) {
        me->setFrom(me->getTo());
        me->setTo(rand() % GameState::Instance()->getCurrentWorld()->getWayPoints()->getNumberOfPNodes());
    }
    
    if (me->getTo() != me->getPath()->getTo() && (Game::Instance()->getDemoMode() != 1)) {
        me->getPath()->setTo(me->getTo());
        me->getPath()->setFrom(me->getFrom());
        me->getPath()->setDone(false);
        PRoute *route = new PRoute();
        me->getPath()->setWaypoints(route->calculateRoute(GameState::Instance()->getCurrentWorld()->getWayPoints(), GameState::Instance()->getCurrentWorld()->getWayPoints()->getPNode(me->getFrom()), GameState::Instance()->getCurrentWorld()->getWayPoints()->getPNode(me->getTo())));
    }
    
    if(me->getPath()->getWaypoints().size() < 2 && (Game::Instance()->getDemoMode() == 0 || Game::Instance()->getDemoMode() == 1)){
        acceleration.linear = Vector3f(0,0,0);
        acceleration.angular = 0;
        me->setVelocity(acceleration.linear);
    }
    
    else{
        acceleration = SteeringBehaviors::Instance()->followPath(me, me->getPath(), 4);
    }
    
    acceleration.linear = acceleration.linear * 5;
    
    //Calculate acceleration = forces/mass
    acceleration.linear = acceleration.linear / me->getMass();

    //Update velocity = acceleration * elapsedTime (truncate to max velocity if so)
    me->setVelocity(me->getVelocity() + acceleration.linear * FPS);

    me->setRotation(acceleration.angular * FPS);

    me->setVelocity(me->getVelocity().truncate(me->getMaxSpeed()));

    if(me->getPath()->getWaypoints().size() >= 2){
        std::vector<BaseGameEntity *> neighborhood = me->getNeighborhood(GameState::Instance()->getEntities(), 10);
        me->avoidPenetrationWithNeighbors(neighborhood, 2, 2, 2);
    }

    me->setRotation(atan2(me->getVelocity().X, me->getVelocity().Z));

    //cout<<"rotation: "<<rotation<<endl;
    me->setOrientation(me->getRotation());
    
}
