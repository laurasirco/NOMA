/* 
 * File:   Noma.cpp
 * Author: MAC
 * 
 * Created on 15 de octubre de 2013, 17:26
 */

#include "../headers/Noma.h"
#include "../headers/Game.h"
#include "../headers/GraphicEngine.h"
#include "../headers/GameState.h"
#include "../headers/TTransformation.h"
#include "../Bullet/src/BulletCollision/CollisionDispatch/btGhostObject.h"
#include "../headers/TAnimatedMesh.h"
#include <iostream>
using namespace std;

Noma::Noma(Vector3f pos) {

    ID = Game::Instance()->addEntity();
    maxSpeed = 50;
    auxFrame=0;
    //********* ENTREGABLE 8 **********//

    if (Game::Instance()->getDemoMode() == 0 || Game::Instance()->getDemoMode() == 1)
        maxForce = 5;
    else
        maxForce = 50;

    //********************************//


    mass = 1;
    activity = 50;
    temperament = 50;
    conversation = 50;
    confidence = 50;
    interacting = false;
    walking = false;
    jumping = false;
    travel = false;

    position = pos;

    type = TNoma;

    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(position.X, position.Y + 10, position.Z));

    m_ghostObject = new btPairCachingGhostObject();
    m_ghostObject->setWorldTransform(startTransform);
    btScalar characterHeight = 2;
    btScalar characterWidth = 2;
    btConvexShape* capsule = new btSphereShape(characterWidth);
    m_ghostObject->setCollisionShape(capsule);
    m_ghostObject->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
    m_ghostObject->setFriction(1.0);

    btScalar stepHeight = 0.5;
    m_character = new btKinematicCharacterController(m_ghostObject, capsule, stepHeight);
    GameState::Instance()->getPhysicsEngine()->addKinematicObject(m_ghostObject, 4, 1);
    GameState::Instance()->getPhysicsEngine()->addAction(m_character);
    m_character->setMaxJumpHeight(20.0f);


}

void Noma::setInitPosition(Vector3f p) {
    m_ghostObject->getWorldTransform().setOrigin(btVector3(p.X, p.Y, p.Z));
}

Noma::Noma(const Noma& orig) {

}

Noma::~Noma() {

    GameState::Instance()->getPhysicsEngine()->removeAction(m_character);
    GameState::Instance()->getPhysicsEngine()->removeKinematicObject(m_ghostObject);
    delete(m_character);
    m_character = NULL;
    delete(m_ghostObject);
    m_ghostObject = NULL;
}

/*
 * 1 - Apply force to Noma into the desired direction
 * 2 - Divide /mass and truncate to the max value of force applied
 * 3 - Calculate velocity
 * 4 - Apply velocity to the physic object
 * 5 - Get the physics engine calculated new position of the physic object and save it into the Noma position
 */

void Noma::accelerate(float ax, float ay, float az) {

    //Vector3f acceleration = Vector3f(ax, ay, az);
    //acceleration = acceleration / mass;
    //acceleration = acceleration.truncate(maxForce);

    velocity = Vector3f(ax, ay, az);

}

void Noma::deccelerate() {

    float factor = 2.5;

    if (velocity.magnitude() > 0) {
        velocity = velocity - velocity * factor * FPS;
    }
}

void Noma::jump() {
    jumping = true;
    m_character->jump();
}

void Noma::elevate() {

    m_character->setGravity(0.1);
    m_character->jump();
}

void Noma::fall() {
    m_character->setGravity(10.0);
}

void Noma::update() {

    frame = ((TAnimatedMesh*) graphicNode->getEntity())->getFrame();
    m_character->setGravity(9);

    Vector3f prevPosition = position;

    if (!walking)
        deccelerate();

    velocity.truncate(maxSpeed);
    m_character->setVelocityForTimeInterval(btVector3(velocity.X, velocity.Y, velocity.Z), FPS);

    /*btManifoldArray manifoldArray;
    btBroadphasePairArray &pairs = m_ghostObject->getOverlappingPairCache()->getOverlappingPairArray();
    for (int i = 0; i < pairs.size(); i++) {
        manifoldArray.clear();
        const btBroadphasePair &pair = pairs[i];
        btBroadphasePair *collisionPair = GameState::Instance()->getPhysicsEngine()->getWorld()->getPairCache()->findPair(pair.m_pProxy0, pair.m_pProxy1);
        if (!collisionPair)
            continue;
        if (collisionPair->m_algorithm) {
            collisionPair->m_algorithm->getAllContactManifolds(manifoldArray);
        }

        for (int j = 0; j < manifoldArray.size(); j++) {
            btPersistentManifold * manifold = manifoldArray[j];
        }
    }*/

    //position = position + velocity * FPS;
    //m_ghostObject->getWorldTransform().setOrigin(btVector3(position.X, position.Y, position.Z));

    float newX = m_ghostObject->getWorldTransform().getOrigin().getX();
    float newY = m_ghostObject->getWorldTransform().getOrigin().getY();
    float newZ = m_ghostObject->getWorldTransform().getOrigin().getZ();
    setPosition(newX, newY, newZ);

    if (position.Y > 100)
        fall();

    /*if (!interacting && !GraphicEngine::Instance()->isSubtitleSpaceEmpty()) {
        GraphicEngine::Instance()->setSubtitleSpace(true);
    }*/

    if (Game::Instance()->getWhichGraphicConnector() != 0) {
        TTransformation * transformation = (TTransformation *) graphicNode->getParent()->getEntity();
        transformation->translate(position.X - prevPosition.X, position.Y - prevPosition.Y, position.Z - prevPosition.Z);
        /***SET CYCLE****/
        TAnimatedMesh * animatedMesh = (TAnimatedMesh *) graphicNode->getEntity();
        if (jumping) {
            animatedMesh->setCycle(TResourceAnimatedMeshContainer::Jump);
            frame += 0.5;
            animatedMesh->setFrame(frame);

            //**************COAT***************
            TAnimatedMesh * coatMesh = (TAnimatedMesh *) accesoryNode->getEntity();

            coatMesh->setCycle(TResourceAnimatedMeshContainer::Jump);
            frame += 0.5;
            coatMesh->setFrame(frame);
            //*********************************
            if (frame >= 38) {
                jumping = false;
            }
        } else if (walking) {
            animatedMesh->setCycle(TResourceAnimatedMeshContainer::RunNeutral);
            
    
            frame += 0.5;
            
            
            animatedMesh->setFrame(frame);
            

            //**************COAT***************
            TAnimatedMesh * coatMesh = (TAnimatedMesh *) accesoryNode->getEntity();

            coatMesh->setCycle(TResourceAnimatedMeshContainer::RunNeutral);
            frame += 0.5;
            coatMesh->setFrame(frame);
            //*********************************
        } else if (velocity.magnitude() < 5) {
            animatedMesh->setCycle(TResourceAnimatedMeshContainer::Stand);
            frame += 0.5;
            animatedMesh->setFrame(frame);

            //**************COAT***************
            TAnimatedMesh * coatMesh = (TAnimatedMesh *) accesoryNode->getEntity();

            coatMesh->setCycle(TResourceAnimatedMeshContainer::Stand);
            frame += 0.5;
            coatMesh->setFrame(frame);
            //*********************************
        } else {
            animatedMesh->setCycle(TResourceAnimatedMeshContainer::Stop);
            frame += 0.5;
            animatedMesh->setFrame(frame);

            //**************COAT***************
            TAnimatedMesh * coatMesh = (TAnimatedMesh *) accesoryNode->getEntity();

            coatMesh->setCycle(TResourceAnimatedMeshContainer::Stop);
            frame += 0.5;
            coatMesh->setFrame(frame);
            //*********************************

        }


    }

}

