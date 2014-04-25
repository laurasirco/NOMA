/* 
 * File:   MapState.cpp
 * Author: MAC
 * 
 * Created on 15 de octubre de 2013, 17:34
 */

#include "../headers/MapState.h"
#include "../headers/GraphicEngine.h"
#include "../headers/EventManager.h"
#include "../headers/GameState.h"
#include "../headers/Game.h"

#include <iostream>
#include <cmath>

#define DEG2RAD 3.14159/180;

using namespace std;

MapState::MapState() {

    type = State::Map;
    enterKey = false;
    angle = 0;

    int oRadius[] = {70, 120, 190, 260, 360, 450, 580};
    int pSize[] = {20, 25, 30, 35, 40, 55, 60};
    int pAngles[] = {-0, 0, -0, -0, -0, -0, -0};
    const wchar_t * pTexts[] = {L"0", L"1", L"2", L"3", L"4", L"5", L"6"};

    int backgroundH = GraphicEngine::Instance()->getHeight() - 20;
    int backgroundW = GraphicEngine::Instance()->getWidth() - 20;

    GUIBackground *background = new GUIBackground(Vector3f(20, 20), Vector3f(backgroundW, backgroundH), new RGBA(0.4, 0.4, 0.4, 0.5));
    addGUIElement(background);

    GUIButton *sun = new GUIButton(-1, Vector3f(200, backgroundH / 2), GUIButton::Center, L"7", true, "Planets.ttf", 50);
    sun->setDisabledColor(new RGBA(1.0, 0.98, 0.80, 1.0));
    sun->setEnabled(false);
    addGUIElement(sun);
    center = Vector3f(200, backgroundH / 2);
    std::vector<int> reachable = GameState::Instance()->getCurrentWorld()->getReachableWorlds();
    int c = 0;

    for (int i = 0; i < 7; i++) {
        GUIButton *planet = new GUIButton(i, Vector3f((center.X + oRadius[i]), (backgroundH / 2)), GUIButton::Center, pTexts[i], true, "Planets.ttf", pSize[i]);
        planet->setColor(new RGBA(0.5, 1, 0.83, 0.6));
        planet->setHoverColor(new RGBA(0.5, 1, 0.83, 1.0));
        planet->setDisabledColor(new RGBA(1.0, 1.0, 1.0, 0.6));
        planet->rotate(center, pAngles[i], oRadius[i]);
        planet->setEnabled(false);
        if (reachable[c] == i) {
            planet->setEnabled(true);
            c++;
        }
        addGUIElement(planet);
        planets.push_back(planet);
        GUIOrbit *orbit = new GUIOrbit(oRadius[i], Vector3f(200, backgroundH / 2), planet->getBoundingBox().Y);
        orbit->setColor(new RGBA(0.9, 0.9, 0.9, 0.3));
        orbit->setDisplacement(pAngles[i]);
        addGUIElement(orbit);
        orbits.push_back(orbit);
    }

}

MapState::MapState(const MapState& orig) {
}

MapState::~MapState() {
}

MapState * MapState::pinstance = 0;

MapState * MapState::Instance() {
    if (pinstance == 0) {
        pinstance = new MapState;
    }
    return pinstance;
}

void MapState::eventManager() {

    if (EventManager::Instance()->isKeyDown(KEY_RETURN)) {
        enterKey = true;
    }
    if (EventManager::Instance()->isKeyUp(KEY_RETURN) && enterKey) {
        enterKey = false;
        Game::Instance()->setState(GameState::Instance());
    }
}

void MapState::render(bool interpolation) {
    GraphicEngine::Instance()->render(interpolation);
}

void MapState::update() {

    for (int i = 0; i < planets.size(); i++) {
        planets[i]->incrementRotationAngle(0.01);
        planets[i]->rotate(center, planets[i]->getRotationAngle(), orbits[i]->getRadius());
        orbits[i]->incrementDisplacement(0.01);
    }

}

void MapState::resume() {

    if (GameState::Instance()->getNoma()->canTravel())
        setTravellingAllowed(true);
    else
        setTravellingAllowed(false);
}

void MapState::pause() {
}

void MapState::deleteState() {
}

void MapState::setTravellingAllowed(bool t) {

    std::vector<int> reachable = GameState::Instance()->getCurrentWorld()->getReachableWorlds();
    int c = 0;
    for (int i = 0; i < planets.size(); i++) {
        
        planets[i]->setEnabled(false);
        if (t == true) {
            if (reachable[c] == i) {
                planets[i]->setEnabled(true);
                c++;
            }
        } else
            planets[i]->setEnabled(t);

    }
}