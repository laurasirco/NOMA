/* 
 * File:   Character.cpp
 * Author: MAC
 * 
 * Created on 15 de octubre de 2013, 17:22
 */

#include "../headers/Character.h"
#include "../headers/GameState.h"

Character::Character() {
    
    
}

Character::Character(const Character& orig) {
}

Character::~Character() {

}

void Character::setPhysicsPosition(Vector3f pos){
    GameState::Instance()->getPhysicsEngine()->moveKinematicObject(m_ghostObject, btVector3(pos.X,pos.Y,pos.Z));
}
