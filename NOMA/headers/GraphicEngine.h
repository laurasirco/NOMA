/* 
 * File:   GraphicEngine.h
 * Author: MAC
 *
 * Created on 15 de octubre de 2013, 17:37
 */

#ifndef GRAPHICENGINE_H
#define	GRAPHICENGINE_H

#include "../Irrlicht/include/irrlicht.h"
#include "BaseGameEntity.h"
#include "DynamicEntity.h"
#include "EventManager.h"
#include "PGraph.h"
#include "MainMenuState.h"
#include "GraphicConnector.h"
#include "TAGConnector.h"
#include "World.h"
#include "GUIText.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class GraphicEngine {
public:
    GraphicEngine();
    GraphicEngine(const GraphicEngine& orig);
    virtual ~GraphicEngine();
    GraphicEngine &operator = (const GraphicEngine &);
    static GraphicEngine* Instance();
    void init(int which, int screenWidth, int screenHeight, bool fullScreen = false);
    void render(bool interpolation = true);
    void addWaypoints(PGraph *waypoints);
    void drawWaypoints();
    void update();
    void addEntities(std::vector<BaseGameEntity *> entities);
    bool isDeviceRunning();
    void deleteGraphicEngine();
    void loadWorldMap(World *world);
    void addDebugInterface ();
    void toggleDepurationMode();
    void deleteDepuration(){ depuration = false; firstTimeDepuration = false; deleteGUIEntities(); }
    
    void addGUIEntities(std::vector<MenuItem> elements);
    void deleteGUIEntities();
    void deleteEntities(){ if(which == 0)connector->deleteEntities(); else TConnector->clearSceneTree(); }
        
    void printActualFPS(float aFPS){ cFPS = aFPS; };
    
    void printSubtitle(std::wstring s);
    bool isSubtitleSpaceEmpty(){ return empty; }
    void emptySubtitle();
    
    GraphicConnector * getGraphicConnector(){ return connector; }
    void resumeScene();
    void close(){ connector->close(); }
    TAGConnector* getTConnector() { return TConnector; }
    
    int getHeight(){ return screenHeight; }
    int getWidth(){ return screenWidth; }
    
private:
    static GraphicEngine* pinstance;
    int which;
    GraphicConnector * connector;
    TAGConnector * TConnector;
    float cFPS;
    EventManager * em;
    int screenHeight, screenWidth;
    
    bool depuration;
    bool firstTimeDepuration;
    
    std::wstring subtitle;
    bool empty;
    GUIText * sub;
        
};

#endif	/* GRAPHICENGINE_H */

