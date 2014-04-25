/* 
 * File:   LoginState.cpp
 * Author: laurasirventcollado
 * 
 * Created on 18 de abril de 2014, 12:19
 */

#include "../headers/LoginState.h"
#include "../headers/GraphicEngine.h"
#include "../headers/EventManager.h"
#include "../headers/Game.h"

LoginState::LoginState() {
    type = State::Login;
    
    int w = GraphicEngine::Instance()->getWidth();
    int h = GraphicEngine::Instance()->getHeight();
    
    GUIBackground * background = new GUIBackground(Vector3f(300, 150), Vector3f(w - 300, h - 150), new RGBA(0.26, 0.26, 0.26, 1.0), new RGBA(0.26, 0.26, 0.26, 1.0));
    addGUIElement(background);
    
    usernameText = new GUIText(Vector3f(400,200), GUIText::Left, 0, L"Username", "Lekton-Regular.ttf", 16, GUIText::TwoD);
    usernameText->setID(0);
    addGUIElement(usernameText);
    
}

LoginState::LoginState(const LoginState& orig) {
}

LoginState::~LoginState() {
}

LoginState * LoginState::pinstance = 0;

LoginState * LoginState::Instance(){
    if(pinstance == 0){
        pinstance = new LoginState;
    }
    return pinstance;
}


void LoginState::update() {

}

void LoginState::render(bool interpolation) {
    GraphicEngine::Instance()->render(interpolation);
}

void LoginState::deleteState() {

}

void LoginState::pause() {
    GraphicEngine::Instance()->deleteGUIEntities();
}

void LoginState::resume() {

}

void LoginState::eventManager() {

}