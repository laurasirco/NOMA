/* 
 * File:   Game.h
 * Author: MAC
 *
 * Created on 15 de octubre de 2013, 17:18
 */

#ifndef GAME_H
#define	GAME_H
#include <stack>
#include "State.h"
#include "GraphicEngine.h"
#include <iostream> 
#include <string.h>

using namespace std;
#define FPS 1/60.0

class Game {
public:
    Game();
    Game(const Game& orig);
    virtual ~Game();
    Game &operator = (const Game &);
    static Game *Instance();
    void init();
    void eventManager();
    void update();
    void render(bool interpolation = true);
    void changeState(State * s){currentState = s;};
    void setState(State *s);
    void popCurrentState();
    State * getCurrentState(){ return currentState; }
    
    std::stack<State*> &getState(){return states;};
    void deleteGame();
    double getDeltaTime(){ return deltaTime; }
    void setDeltaTime(double dt){ deltaTime = dt; }
    void setDemoMode(int d){ demoMode = d; }
    int getDemoMode(){ return demoMode; }
    void toggleDepurationMode(){ GraphicEngine::Instance()->toggleDepurationMode(); }
    
    int addEntity(){ nEntities++; return nEntities-1; }
    int getNumberOfEntities(){ return nEntities; }
    void resetNumberOfEntities(){ nEntities = 0; }
    
    void setWhichGraphicConnector(int w){ whichGraphicConnector = w; }
    int getWhichGraphicConnector(){ return whichGraphicConnector; }
    
        
    bool getDebugMode(){ return debugMode; }
    void setDebugMode(bool d){ debugMode = d; }
    
    void createNewGame();
    
private:
    static Game *pinstance;
    State *currentState;
    std::stack<State*> states;
    double deltaTime;
    
    int nEntities;
    
    int demoMode;
    
    int whichGraphicConnector;
    
    bool debugMode; 
    
    char * ID;
    char * password;

    char * generateGameID();
    char * generateGamePassword();
    
};

#endif	/* GAME_H */

