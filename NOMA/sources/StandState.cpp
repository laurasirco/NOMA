/* 
 * File:   StandState.cpp
 * Author: laurasirventcollado
 * 
 * Created on 10 de enero de 2014, 10:36
 */

#include "../headers/StandState.h"
#include "../headers/GameState.h"

StandState::StandState() {
    index = Stand;
}

StandState::StandState(const StandState& orig) {
}

StandState::~StandState() {
}

void StandState::update(Citizen* me) {
    me->setVelocity(Vector3f(0, 0, 0));

    Vector3f nomaDirection = GameState::Instance()->getNoma()->getPosition() - me->getPosition();
    //ANGULAR
    me->setRotation(atan2(nomaDirection.X, nomaDirection.Z));
    me->setOrientation(me->getRotation());
}

