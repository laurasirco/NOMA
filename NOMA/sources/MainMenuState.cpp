/* 
 * File:   MainMenuState.cpp
 * Author: MAC
 * 
 * Created on 15 de octubre de 2013, 17:32
 */

#include "../headers/GraphicEngine.h"
#include "../headers/MainMenuState.h"
#include "../headers/GUIButton.h"
#include "../headers/GUISlider.h"
#include "../headers/GUIBackground.h"

MainMenuState::MainMenuState() {

    type = State::MainMenu;
    int w = GraphicEngine::Instance()->getWidth();
    int h = GraphicEngine::Instance()->getHeight();
    isSavedGamesShowing = false;

    //GUIBackground * background = new GUIBackground(Vector3f(0,0), Vector3f(w,h), new RGBA(0.69,0.74,0.84,1.0), new RGBA(0.35,0.38,0.53,1.0));
    GUIBackground * background = new GUIBackground(Vector3f(0,0), Vector3f(w,h), new RGBA(0.17,0.17,0.17,1.0), new RGBA(0.17,0.17,0.17,1.0));
    addGUIElement(background);
    
    GUIButton *button1 = new GUIButton(3, Vector3f(w*0.96,h*0.07), GUIButton::Right , L"NUEVA PARTIDA", true, "Nexa bold.otf", 20);
    addGUIElement(button1);
    GUIButton *button2 = new GUIButton(4, Vector3f(w*0.96,h*0.07 +40), GUIButton::Right , L"LOGROS", true, "Nexa bold.otf", 20);
    addGUIElement(button2);
    GUIButton *button3 = new GUIButton(5, Vector3f(w*0.96,h*0.07 +80), GUIButton::Right , L"OPCIONES", true, "Nexa bold.otf", 20);
    addGUIElement(button3);
    GUIButton *button4 = new GUIButton(6, Vector3f(w*0.96,h*0.07 +120), GUIButton::Right , L"SALIR", true, "Nexa bold.otf", 20);
    addGUIElement(button4);
    //GUIButton *button5 = new GUIButton(7, Vector3f(w*0.96,h*0.07 +160), GUIButton::Right , L"SALIR", true, "Nexa bold.otf", 20);
    //addGUIElement(button5);
    
    debugButton = new GUIButton(8, Vector3f(w*0.015,h*0.95), GUIButton::Left , L"DEPURACION", true, "Nexa bold.otf", 16);
    addGUIElement(debugButton);
    
    GUIButton *demo1 = new GUIButton(1, Vector3f(w*0.65, h*0.07), GUIButton::Right, L"EJECUTABLE 8", true, "Nexa bold.otf", 16);
    demoButtons.push_back(demo1);
    GUIButton *demo2 = new GUIButton(2, Vector3f(w*0.65, h*0.07 + 40), GUIButton::Right, L"EJECUTABLE 9", true, "Nexa bold.otf", 16);
    demoButtons.push_back(demo2);
    
    MenuItem i1;
    i1.x1 = 0;
    i1.x2 = 300;
    i1.y1 = 200;
    i1.y2 = 240;
    i1.title = L"Citizen's AI";
    i1.tooltip = L"Demostración de la inteligencia de los ciudadanos";
    menuItems.push_back(i1);

    MenuItem i2;
    i2.x1 = 0;
    i2.x2 = 300;
    i2.y1 = 250;
    i2.y2 = 290;
    i2.title = L"Pathfinding to Noma";
    i2.tooltip = L"Cada ciudadano del juego se desplazará hacia el nodo más cercano a Noma utilizando pathfinding para encontrar la ruta más corta";
    menuItems.push_back(i2);

    MenuItem i3;
    i3.x1 = 0;
    i3.x2 = 300;
    i3.y1 = 300;
    i3.y2 = 340;
    i3.title = L"Flocking";
    i3.tooltip = L"Todos los ciudadanos se desplazarán hacia el final del mapa utilizando flocking para actuar como una masa, y evitando a Noma";
    menuItems.push_back(i3);

    MenuItem i4;
    i4.x1 = 0;
    i4.x2 = 300;
    i4.y1 = 350;
    i4.y2 = 390;
    i4.title = L"Environment";
    i4.tooltip = L"Las entradas por teclado generarán un ambiente y su consecuente salida ambiental, visualizada en los iconos";
    menuItems.push_back(i4);

    GraphicEngine::Instance()->addGUIEntities(menuItems);
}

void MainMenuState::eventManager() {
    if (EventManager::Instance()->isKeyDown(KEY_ESCAPE)) {
        //GraphicEngine::Instance()->close();
        
    }
}

void MainMenuState::update() {

}

void MainMenuState::render(bool interpolation) {
    GraphicEngine::Instance()->render(interpolation);
}

void MainMenuState::deleteState() {

}

void MainMenuState::pause() {
    GraphicEngine::Instance()->deleteGUIEntities();
}

void MainMenuState::resume() {
    
    GraphicEngine::Instance()->addGUIEntities(menuItems);
}

MainMenuState * MainMenuState::pinstance = 0;

MainMenuState * MainMenuState::Instance() {
    if (pinstance == 0) {
        pinstance = new MainMenuState;
    }
    return pinstance;
}

MainMenuState::MainMenuState(const MainMenuState& orig) {
}

MainMenuState::~MainMenuState() {
    GraphicEngine::Instance()->deleteGUIEntities();
    pinstance = 0;
}

void MainMenuState::showSavedGames(){
    
    isSavedGamesShowing = !isSavedGamesShowing;
    
    if(isSavedGamesShowing){
        for(int i = 0; i < demoButtons.size(); i++)
            addGUIElement(demoButtons[i]);
    }
    else{
       for(int i = 0; i < demoButtons.size(); i++)
            removeGUIElement(demoButtons[i]); 
    }
}
