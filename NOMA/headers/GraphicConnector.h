/* 
 * File:   GraphicConnector.h
 * Author: laurasirventcollado
 *
 * Created on 24 de enero de 2014, 18:10
 */

#ifndef GRAPHICCONNECTOR_H
#define	GRAPHICCONNECTOR_H
#include "../Irrlicht/include/irrlicht.h"
#include "BaseGameEntity.h"
#include "DynamicEntity.h"
#include "EventManager.h"
#include "PGraph.h"
#include "MainMenuState.h"
#include "GameState.h"
#include "PGraph.h"
#include <iostream>
#include <vector>
#include "../Bullet/src/btBulletDynamicsCommon.h"

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class GraphicConnector: public btIDebugDraw {
    
public:
    
    enum FontSize { Small, Medium, Large };
    
    GraphicConnector();
    GraphicConnector(const GraphicConnector& orig);
    virtual ~GraphicConnector();
    void init(int screenWidth, int screenHeight, bool fullScreen = false);
    void addGUIEntities (vector <MenuItem> elements);
    void deleteGUIEntities();
    bool isDeviceRunning(){ return device->run(); }
    void loadMesh(std::string filename);
    void setTexture(int index, std::string filename);
    void addGameEntity(BaseGameEntity * entity, std::string filename);
    void addCubeGameEntity(BaseGameEntity * entity);
    void setPosition(int index, Vector3f position);
    void setRotation(int index, float deg);
    void setRotation(int index, Quaternion q);
    void setFollowCamera(int index);
    
    void draw2DText(std::string text, Vector3f upperCorner, Vector3f bottomCorner, FontSize size);
    void addButton(std::string text, Vector3f upperCorner, Vector3f bottomCorner, int id);
    void add3DTextToEntity(std::string text);
    void set3DTextPosition(int index, Vector3f position);
    void set3DTextContent(int index, std::string text);
    void addRadiusToEntity(int index, float radius, float propagation=0, float mood=0, float trust=0);
    void setRadius(int index, float mood, float trust);
    void setRadiusPosition(int index, Vector3f position);
    void addWaypoints(PGraph * waypoints, float radius);
    void drawWayroutes(PGraph * waypoints);
    void clearPathfindingRoutes(){ pathfindingRoutes.clear(); }
    void updatePathfindingRoutes(std::string route);
    void printPathfindingRoutes();
    void setDebugInterfaceVisible(bool visible);
    
    void beginScene(float r=0, float g=0, float b=0);
    void drawGUIElements();
    void draw3DElements();
    void endScene();
    void close(){ device->closeDevice(); }
    void deleteEntities();
    void resumeScene();
    
    void moveCameraControl(IMeshSceneNode* ch);
    
    void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color){ }
    void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
    void reportErrorWarning(const char* text){ }
    void draw3dText(const btVector3& location, const char* text) { }
    void setDebugMode(int mode) { this->mode = mode; }
    int getDebugMode() const { return this->mode; }
    
    
private:
    IrrlichtDevice * device; 
    IVideoDriver * driver;
    IGUIEnvironment * guienv;
    ISceneManager * smgr;
    EventManager *em;
    
    IGUIFont * mainFont;
    IGUIFont * textFont;
    ITexture * background;

    
    std::vector<ISceneNode *> nodes;    
    std::vector<IGUIElement *> guiElements;
    
    float direction;
    float zdirection;
    float cFPS;

    //Depuration 
    std::vector<ITextSceneNode *> entitiesTexts;
    std::vector<ISceneNode *> entitiesRadius;
    std::vector<core::stringw> pathfindingRoutes;
    std::vector<IAnimatedMeshSceneNode *> debugMoodCitizenRadius;
    std::vector<IAnimatedMeshSceneNode *> debugTrustCitizenRadius;
    std::vector<IAnimatedMeshSceneNode *> debugPropagationCitizenRadius;
    
    int mode;
    
};

#endif	/* GRAPHICCONNECTOR_H */

