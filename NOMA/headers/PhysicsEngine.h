/* 
 * File:   PhysicsEngine.h
 * Author: laurasirventcollado
 *
 * Created on 13 de febrero de 2014, 11:28
 */

#ifndef PHYSICSENGINE_H
#define	PHYSICSENGINE_H

#include "../Bullet/src/btBulletDynamicsCommon.h"
#include "../Bullet/src/BulletDynamics/Character/btKinematicCharacterController.h"
#include "../Bullet/src/BulletCollision/CollisionDispatch/btGhostObject.h"
#include <BulletWorldImporter/btBulletWorldImporter.h>

#include <iostream>
using namespace std;

class PhysicsEngine {
public:
    PhysicsEngine(std::string collisionMapFilename);
    PhysicsEngine(const PhysicsEngine& orig);
    virtual ~PhysicsEngine();
    void update(double deltaTime);
    void addKinematicObject(btCollisionObject * collisionObject, int group, int mask);
    void addStaticObject();
    void addDinamicObject(btRigidBody * object, int group, int mask);
    void moveKinematicObject(btCollisionObject * object, btVector3 traslation);
    void debugRender();
    void addAction(btKinematicCharacterController *c);
    void removeAction(btKinematicCharacterController *c);
    void removeKinematicObject(btCollisionObject * collisionObject);
    void removeDynamicObject(btRigidBody *body);
    void addCollisionMeshToWorld(char * filename);
    void removeWorldMap();
    btDynamicsWorld * getWorld(){ return world; }
    
private:
       
   btDynamicsWorld * world; 
   btRigidBody * worldMap;
};

#endif	/* PHYSICSENGINE_H */

