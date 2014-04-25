/* 
 * File:   EventManager.cpp
 * Author: MAC
 * 
 * Created on 15 de octubre de 2013, 17:39
 */

#include "../headers/EventManager.h"
#include "../headers/GameState.h"
#include "../headers/MapState.h"
#include "../headers/OptionMenuState.h"
#include "../headers/BlankState.h"
#include "../headers/PopupState.h"
#include "../headers/Game.h"
#include "../headers/GraphicEngine.h"
#include "../headers/GUIElement.h"
#include "../headers/GUIButton.h"
#include "../headers/GUISlider.h"
#include "../headers/TAGConnector.h"
#include "../headers/AudioEngine.h"
#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <sstream>

using namespace std;

bool EventManager::KeyDown[255] = {false};
int EventManager::mouseX = 0;
int EventManager::mouseY = 0;

EventManager::EventManager() {

}

EventManager::EventManager(const EventManager& orig) {
}

EventManager::~EventManager() {
}

EventManager * EventManager::pinstance = 0;

EventManager * EventManager::Instance() {
    if (pinstance == 0) {
        pinstance = new EventManager;
    }
    return pinstance;
}

bool EventManager::OnEvent(const SEvent& event) {

    if (event.GUIEvent.EventType == EGET_BUTTON_CLICKED) {
        cout << "button " << event.GUIEvent.Caller->getID() << endl;
        if ((int) event.GUIEvent.Caller->getID() < 5) {
            Game::Instance()->setDemoMode((int) event.GUIEvent.Caller->getID() + 1);
            Game::Instance()->setState(GameState::Instance());
        } else if ((int) event.GUIEvent.Caller->getID() == 5) {
            Game::Instance()->toggleDepurationMode();
        } else if ((int) event.GUIEvent.Caller->getID() == 6) {
            //GraphicEngine::Instance()->setSubtitleSpace(true);
            //GraphicEngine::Instance()->emptySubtitle();
            //GameState::Instance()->getNoma()->setInteracting(false);
            Game::Instance()->setState(MainMenuState::Instance());
        }
    }

    switch (event.EventType) {
        case irr::EET_KEY_INPUT_EVENT:
            KeyDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
            break;
        case irr::EMIE_LMOUSE_PRESSED_DOWN:
            mouseState.leftButtonDown = true;
            break;
        case irr::EMIE_LMOUSE_LEFT_UP:
            mouseState.leftButtonDown = false;
        case irr::EMIE_MOUSE_MOVED:
            mouseState.Position.X = event.MouseInput.X;
            mouseState.Position.Y = event.MouseInput.Y;
            break;
        default:
            break;
    }
    return false;
}

void EventManager::resetAllKeys() {
    for (int i = 0; i < 255; i++) {
        KeyDown[i] = false;
    }
}

bool EventManager::isKeyDown(EKEY_CODE keyCode) const {
    return KeyDown[keyCode];
}

bool EventManager::isKeyUp(EKEY_CODE keyCode) const {
    return !KeyDown[keyCode];
}

void EventManager::keyPressed(unsigned char key, int x, int y) {

    if (key == 'w') {
        KeyDown[KEY_KEY_W] = true;
    }
    else if (key == 's')
        KeyDown[KEY_KEY_S] = true;
    else if (key == 'a')
        KeyDown[KEY_KEY_A] = true;
    else if (key == 'd')
        KeyDown[KEY_KEY_D] = true;
    else if (key == 'e')
        KeyDown[KEY_KEY_E] = true;
    else if (key == ' ') {
        KeyDown[KEY_SPACE] = true;
        
    }
    else if (key == 'z')
        KeyDown[KEY_KEY_Z] = true;
    else if (key == 13)
        KeyDown[KEY_RETURN] = true;
    else if (key == 27)
        KeyDown[KEY_ESCAPE] = true;
    else if (key == 49)
        KeyDown[KEY_KEY_1] = true;
}

void EventManager::keyUp(unsigned char key, int x, int y) {

    if (key == 'w')
        KeyDown[KEY_KEY_W] = false;
    else if (key == 's')
        KeyDown[KEY_KEY_S] = false;
    else if (key == 'a')
        KeyDown[KEY_KEY_A] = false;
    else if (key == 'd')
        KeyDown[KEY_KEY_D] = false;
    else if (key == 'e')
        KeyDown[KEY_KEY_E] = false;
    else if (key == ' ')
        KeyDown[KEY_SPACE] = false;
    else if (key == 'z')
        KeyDown[KEY_KEY_Z] = false;
    else if (key == 13)
        KeyDown[KEY_RETURN] = false;
    else if (key == 27)
        KeyDown[KEY_ESCAPE] = false;
    else if (key == 49)
        KeyDown[KEY_KEY_1] = false;

}

void EventManager::passiveMouseMoved(int x, int y) {

    mouseX = x;
    mouseY = y;

    std::vector<GUIElement*> GUI = Game::Instance()->getCurrentState()->getGUIElements();
    for (int i = 0; i < GUI.size(); i++) {
        if ((typeid (* GUI.at(i)) == typeid (GUIButton))) {
            GUIButton *button = (GUIButton *) GUI.at(i);
            button->setHover(x, y);
        }
    }

}

void EventManager::mouseMoved(int x, int y) {

    std::vector<GUIElement*> GUI = Game::Instance()->getCurrentState()->getGUIElements();
    for (int i = 0; i < GUI.size(); i++) {
        if ((typeid (* GUI.at(i)) == typeid (GUISlider))) {
            GUISlider *slider = (GUISlider *) GUI.at(i);
            slider->setDragging(x, y);
        }
    }

}

void EventManager::processMouse(int button, int state, int x, int y) {

    int idButton = -1;
    bool clicked = false;
    int i = 0;

    if (state == 1) {

        if(Game::Instance()->getCurrentState()->getType() == State::Login){
           
            std::vector<GUIElement*> GUI = Game::Instance()->getCurrentState()->getGUIElements();
            while(!clicked && i < GUI.size()){
                if ((typeid (* GUI.at(i)) == typeid (GUIText))) {
                    GUIText *text = (GUIText *) GUI.at(i);
                    if(text->isEditable()){
                        clicked = text->checkClick(x, y);
                    }
                }
            }
            
            if(clicked){
                idButton = GUI.at(i-1)->getID();
                if(idButton == 0){
                    cout<<"Username"<<endl;
                }
                else if(idButton == 1){
                    cout<<"Password"<<endl;
                }
            }
        }

        else {
            std::vector<GUIElement*> GUI = Game::Instance()->getCurrentState()->getGUIElements();
            while (!clicked && i < GUI.size()) {
                if ((typeid (* GUI.at(i)) == typeid (GUIButton))) {
                    GUIButton *button = (GUIButton *) GUI.at(i);
                    clicked = button->checkClick(x, y);
                }
                i++;
            }
            if (clicked) {
                idButton = GUI.at(i - 1)->getID();

                if (Game::Instance()->getCurrentState()->getType() == State::MainMenu) {
                    //CALL FUNCTIONS
                    switch (idButton) {
                        case 1: //DEMO 1
                            Game::Instance()->setDemoMode(idButton);
                            Game::Instance()->setState(PopupState::Instance());
                            break;
                        case 2: //DEMO 2
                            Game::Instance()->setDemoMode(3);
                            Game::Instance()->setState(GameState::Instance());
                            break;
                        case 3: //CONTINUE
                            MainMenuState::Instance()->showSavedGames();
                            break;
                        case 5: //OPTIONS
                            Game::Instance()->setState(OptionMenuState::Instance());
                            break;
                        case 6: //EXIT
                            TAGConnector::close();
                            break;
                        case 8:
                            Game::Instance()->setDebugMode(!Game::Instance()->getDebugMode());
                            if (!Game::Instance()->getDebugMode()) {
                                MainMenuState::Instance()->getDebugButton()->setDrawBoundingBox(false);
                                MainMenuState::Instance()->getDebugButton()->setColor(new RGBA(0.95, 0.95, 0.95, 1.0));
                            } else {
                                MainMenuState::Instance()->getDebugButton()->setDrawBoundingBox(true);
                                MainMenuState::Instance()->getDebugButton()->setColor(new RGBA(0.1, 0.1, 0.1, 1.0));
                                MainMenuState::Instance()->getDebugButton()->setBoundingBoxColor(new RGBA(0.95, 0.95, 0.95, 1.0));
                            }
                            cout << "debug: " << Game::Instance()->getDebugMode() << endl;
                        default:
                            break;
                    }
                } else if (Game::Instance()->getCurrentState()->getType() == State::Map) {

                    //Travel
                    if (idButton >= 0) {
                        std::ostringstream oss;
                        oss << "World" << idButton << "/world" << ".json";
                        std::string path = oss.str();
                        cout << "Change world here to " << path << endl;

                        //Set BlankState change to world
                        BlankState::Instance()->setNewWorld(path);

                        //set State to BlankState
                        Game::Instance()->setState(BlankState::Instance());
                    }
                } else if (Game::Instance()->getCurrentState()->getType() == State::Option) {
                    switch (idButton) {
                        case 0:
                            OptionMenuState::Instance()->decreaseResolution();
                            break;
                        case 1:
                            OptionMenuState::Instance()->increaseResolution();
                            break;
                        case 2:
                            OptionMenuState::Instance()->decreaseGraphics();
                            break;
                        case 3:
                            OptionMenuState::Instance()->increaseGraphics();
                            break;
                        default:
                            break;
                    }
                }
                else if (Game::Instance()->getCurrentState()->getType() == State::Popup) {
                    switch (idButton) {
                        case 0:
                            PopupState::Instance()->decreaseDemo();
                            break;
                        case 1:
                            PopupState::Instance()->increaseDemo();
                            break;
                        case 2:
                            Game::Instance()->setDemoMode(PopupState::Instance()->getSelectedDemo());
                            Game::Instance()->setState(GameState::Instance());
                            break;
                    }
                }
            }
        }
    }

}
