/* 
 * File:   PopupState.cpp
 * Author: laurasirventcollado
 * 
 * Created on 19 de marzo de 2014, 13:32
 */

#include "../headers/PopupState.h"
#include "../headers/GraphicEngine.h"
#include "../headers/EventManager.h"
#include "../headers/Game.h"

PopupState::PopupState() {
    type = State::Popup;
    int w = GraphicEngine::Instance()->getWidth();
    int h = GraphicEngine::Instance()->getHeight();
    int border = 100;
    counter = 0;

    demoTitles.push_back(L"EJECUTABLE 8.1");
    demoTitles.push_back(L"EJECUTABLE 8.2");
    demoTitles.push_back(L"EJECUTABLE 8.3");
    demoExplanations.push_back(L"Visualizacion de maquina de estados y personalidad, interaccion con Noma.");
    demoExplanations.push_back(L"Visualizacion de propagacion a los vecinos.");
    demoExplanations.push_back(L"Visualizacion de la IA en un mapa real del juego");

    //GUIBackground * background = new GUIBackground(Vector3f(2*border,border), Vector3f(w-2*border,h-border), new RGBA(0.69,0.74,0.84,1.0), new RGBA(0.35,0.38,0.53,1.0));
    GUIBackground * background = new GUIBackground(Vector3f(0, 0), Vector3f(w, h), new RGBA(0.17, 0.17, 0.17, 1.0), new RGBA(0.17, 0.17, 0.17, 1.0));
    addGUIElement(background);

    currentTitle = new GUIText(Vector3f(w / 2, h / 2 - border + 20), GUIText::Center, 0, demoTitles[counter], "Nexa bold.otf", 20);
    addGUIElement(currentTitle);

    GUIButton *gLeftButton = new GUIButton(0, Vector3f(2 * border - 20, h / 2 - border + 60), Vector3f(2 * border - 10, h / 2 - border + 80), GUIButton::RightArrow, true);
    addGUIElement(gLeftButton);
    currentExplanation = new GUIText(Vector3f(w / 2, h / 2 - border + 60), GUIText::Center, 0, demoExplanations[counter], "Lekton-Regular.ttf", 14);
    addGUIElement(currentExplanation);
    GUIButton *gRightButton = new GUIButton(1, Vector3f(w - (2 * border - 20), h / 2 - border + 60), Vector3f(w - (2 * border - 10), h / 2 - border + 80), GUIButton::RightArrow, true);
    addGUIElement(gRightButton);

    GUIButton *play = new GUIButton(2, Vector3f(w / 2, h / 2 - border + 130), GUIButton::Center, L"JUGAR", true, "Nexa Bold.otf", 16);
    play->setBoundingBoxColor(new RGBA(1.0, 1.0, 1.0, 1.0));
    play->setDrawBoundingBox(true);
    play->setColor(new RGBA(0.17, 0.17, 0.17, 1.0));
    addGUIElement(play);
    
    escapePressed = false;

}

PopupState::PopupState(const PopupState& orig) {
}

PopupState::~PopupState() {
}

void PopupState::update() {
    currentTitle->setText(demoTitles.at(counter));
    currentExplanation->setText(demoExplanations.at(counter));
}

void PopupState::render(bool interpolation) {
    GraphicEngine::Instance()->render(interpolation);
}

void PopupState::deleteState() {

}

void PopupState::pause() {
    GraphicEngine::Instance()->deleteGUIEntities();
}

void PopupState::resume() {
    escapePressed = false;
}

void PopupState::eventManager() {

    if (EventManager::Instance()->isKeyUp(KEY_ESCAPE) && escapePressed) {
        Game::Instance()->setState(MainMenuState::Instance());
        escapePressed = false;
    }
    if (EventManager::Instance()->isKeyDown(KEY_ESCAPE)){
        escapePressed = true;
    }
}

PopupState * PopupState::pinstance = 0;

PopupState * PopupState::Instance() {
    if (pinstance == 0) {
        pinstance = new PopupState;
    }
    return pinstance;
}

void PopupState::increaseDemo() {
    counter++;
    if (counter == demoTitles.size())
        counter--;
}

void PopupState::decreaseDemo() {
    counter--;
    if (counter < 0)
        counter = 0;
}
