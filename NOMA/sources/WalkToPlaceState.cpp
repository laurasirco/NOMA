/* 
 * File:   WalkToPlaceState.cpp
 * Author: laurasirventcollado
 * 
 * Created on 10 de enero de 2014, 10:25
 */

#include "../headers/WalkToPlaceState.h"
#include "../headers/PathwalkingState.h"
#include "../headers/SteeringBehaviors.h"
#include "../headers/FlockingBehaviors.h"
#include "../headers/TalkToNomaState.h"
#include "../headers/GameState.h"
#include "../headers/Game.h"
#include "../headers/PRoute.h"
#include "../headers/GraphicEngine.h"
#include <iostream>

WalkToPlaceState::WalkToPlaceState() {
    index = WalkToPlace;
}

WalkToPlaceState::WalkToPlaceState(const WalkToPlaceState& orig) {
}

WalkToPlaceState::~WalkToPlaceState() {
}

void WalkToPlaceState::update(Citizen* me) {

    //Citizen arrived to place
    GameState::Instance()->getNoma()->setInteracting(true);
    if (me->getPath()->isPathDone()) {
        me->setVelocity(Vector3f(0, 0, 0));
        
        if (GraphicEngine::Instance()->isSubtitleSpaceEmpty() && me->isNomaInRadius(me->getTrustValue(), GameState::Instance()->getNoma())) {
            me->getScriptLine()->setArrived(true);
            me->changeState(new TalkToNomaState());
        }

        Vector3f nomaDirection = GameState::Instance()->getNoma()->getPosition() - me->getPosition();
        //ANGULAR
        me->setRotation(atan2(nomaDirection.X, nomaDirection.Z));
        me->setOrientation(me->getRotation());
    } 
    
    else {
        if (GraphicEngine::Instance()->isSubtitleSpaceEmpty()) {
            SteeringOutput acceleration;

            if (me->getTo() != GameState::Instance()->getCurrentWorld()->getWayPoints()->getNearestPNode(me->getScriptLine()->getPoint())) {
                me->setFrom(GameState::Instance()->getCurrentWorld()->getWayPoints()->getNearestPNode(me->getPosition()));
                me->setTo(GameState::Instance()->getCurrentWorld()->getWayPoints()->getNearestPNode(me->getScriptLine()->getPoint()));
            }
            if (me->getTo() != me->getPath()->getTo()) {
                me->getPath()->setTo(me->getTo());
                me->getPath()->setFrom(me->getFrom());
                me->getPath()->setDone(false);
                PRoute *route = new PRoute();
                me->getPath()->setWaypoints(route->calculateRoute(GameState::Instance()->getCurrentWorld()->getWayPoints(), GameState::Instance()->getCurrentWorld()->getWayPoints()->getPNode(me->getFrom()), GameState::Instance()->getCurrentWorld()->getWayPoints()->getPNode(me->getTo())));
            }

            acceleration = SteeringBehaviors::Instance()->followPath(me, me->getPath(), 4);
            acceleration.linear = acceleration.linear * 5;

            //Calculate acceleration = forces/mass
            acceleration.linear = acceleration.linear / me->getMass();

            //Update velocity = acceleration * elapsedTime (truncate to max velocity if so)
            me->setVelocity(me->getVelocity() + acceleration.linear * FPS);

            me->setRotation(acceleration.angular * FPS);

            me->setVelocity(me->getVelocity().truncate(me->getMaxSpeed()));

            //ANGULAR
            me->setRotation(atan2(me->getVelocity().X, me->getVelocity().Z));

            //cout<<"rotation: "<<rotation<<endl;
            me->setOrientation(me->getRotation());

        } 
        else {
            Vector3f nomaDirection = GameState::Instance()->getNoma()->getPosition() - me->getPosition();
            //ANGULAR
            me->setRotation(atan2(nomaDirection.X, nomaDirection.Z));
            me->setOrientation(me->getRotation());
            me->setVelocity(Vector3f(0,0,0));
        }
    }

}
