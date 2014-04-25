/* 
 * File:   DynamicEntity.cpp
 * Author: laurasirventcollado
 * 
 * Created on 14 de febrero de 2014, 17:56
 */

#include "../headers/DynamicEntity.h"
#include "../headers/Game.h"
#include "../headers/GameState.h"

DynamicEntity::DynamicEntity(Vector3f pos) {
    position = pos;
    orientation.X = 0; orientation.Y = 0; orientation.Z = 0;
    ID = Game::Instance()->addEntity();
    
    type = TDynamic;
    
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(btVector3(position.X, position.Y, position.Z));

    btMotionState * cubeMotionState = new btDefaultMotionState(transform);
    btBoxShape *cubeShape = new btBoxShape(btVector3(1, 1, 1));
    btVector3 cubeLocalInertia;
    cubeShape->calculateLocalInertia(1, cubeLocalInertia);
    body = new btRigidBody(0.5, cubeMotionState, cubeShape, cubeLocalInertia);
    body->setRestitution(1.0f);
    
    
    GameState::Instance()->getPhysicsEngine()->addDinamicObject(body, 1, 7);
}

DynamicEntity::DynamicEntity(const DynamicEntity& orig) {
}

DynamicEntity::~DynamicEntity() {
    GameState::Instance()->getPhysicsEngine()->removeDynamicObject(body);
    delete(body);
    body = NULL;
}

void DynamicEntity::update(){
    
    Vector3f prevPosition = position;
    btVector3 pos = body->getCenterOfMassPosition();
    position = Vector3f((f32)pos[0], (f32)pos[1], (f32)pos[2]);
    
    if(Game::Instance()->getWhichGraphicConnector() != 0){
        TTransformation * transformation = (TTransformation *)graphicNode->getParent()->getEntity();
        transformation->translate(position.X - prevPosition.X, position.Y - prevPosition.Y, position.Z - prevPosition.Z);
    }

}

Quaternion DynamicEntity::getOrientation(){
    
    const btQuaternion& quat = body->getOrientation();
    Quaternion q(quat.getX(), quat.getY(), quat.getZ(), quat.getW());
    return q;
    
}

