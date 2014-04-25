/* 
 * File:   GameState.h
 * Author: MAC
 *
 * Created on 15 de octubre de 2013, 17:29
 */

#ifndef GAMESTATE_H
#define	GAMESTATE_H
#include "State.h"
#include "BaseGameEntity.h"
#include "Noma.h"
#include "World.h"
#include "Environment.h"
#include "DynamicEntity.h"
#include "PhysicsEngine.h"
#include "HUD.h"
#include "GUIText.h"
#include <iostream>
#include <vector>

#include "GUIText.h"

using namespace std;

class GameState : public State {
public:
    GameState();
    GameState(const GameState& orig);
    virtual ~GameState();
    GameState &operator = (const GameState &);
    static GameState * Instance();
    
    void initEntities();
    void eventManager();
    void update();
    void render(bool interpolation = true);
    void pause();
    void resume();
    void deleteState();
    
    Noma * getNoma() { return noma; }
    std::vector<BaseGameEntity *> getEntities(){ return entities; }
    
    World * getCurrentWorld(){ return currentWorld; }
    Environment * getEnvironment(){ return environment; }
    void lowerNomaParameters ();
    BaseGameEntity * getGameEntityByIndex(int i){ return entities[i]; }
    PhysicsEngine * getPhysicsEngine(){ return physics; }
    
    void changeCurrentWorld(std::string world);
    
    HUD* getHUD(){ return hud; }

    
private:
    static GameState * pinstance;
    
    std::vector<BaseGameEntity *> entities;
    std::vector<BaseGameEntity *>::iterator i;
    
    Noma *noma;
    World *currentWorld;
    Environment *environment;
    PhysicsEngine *physics;
    
    bool downKey;
    bool enterKey;
    
    HUD *hud;
    GUIText * environmentInfo;
    float frame;
    
    
};

#endif	/* GAMESTATE_H */

