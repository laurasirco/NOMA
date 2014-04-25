/* 
 * File:   OptionMenuState.cpp
 * Author: MAC
 * 
 * Created on 15 de octubre de 2013, 17:31
 */

#include "../headers/OptionMenuState.h"
#include "../headers/GraphicEngine.h"
#include "../headers/EventManager.h"
#include "../headers/Game.h"
#include <stdio.h>
#include <wchar.h>

OptionMenuState::OptionMenuState() {
    
    type = State::Option;
    int w = GraphicEngine::Instance()->getWidth();
    int h = GraphicEngine::Instance()->getHeight();
    
    resolutionsVector.push_back(L"1280 x 720");
    resolutionsVector.push_back(L"1920 x 1080");
    resolutionsCounter = 0;
    
    graphicsVector.push_back(L"BAJA");
    graphicsVector.push_back(L"MEDIA");
    graphicsVector.push_back(L"ALTA");
    graphicsCounter = 0;
    
    //GUIBackground * background = new GUIBackground(Vector3f(0,0), Vector3f(w,h), new RGBA(0.69,0.74,0.84,1.0), new RGBA(0.35,0.38,0.53,1.0));
    GUIBackground * background = new GUIBackground(Vector3f(0,0), Vector3f(w,h), new RGBA(0.17,0.17,0.17,1.0), new RGBA(0.17,0.17,0.17,1.0));
    addGUIElement(background);
    
    GUIText *options = new GUIText(Vector3f(w*0.96,h*0.07), GUIText::Right, 0, L"OPCIONES", "Nexa bold.otf", 18);
    addGUIElement(options);
    
    /*LEFT*/
    
    GUIText *fx = new GUIText(Vector3f(w*0.16,h*0.40), GUIText::Right, 0, L"EFECTOS", "Nexa bold.otf", 18);
    addGUIElement(fx);
    fxSlider = new GUISlider(0, Vector3f(w*0.19, h*0.40 + 15), Vector3f(w*0.35, h*0.40 + 15), 0, 100, 50);
    addGUIElement(fxSlider);
    fxNumber = new GUIText(Vector3f(w*0.38,h*0.40), GUIText::Left, 0, L"50", "Nexa bold.otf", 18);
    addGUIElement(fxNumber);
    
    GUIText *music = new GUIText(Vector3f(w*0.16,h*0.49), GUIText::Right, 0, L"MUSICA", "Nexa bold.otf", 18);
    addGUIElement(music);
    musicSlider = new GUISlider(0, Vector3f(w*0.19,h*0.49 + 15), Vector3f(w*0.35, h*0.49 + 15), 0, 100, 50);
    addGUIElement(musicSlider);
    musicNumber = new GUIText(Vector3f(w*0.38,h*0.49), GUIText::Left, 0, L"50", "Nexa bold.otf", 18);
    addGUIElement(musicNumber);
    
    GUIText *voices = new GUIText(Vector3f(w*0.16,h*0.58), GUIText::Right, 0, L"VOCES", "Nexa bold.otf", 18);
    addGUIElement(voices);
    voicesSlider = new GUISlider(0, Vector3f(w*0.19, h*0.58 + 15), Vector3f(w*0.35, h*0.58 + 15), 0, 100, 50);
    addGUIElement(voicesSlider);
    voicesNumber = new GUIText(Vector3f(w*0.38,h*0.58), GUIText::Left, 0, L"50", "Nexa bold.otf", 18);
    addGUIElement(voicesNumber);
    
    /*RIGHT*/
    
    GUIText *resolution = new GUIText(Vector3f(w*0.78,h*0.42), GUIText::Right, 0, L"RESOLUCION", "Nexa bold.otf", 18);
    addGUIElement(resolution);
    GUIButton *resLeftButton = new GUIButton(0, Vector3f(w*0.815,h*0.43), Vector3f(w*0.82,h*0.44), GUIButton::RightArrow, true);
    addGUIElement(resLeftButton);
    resolutionValue = new GUIText(Vector3f(w*0.83,h*0.42 - 5), GUIText::Left, 0, resolutionsVector.at(resolutionsCounter), "Nexa bold.otf", 18);
    addGUIElement(resolutionValue);
    GUIButton *resRightButton = new GUIButton(1, Vector3f(w*0.945,h*0.43), Vector3f(w*0.95,h*0.44), GUIButton::LeftArrow, true);
    addGUIElement(resRightButton);
    
    
    GUIText *graphics = new GUIText(Vector3f(w*0.78,h*0.51), GUIText::Right, 0, L"CALIDAD", "Nexa bold.otf", 18);
    addGUIElement(graphics);
    GUIButton *gLeftButton = new GUIButton(2, Vector3f(w*0.815,h*0.52), Vector3f(w*0.82,h*0.53), GUIButton::RightArrow, true);
    addGUIElement(gLeftButton);
    graphicsValue = new GUIText(Vector3f(w*0.83,h*0.51), GUIText::Left, 0, graphicsVector.at(graphicsCounter), "Nexa bold.otf", 18);
    addGUIElement(graphicsValue);
    GUIButton *gRightButton = new GUIButton(3, Vector3f(w*0.945,h*0.52), Vector3f(w*0.95,h*0.53), GUIButton::LeftArrow, true);
    addGUIElement(gRightButton);
    
}


void OptionMenuState::eventManager() {
    
    if (EventManager::Instance()->isKeyDown(KEY_ESCAPE)) {
        Game::Instance()->setState(MainMenuState::Instance());
    }
    
}

void OptionMenuState::update() {

    int fxValue = (int)fxSlider->getValue();

    wchar_t newfxNumber[16];
    swprintf(newfxNumber, sizeof(newfxNumber) / sizeof(*newfxNumber), L"%d", fxValue);
    
    fxNumber->setText((const wchar_t *)newfxNumber);
    
    int musicValue = (int)musicSlider->getValue();

    wchar_t newMusicNumber[16];
    swprintf(newMusicNumber, sizeof(newMusicNumber) / sizeof(*newMusicNumber), L"%d", musicValue);
    
    musicNumber->setText((const wchar_t *)newMusicNumber);
    
    int voicesValue = (int)voicesSlider->getValue();

    wchar_t newVoicesNumber[16];
    swprintf(newVoicesNumber, sizeof(newVoicesNumber) / sizeof(*newVoicesNumber), L"%d", voicesValue);
   
    voicesNumber->setText((const wchar_t *)newVoicesNumber);
    
    resolutionValue->setText(resolutionsVector.at(resolutionsCounter));
    graphicsValue->setText(graphicsVector.at(graphicsCounter));
    
}

void OptionMenuState::render(bool interpolation) {
    GraphicEngine::Instance()->render(interpolation);
}

void OptionMenuState::deleteState() {

}

void OptionMenuState::pause() {
    GraphicEngine::Instance()->deleteGUIEntities();
}

void OptionMenuState::resume() {
}

OptionMenuState::OptionMenuState(const OptionMenuState& orig) {
}

OptionMenuState::~OptionMenuState() {
    GraphicEngine::Instance()->deleteGUIEntities();
    pinstance = 0;
}

OptionMenuState * OptionMenuState::pinstance = 0;

OptionMenuState * OptionMenuState::Instance() {
    if (pinstance == 0) {
        pinstance = new OptionMenuState;
    }
    return pinstance;
}

void OptionMenuState::increaseGraphics(){
    graphicsCounter++;
    if(graphicsCounter == graphicsVector.size())
        graphicsCounter--;
}

void OptionMenuState::decreaseGraphics(){
    graphicsCounter--;
    if(graphicsCounter < 0)
        graphicsCounter = 0;
}

void OptionMenuState::increaseResolution(){
    resolutionsCounter++;
    if(resolutionsCounter == resolutionsVector.size())
        resolutionsCounter--;
}

void OptionMenuState::decreaseResolution(){
    resolutionsCounter--;
    if(resolutionsCounter < 0)
        resolutionsCounter = 0;
    
}