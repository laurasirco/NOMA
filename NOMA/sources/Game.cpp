/* 
 * File:   Game.cpp
 * Author: MAC
 * 
 * Created on 15 de octubre de 2013, 17:18
 */

#include "../headers/Game.h"
#include "../headers/MainMenuState.h"
#include "../headers/GameState.h"
#include "../headers/PopupState.h"
#include "../headers/LoginState.h"
#include "../headers/PhysicsEngine.h"
#include <typeinfo>

Game::Game() {
    deltaTime = 0;
    nEntities = 0;
    demoMode = 0;
    debugMode = false;
}

Game::Game(const Game& orig) {
}

Game::~Game() {
}

Game* Game::pinstance = 0;
Game* Game::Instance()
{
    if(pinstance == 0)
    {
        pinstance = new Game;
    }
    return pinstance;
}

void Game::createNewGame(){
    
    //Generate ID and password
    ID = generateGameID();
    password = generateGamePassword();
    
    //Call server and register new game
    
    //Create initial JSON and save it
}

char * Game::generateGameID(){
    
    
}

char * Game::generateGamePassword(){
    
    
}

void Game::init()
{
    /*if(whichGraphicConnector == 0){
       currentState = MainMenuState::Instance();
    }
    else{
        GameState *gameState = GameState::Instance();
        gameState->initEntities();
        currentState = gameState;
    }*/
    currentState = MainMenuState::Instance();
    states.push(currentState);
    //currentState = LoginState::Instance();
    //states.push(currentState);
}

void Game::eventManager()
{
    currentState->eventManager();
}

void Game::update()
{
    currentState->update();
}

void Game::render(bool interpolation)
{
    currentState->render(interpolation);
}

void Game::setState(State* s){
    //states.pop();
    //delete(currentState);
    states.top()->pause();
        std::cout << "Stack has " << states.size() <<" states. Current is " << states.top()->getType() << std::endl;

    switch(currentState->getType()){
        case State::Badget:
            break;
        case State::Game:
            if(s->getType() == State::MainMenu){
                delete(currentState);
                states.pop();
            }
            if(s->getType() == State::Popup){
                delete(currentState);
                states.pop();
            }
            else if(s->getType() == State::Map){
                states.push(s);
            }
            break;
        case State::MainMenu:
            if(s->getType() == State::Game){
                GameState *gameState = (GameState*)s;
                gameState->initEntities();
            }
            else if(s->getType() == State::Option){
                states.pop();
            }
            
            states.push(s);
            break;
        case State::Map:
            states.pop();
            if(s->getType() == State::Blank)
                states.push(s);
            break;
        case State::Option:
            states.pop();
            states.push(s);
            break;
        case State::Blank:
            states.pop();
            break;
        case State::Popup:
            if(s->getType() == State::Game){
                GameState *gameState = (GameState*)s;
                gameState->initEntities();
                states.push(s);
            }
            if(s->getType() == State::MainMenu){
                PopupState::Instance()->resetCounter();
                states.pop();
            }
            break;
    }

    currentState = s;
    EventManager::Instance()->resetAllKeys();
    currentState->resume();
    update();
    if (typeid (* currentState) == typeid (GameState))
        GraphicEngine::Instance()->addDebugInterface();
    
    std::cout << "Stack has " << states.size() <<" states. Current is " << states.top()->getType() << std::endl;
}

void Game::popCurrentState(){
    
}

void Game::deleteGame(){
    
}
