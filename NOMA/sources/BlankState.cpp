/* 
 * File:   BlankState.cpp
 * Author: laurasirventcollado
 * 
 * Created on 14 de marzo de 2014, 18:02
 */

#include "../headers/BlankState.h"
#include "../headers/GraphicEngine.h"
#include "../headers/EventManager.h"
#include "../headers/GUIBackground.h"
#include "../headers/GameState.h"
#include "../headers/Game.h"

BlankState::BlankState() {
    changed = false;
    type = State::Blank;
    color = new RGBA(1.0,1.0,1.0,0.0);
    int backgroundH = GraphicEngine::Instance()->getHeight();
    int backgroundW = GraphicEngine::Instance()->getWidth();

    GUIBackground *background = new GUIBackground(Vector3f(0, 0), Vector3f(backgroundW, backgroundH), color);
    addGUIElement(background);
}

BlankState::BlankState(const BlankState& orig) {
}

BlankState::~BlankState() {
    GraphicEngine::Instance()->deleteGUIEntities();
    pinstance = 0;
}

BlankState * BlankState::pinstance = 0;

BlankState * BlankState::Instance() {
    if (pinstance == 0) {
        pinstance = new BlankState;
    }
    return pinstance;
}

void BlankState::eventManager() {
    

}

void BlankState::update() {
        
    if(color->a < 1.0 && !changed)
        color->a += 0.01;
    else if(color->a >= 1.0 && !changed){
        GameState::Instance()->changeCurrentWorld(newWorld);
        changed = true;
    }
    
    
    if(changed)
        color->a -= 0.01;
    if(color->a <= 0.0 && changed)
        Game::Instance()->setState(GameState::Instance());

}

void BlankState::render(bool interpolation) {
    GraphicEngine::Instance()->render(interpolation);
}

void BlankState::deleteState() {

}

void BlankState::pause() {
    GraphicEngine::Instance()->deleteGUIEntities();
}

void BlankState::resume() {
    changed = false;
    color->a = 0.0;
}