/* 
 * File:   GameState.cpp
 * Author: MAC
 * 
 * Created on 15 de octubre de 2013, 17:29
 */

#include "../headers/GameState.h"
#include "../headers/GraphicEngine.h"
#include "../headers/Citizen.h"
#include "../headers/EventManager.h"
#include "../headers/Parser.h"
#include "../headers/Game.h"
#include "../headers/StandState.h"
#include "../headers/Parser.h"
#include "../headers/MapState.h"
#include "../headers/PopupState.h"
#include "../headers/FlockingState.h"
#include "../headers/AudioEngine.h"
#include <stdlib.h>
#include <ctime>
#include <cmath>
#include <typeinfo>
#include <stdarg.h>
#include <stdio.h>
#include <wchar.h>
#include <string>
#include <sstream>

using namespace std;

GameState::GameState() {

    entities.clear();
    GUIElements.clear();
    type = State::Game;
    downKey = false;
    enterKey = false;
    frame = 0;
    //8.1 
    if (Game::Instance()->getDemoMode() == 0) {
        currentWorld = new World("Demo8.1/world.json");
        physics = new PhysicsEngine(currentWorld->getMapName() + ".obj");

    }//8.2
    else if (Game::Instance()->getDemoMode() == 1) {
        currentWorld = new World("Demo8.2/world.json");
        physics = new PhysicsEngine(currentWorld->getMapName() + ".obj");

    }//8.3
    else if (Game::Instance()->getDemoMode() == 2) {
        currentWorld = new World("Demo8.3/world.json");
        physics = new PhysicsEngine(currentWorld->getMapName() + ".obj");
    }//9
    else if (Game::Instance()->getDemoMode() == 3) {
        currentWorld = new World("World0/world.json");
        physics = new PhysicsEngine(currentWorld->getMapName() + ".obj");
    }

    environment = new Environment;
    hud = new HUD(0);
    addGUIElement(hud);

}

void GameState::initEntities() {

    currentWorld->loadGraphicEntities();


    noma = new Noma(Vector3f(0, 0, 0));
    cout << "noma position: ";
    noma->getPosition().print();
    cout << endl;
    noma->setPosition(0, 0, 0);
    noma->setVelocity(0, 0, 0);
    i = entities.begin();
    entities.insert(i, noma);
    i = entities.end();
    int k = 1;
    for (int j = 0; j < currentWorld->getNumCitizens(); j++) {
        Citizen *t = new Citizen;
        t->setVelocity(0, 0, 0);

        if (Game::Instance()->getDemoMode() == 0 || Game::Instance()->getDemoMode() == 1 || Game::Instance()->getDemoMode() == 2) {
            t->setFrom(j);
            t->setTo(j + 1);
            if (Game::Instance()->getDemoMode() == 0)
                t->setTo(j + 1);
            t->setPosition(currentWorld->getWayPoints()->getPNode(j)->getPosition().X, currentWorld->getWayPoints()->getPNode(j)->getPosition().Y, currentWorld->getWayPoints()->getPNode(j)->getPosition().Z);

            GUIText * citizenText = new GUIText(Vector3f(10, 10), GUIText::Center, 0, L"Citizen", "Lekton-Regular.ttf", 14, GUIText::ThreeD);
            citizenText->setDrawBBox(true);
            citizenText->setBBoxColor(new RGBA(0.0, 0.0, 0.0, 0.3));
            addGUIElement(citizenText);
        } else {
            t->setFrom(0);
            t->setTo(1);
            if (currentWorld->getWorldName() == "World 0") {
                t->setTo(17);
                t->changeState(new FlockingState());
            }
            t->setPosition(currentWorld->getWayPoints()->getPNode(0)->getPosition().X + 0.01 * j, currentWorld->getWayPoints()->getPNode(0)->getPosition().Y, currentWorld->getWayPoints()->getPNode(0)->getPosition().Z + 0.01 * j);
        }

        if (Game::Instance()->getDemoMode() == 2) {
            GUIText * citizenText = new GUIText(Vector3f(10, 10), GUIText::Center, 0, L"", "Lekton-Regular.ttf", 14, GUIText::ThreeD);
            citizenText->setDrawBBox(true);
            citizenText->setBBoxColor(new RGBA(0.0, 0.0, 0.0, 0.3));
            addGUIElement(citizenText);
        }

        entities.insert(i, t);
        i = entities.end();
        if (j % 10 == 0) k += 1;
    }

    /*for (int j = 0; j < 10; j++) {
        entities.insert(i, new DynamicEntity(Vector3f(10 + j, 10 + j, 0)));
        i = entities.end();
        entities.insert(i, new DynamicEntity(Vector3f(10 - j, 10 + j, 0)));
        i = entities.end();
        entities.insert(i, new DynamicEntity(Vector3f(-10 + j, 10 + j, 0)));
        i = entities.end();
    }*/

    GraphicEngine::Instance()->addEntities(entities);
    int w = GraphicEngine::Instance()->getWidth();
    int h = GraphicEngine::Instance()->getHeight();

    if (Game::Instance()->getDebugMode() && Game::Instance()->getDemoMode() == 3) {
        environmentInfo = new GUIText(Vector3f(0.1 * w, 0.9 * h), GUIText::Left, 0, L"", "Lekton-Regular.ttf", 14, GUIText::TwoD);
        environmentInfo->setDrawBBox(true);
        environmentInfo->setBBoxColor(new RGBA(1, 1, 1, 0.3));
        addGUIElement(environmentInfo);
    }

}

GameState::GameState(const GameState& orig) {
}

GameState::~GameState() {
    deleteState();
    pinstance = NULL;
}

GameState * GameState::pinstance = 0;

GameState * GameState::Instance() {
    if (pinstance == 0) {
        pinstance = new GameState;
    }
    return pinstance;
}

void GameState::eventManager() {

    if (noma != NULL) {

        if (EventManager::Instance()->isKeyDown(KEY_KEY_S)) {
            noma->accelerate(0, 0, -noma->getMaxForce());
            noma->setWalking(true);
            noma->setActivity(noma->getActivity() + 0.01);
            environment->setEnvNumber(environment->getEnvNumber() + noma->getActivity() * 0.01);
        }
        if (EventManager::Instance()->isKeyDown(KEY_KEY_W)) {
            frame++;
            //cout<<"frame:"<<frame<<endl;

            if (frame >= 30) {
                AudioEngine::Instance()->play2DRandomSound("Audio/nomaWalk", 7);
                frame = 0;
            }
            noma->accelerate(noma->getMaxForce() * sin(noma->getRotation()*(3.14159 / 180)), 0, noma->getMaxForce() * cos(noma->getRotation()*(3.14159 / 180)));
            noma->setWalking(true);
            //noma->accelerate(0, 0, noma->getMaxForce());
            noma->setActivity(noma->getActivity() + 0.01);
            environment->setEnvNumber(environment->getEnvNumber() + noma->getActivity() * 0.01);
        }
        if (EventManager::Instance()->isKeyDown(KEY_KEY_D)) {
            noma->accelerate(noma->getMaxForce(), 0, 0);
            noma->setWalking(true);
            noma->setActivity(noma->getActivity() + 0.01);
            environment->setEnvNumber(environment->getEnvNumber() + noma->getActivity() * 0.01);
        }
        if (EventManager::Instance()->isKeyDown(KEY_KEY_A)) {
            noma->accelerate(-noma->getMaxForce(), 0, 0);
            noma->setWalking(true);
            noma->setActivity(noma->getActivity() + 0.01);
            environment->setEnvNumber(environment->getEnvNumber() + noma->getActivity() * 0.01);
        }

        if (EventManager::Instance()->isKeyUp(KEY_KEY_W) && EventManager::Instance()->isKeyUp(KEY_KEY_S) && EventManager::Instance()->isKeyUp(KEY_KEY_A) && EventManager::Instance()->isKeyUp(KEY_KEY_D))
            noma->setWalking(false);

        if (EventManager::Instance()->isKeyDown(KEY_KEY_E)) {
            downKey = true;
        }
        if (EventManager::Instance()->isKeyUp(KEY_KEY_E) && downKey) {
            GraphicEngine::Instance()->emptySubtitle();
            noma->setInteracting(false);
            downKey = false;

            //TALK
            noma->setConversacion(noma->getConversation() + 0.1);
            environment->setEnvNumber(environment->getEnvNumber() - noma->getConversation() * 0.01);

            //INTERACTION
            noma->setTemperament(noma->getTemperament() + 0.1);
            noma->setConfidence(noma->getConfidence() + 0.11);
            environment->setEnvNumber(environment->getEnvNumber() + noma->getTemperament() * 0.01 - noma->getConfidence() * 0.01);
        }
        if (EventManager::Instance()->isKeyDown(KEY_SPACE)) {
            noma->jump();
            noma->setActivity(noma->getActivity() + 0.01);
            environment->setEnvNumber(environment->getEnvNumber() + noma->getActivity() * 0.01);
        }

        if (EventManager::Instance()->isKeyDown(KEY_ESCAPE)) {

            if (Game::Instance()->getDemoMode() == 3)
                Game::Instance()->setState(MainMenuState::Instance());
            else
                Game::Instance()->setState(PopupState::Instance());
        }

        if (EventManager::Instance()->isKeyDown(KEY_RETURN)) {
            enterKey = true;
        }
        if (EventManager::Instance()->isKeyUp(KEY_RETURN) && enterKey) {
            enterKey = false;
            Game::Instance()->setState(MapState::Instance());
        }

        if (EventManager::Instance()->isKeyDown(KEY_KEY_F)) {
            noma->setTemperament(noma->getTemperament() + 0.1);
            environment->setEnvNumber(environment->getEnvNumber() + noma->getTemperament() * 0.01);
        }


    }
}

void GameState::update() {

    if (currentWorld->getScriptLineNarrator() != NULL) {
        Vector3 narratorPosition(currentWorld->getScriptLineNarrator()->getPoint().X, currentWorld->getScriptLineNarrator()->getPoint().Y, currentWorld->getScriptLineNarrator()->getPoint().Z);
        if (abs(noma->getPosition().magnitude() - narratorPosition.length()) < 50 && !currentWorld->getScriptLineNarrator()->isRead()) {
            std::ostringstream file;
            //cout<<"Audio:"<<currentWorld->getScriptLineNarrator()->getAudioFile()<<endl;
            file << "Audio/Voices/" << currentWorld->getScriptLineNarrator()->getAudioFile();
            AudioEngine::Instance()->play2DUniqueSound((char*) file.str().c_str());
            currentWorld->getScriptLineNarrator()->setRead(true);
        }
    }
    
   
    //Update each entity
    for (int i = 0; i < entities.size(); i++) {

        if ((typeid (* entities.at(i)) == typeid (Citizen))) {
            //entities.at(i)->update();
            Citizen *c = (Citizen *) entities.at(i);
            c->update();
            if (Game::Instance()->getDemoMode() == 0 || Game::Instance()->getDemoMode() == 1 || Game::Instance()->getDemoMode() == 2) {
                GUIText * t = (GUIText *) GUIElements[i];
                t->setSpace(GUIText::ThreeD);

                Vector3f textPosition = Vector3f(c->getPosition().X + 3, c->getPosition().Y + 5, c->getPosition().Z);
                t->set3DPoint(textPosition);

                wchar_t * states[6] = {L"Pathwalking", L"FollowNoma", L"TalkToNoma", L"WalkToPlace", L"Stand", L"Flocking"};

                float mood = c->getMoodValue();
                float trust = c->getTrustValue();
                float talk = c->getTalkValue();

                t->setText(L"State %ls Mood: %.2f, Trust: %.2f, Talk: %.2f", states[c->getState()->getIndex()], mood, trust, talk);

            }

        } else if ((typeid (* entities.at(i)) == typeid (Noma))) {
            noma->update();
        } else if ((typeid (* entities.at(i)) == typeid (DynamicEntity))) {
            DynamicEntity *d = (DynamicEntity *) entities.at(i);
            d->update();
        }
    }
    //cout<<"-------"<<endl;

    //Check if Noma is near the monolith
    if (Game::Instance()->getWhichGraphicConnector() != 0 && Game::Instance()->getDemoMode() == 3) {
        Vector3f distance = currentWorld->getMonolithPosition() - noma->getPosition();
        float numericDist = distance.magnitude();
        float inRadius = 250 - numericDist;
        if (inRadius > 0) {
            noma->setCanTravel(true);
        } else {
            noma->setCanTravel(false);
        }
    }

    //Environment AI update
    environment->update();

    //Physics update
    physics->update(FPS);

    //Update graphics
    GraphicEngine::Instance()->update();

    lowerNomaParameters();

    if (Game::Instance()->getDebugMode() && Game::Instance()->getDemoMode() == 3)
        environmentInfo->setText(L"Environment: Number: %.2f R: %.2f G: %.2f B: %.2f", environment->getEnvNumber(), environment->getColor().r, environment->getColor().g, environment->getColor().b);

}

void GameState::render(bool interpolation) {

    GraphicEngine::Instance()->render(interpolation);
}

void GameState::deleteState() {
    for (int i = 0; i < entities.size(); i++) {
        delete(entities[i]);
        entities[i] = NULL;
    }
    entities.clear();
    noma = NULL;
    delete(currentWorld);
    currentWorld = NULL;
    delete(environment);
    environment = NULL;
    GraphicEngine::Instance()->deleteEntities();
    GraphicEngine::Instance()->emptySubtitle();
    GraphicEngine::Instance()->deleteDepuration();
    Game::Instance()->resetNumberOfEntities();

}

void GameState::pause() {

}

void GameState::resume() {

    GraphicEngine::Instance()->resumeScene();
}

void GameState::changeCurrentWorld(std::string world) {

    deleteState();
    currentWorld = new World(world);
    physics->removeWorldMap();
    std::string newMapName = currentWorld->getMapName() + ".obj";
    physics->addCollisionMeshToWorld((char *) newMapName.c_str());
    initEntities();
    Vector3f p = currentWorld->getMonolithPosition();
    p.Z -= 50;
    noma->setInitPosition(p);
    environment = new Environment;
    cout << "Finished changing to " << currentWorld->getMapName() << endl;
}

void GameState::lowerNomaParameters() {

    noma->setActivity(noma->getActivity() - noma->getActivity()*0.0005);
    noma->setConfidence(noma->getConfidence() - noma->getConfidence()*0.0005);
    noma->setConversacion(noma->getConversation() - noma->getConversation()*0.0005);
    noma->setTemperament(noma->getTemperament() - noma->getTemperament()*0.0005);

    if (environment->getEnvNumber() > 50) {
        environment->setEnvNumber(environment->getEnvNumber() - 0.05);
    } else {
        environment->setEnvNumber(environment->getEnvNumber() + 0.02);
    }
}

