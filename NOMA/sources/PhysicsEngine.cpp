/* 
 * File:   PhysicsEngine.cpp
 * Author: laurasirventcollado
 * 
 * Created on 13 de febrero de 2014, 11:28
 */

#include "../headers/PhysicsEngine.h"
#include "../headers/GraphicEngine.h"
#include "../headers/GraphicConnector.h"
#include "../headers/GLDebugDraw.h"
#include "../headers/Game.h"
#include "../headers/TResourceMesh.h"
#include "../SOIL/include/SOIL.h"
#include "../Bullet/src/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"

PhysicsEngine::PhysicsEngine(std::string collisionMapFilename) {

    btCollisionConfiguration * collisionConfiguration = new btDefaultCollisionConfiguration();
    btBroadphaseInterface * broadPhase = new btAxisSweep3(btVector3(-100, -100, -100), btVector3(100, 100, 100));
    btDispatcher * dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btConstraintSolver * solver = new btSequentialImpulseConstraintSolver();
    world = new btDiscreteDynamicsWorld(dispatcher, broadPhase, solver, collisionConfiguration);

    addCollisionMeshToWorld((char *) collisionMapFilename.c_str());

    /*btBulletWorldImporter *fileLoader = new btBulletWorldImporter(world);
    fileLoader->loadFile(collisionMapFilename.c_str());
    btCollisionObjectArray objects = world->getCollisionObjectArray();

    for (int i = 0; i < objects.size(); i++) {
        btCollisionObject *obj = objects[i];
        if (obj->getCollisionShape()->getShapeType() == SCALED_TRIANGLE_MESH_SHAPE_PROXYTYPE) {
            btScaledBvhTriangleMeshShape *shape = static_cast<btScaledBvhTriangleMeshShape *> (obj->getCollisionShape());
            if (!shape->getChildShape()->getOwnsBvh()) {
                cout << "Optimizing..." << endl;
                shape->getChildShape()->buildOptimizedBvh();
            }
            obj->getWorldTransform().setOrigin(btVector3(0, 0, 0));

        }
        std::cout << "Found collision mesh" << std::endl;
        world->removeCollisionObject(obj);
        world->addCollisionObject(obj, 1, 7);
    }*/

    //HEIGHTMAP

    /*int width, height, channels;
    unsigned char *ht_map = SOIL_load_image("World1/all.tga",&width, &height, &channels,SOIL_LOAD_L);
    btHeightfieldTerrainShape* heightmap = new btHeightfieldTerrainShape(width,height, ht_map, 1, 0, 1, 1, PHY_UCHAR, false);
    heightmap->setLocalScaling(btVector3(100,1,100));
    
    
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(btVector3(0, 0, 0));

    btMotionState * motionState = new btDefaultMotionState(transform);
    btRigidBody * body = new btRigidBody(0, motionState, heightmap, btVector3(0, 0, 0));
    world->addRigidBody(body, 1, 7);
    cout<<"Added heightmap? "<<world->getNumCollisionObjects()<<endl;*/

    //PLANE

    if (world->getNumCollisionObjects() == 0) {
        btTransform transform;
        transform.setIdentity();
        transform.setOrigin(btVector3(0, 0, 0));

        btBoxShape * boxPlaneShape = new btBoxShape(btVector3(1000, 0.1, 1000));
        btTransform planeTransform;
        planeTransform.setIdentity();
        planeTransform.setOrigin(btVector3(0, 0, 0));
        btMotionState * planeMotionState = new btDefaultMotionState(planeTransform);
        btCollisionObject * planeBody = new btCollisionObject();
        planeBody->setCollisionShape(boxPlaneShape);
        planeBody->setWorldTransform(planeTransform);
        planeBody->setRestitution(0.5f);
        world->addCollisionObject(planeBody, 1, 7);

        //  1.g Marca el plano como cuerpo cinematico
        planeBody->setCollisionFlags(planeBody->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
        planeBody->setActivationState(DISABLE_DEACTIVATION);
    }

    if (Game::Instance()->getWhichGraphicConnector() == 0) {
        GraphicConnector * connector = GraphicEngine::Instance()->getGraphicConnector();
        connector->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
        world->setDebugDrawer(connector);
    } else {
        GLDebugDraw *debugDraw = new GLDebugDraw();
        debugDraw->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
        world->setDebugDrawer(debugDraw);
    }
    std::cout << "CONSTRUCTOR" << std::endl;
    std::cout << "World has " << world->getNumCollisionObjects() << " collision objects." << std::endl;

}

PhysicsEngine::PhysicsEngine(const PhysicsEngine& orig) {
}

PhysicsEngine::~PhysicsEngine() {
}

void PhysicsEngine::update(double deltaTime) {

    world->stepSimulation(deltaTime, 10);

    btTransform t;
}

void PhysicsEngine::debugRender() {
    world->debugDrawWorld();
}

void PhysicsEngine::addKinematicObject(btCollisionObject* collisionObject, int group, int mask) {

    world->addCollisionObject(collisionObject, group, mask);
}

void PhysicsEngine::addDinamicObject(btRigidBody* object, int group, int mask) {

    world->addRigidBody(object, group, mask);
}

void PhysicsEngine::moveKinematicObject(btCollisionObject* object, btVector3 traslation) {

    btTransform transform = object->getWorldTransform();
    transform.setOrigin(traslation);
    object->setWorldTransform(transform);
}

void PhysicsEngine::addAction(btKinematicCharacterController* c) {

    world->addAction(c);
}

void PhysicsEngine::removeAction(btKinematicCharacterController* c) {
    world->removeAction(c);
}

void PhysicsEngine::removeKinematicObject(btCollisionObject* collisionObject) {
    world->removeCollisionObject(collisionObject);
}

void PhysicsEngine::removeDynamicObject(btRigidBody* body) {
    world->removeRigidBody(body);
}

void PhysicsEngine::addCollisionMeshToWorld(char* filename) {

    TResourceMesh * mesh = new TResourceMesh();
    mesh->load(filename);

    btTriangleMesh* data = new btTriangleMesh();
    for (int i = 0; i < mesh->getNumberOfFaces(); i++) {

        std::vector<Vector3f> triangle = mesh->getTriangle(i);

        btVector3 A(triangle[0].X, triangle[0].Y, triangle[0].Z);
        btVector3 B(triangle[1].X, triangle[1].Y, triangle[1].Z);
        btVector3 C(triangle[2].X, triangle[2].Y, triangle[2].Z);
        data->addTriangle(A, B, C, false); // false, don’t remove duplicate vertices
    }

    // true for using quantization; true for building the BVH
    btBvhTriangleMeshShape* shape = new btBvhTriangleMeshShape(data, true, true);
    btScaledBvhTriangleMeshShape* sshape = new btScaledBvhTriangleMeshShape(shape, btVector3(1, 1, 1));

    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(btVector3(0, 0, 0));

    btMotionState * cubeMotionState = new btDefaultMotionState(transform);
    worldMap = new btRigidBody(0, cubeMotionState, sshape, btVector3(0, 0, 0));
    worldMap->setFriction(1.0);
    world->addRigidBody(worldMap, 1, 7);

    world->setGravity(btVector3(0, -10, 0));
    world->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
    
    std::cout << "ADD" << std::endl;
    std::cout << "World has " << world->getNumCollisionObjects() << " collision objects." << std::endl;

}

void PhysicsEngine::removeWorldMap() {

    world->removeRigidBody(worldMap);
    std::cout << "REMOVE" << std::endl;
    std::cout << "World has " << world->getNumCollisionObjects() << " collision objects." << std::endl;

    delete(worldMap);
    worldMap = NULL;
}