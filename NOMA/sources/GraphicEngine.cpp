/* 
 * File:   GraphicEngine.cpp
 * Author: MAC
 * 
 * Created on 15 de octubre de 2013, 17:37
 */

#include "../headers/GraphicEngine.h"
#include "../headers/Citizen.h"
#include "../headers/CitizenState.h"
#include "../headers/Noma.h"
#include "../headers/Game.h"
#include "../headers/PGraph.h"
#include "../headers/GameState.h"
#include "../headers/SteeringBehaviors.h"
#include "../headers/Path.h"
#include "../headers/PNode.h"
#include "../headers/GraphicConnector.h"
#include "../headers/GameState.h"
#include "../headers/PhysicsEngine.h"
#include "../headers/World.h"
#include "../headers/Environment.h"
#include <ctime>
#include <typeinfo>
#include <iostream>
#include <utility>
#include <math.h>
#include <stdlib.h>
#include <sstream>
#include <unistd.h>

using namespace std;

GraphicEngine::GraphicEngine() {
    em = EventManager::Instance();
    empty = true;
}

GraphicEngine::GraphicEngine(const GraphicEngine& orig) {
}

GraphicEngine::~GraphicEngine() {

}

GraphicEngine* GraphicEngine::pinstance = 0;

GraphicEngine* GraphicEngine::Instance() {

    if (pinstance == 0) {
        pinstance = new GraphicEngine;
    }
    return pinstance;
}

void GraphicEngine::init(int which, int screenWidth, int screenHeight, bool fullScreen) {

    this->which = which;
    this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;

    if (which == 0)
        connector = new GraphicConnector();
    else
        TConnector = new TAGConnector();

    depuration = false;
    firstTimeDepuration = false;
    this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;

    if (which == 0)
        connector->init(screenWidth, screenHeight, fullScreen);
    else
        TConnector->init(screenHeight, screenWidth);

}

void GraphicEngine::loadWorldMap(World *world) {

    if (which == 0) {
        cout << world->getMapName() + ".obj" << endl;
        connector->loadMesh(world->getMapName() + ".obj");
    }
    else {
        std::vector<WorldMeshData> data = world->getWorldMeshesData();
        std::string folder = world->getFolder();
        for (int i = 0; i < data.size(); i++) {
            TConnector->addWorldEntity(data[i].transformation, folder + data[i].meshName, folder + data[i].textureName);
        }
    }
}

bool GraphicEngine::isDeviceRunning() {

    if (which == 0)
        return connector->isDeviceRunning();
    else
        return true;

}

void GraphicEngine::addEntities(vector<BaseGameEntity *> entities) {

    if (which == 0) {
        std::vector<CitizenData> data = GameState::Instance()->getCurrentWorld()->getCitizenData();
        int citizenCont = 0;
        int dataCont = 0;
        int relativeNum = data[dataCont].relativeNum;
        std::string meshName = data[dataCont].meshName;
        std::string textureName = data[dataCont].textureName;

        for (int j = 0; j < entities.size(); j++) {

            if (typeid (* entities.at(j)) == typeid (Citizen)) {

                if (citizenCont < relativeNum) {
                    connector->addGameEntity(entities.at(j), meshName);
                    connector->setTexture(j, textureName);
                    citizenCont++;
                } else {
                    citizenCont = 0;
                    dataCont++;
                    relativeNum = data[dataCont].relativeNum;
                    meshName = data[dataCont].meshName;
                    textureName = data[dataCont].textureName;
                    connector->addGameEntity(entities.at(j), meshName);
                    connector->setTexture(j, textureName);
                    citizenCont++;
                }

            } else if (typeid (* entities.at(j)) == typeid (Noma)) {

                connector->addGameEntity(entities.at(j), "noma.md2");
                connector->setTexture(j, "noma.png");

            } else if (typeid (* entities.at(j)) == typeid (DynamicEntity)) {

                connector->addCubeGameEntity(entities.at(j));
            }

        }
    } else {
        std::vector<CitizenData> data = GameState::Instance()->getCurrentWorld()->getCitizenData();
        int citizenCont = 0;
        int dataCont = 0;
        int relativeNum = data[dataCont].relativeNum;
        std::string meshName = data[dataCont].meshName;
        std::string textureName = data[dataCont].textureName;

        for (int j = 0; j < entities.size(); j++) {

            if (typeid (* entities.at(j)) == typeid (Citizen)) {

                if (citizenCont < relativeNum) {
                    TConnector->addEntity(entities.at(j), "Animations/Citizen1", textureName);
                    citizenCont++;
                } else {
                    citizenCont = 0;
                    dataCont++;
                    relativeNum = data[dataCont].relativeNum;
                    meshName = data[dataCont].meshName;
                    textureName = data[dataCont].textureName;
                    TConnector->addEntity(entities.at(j), meshName, textureName);
                    citizenCont++;
                }

            } else if (typeid (* entities.at(j)) == typeid (Noma)) {

                TConnector->addEntity(entities.at(j), "Animations/Noma", "noma.png");

            } else if (typeid (* entities.at(j)) == typeid (DynamicEntity)) {

                TConnector->addEntity(entities.at(j), "World1/cube.obj", "");
            }

        }
    }

}

void GraphicEngine::addGUIEntities(std::vector<MenuItem> elements) {
    if (which == 0) {
        connector->addGUIEntities(elements);
    }
}

void GraphicEngine::deleteGUIEntities() {

    if (which == 0) {
        connector->deleteGUIEntities();
    }
}

void GraphicEngine::toggleDepurationMode() {

    depuration = !depuration;
    addDebugInterface();
}

void GraphicEngine::update() {

    int cont = 0;

    if (which == 0) {
        switch (Game::Instance()->getCurrentState()->getType()) {
            case State::MainMenu:
                break;
            case State::Game:
                if (depuration) {
                    connector->clearPathfindingRoutes();
                }
                for (int i = 0; i < Game::Instance()->getNumberOfEntities(); i++) {
                    BaseGameEntity * e = GameState::Instance()->getGameEntityByIndex(i);
                    connector->setPosition(i, e->getPosition());
                    if (typeid (* e) == typeid (DynamicEntity)) {
                        DynamicEntity *d = (DynamicEntity *) e;
                        connector->setRotation(i, d->getOrientation());
                    } else {
                        float deg = (e->getOrientation()*(180)) / 3.1415;
                        connector->setRotation(i, deg);
                    }
                    if (depuration && Game::Instance()->getDemoMode() == 1) {
                        connector->set3DTextPosition(i, Vector3f(e->getPosition().X, e->getPosition().Y + 2, e->getPosition().Z));
                        connector->setRadiusPosition(i, Vector3f(e->getPosition().X, e->getPosition().Y, e->getPosition().Z));
                        if (typeid (* e) == typeid (Citizen)) {
                            Citizen * c = (Citizen *) e;
                            connector->setRadius(i, c->getMoodValue(), c->getTrustValue());

                            std::list<PNode *> list = c->getPath()->getWaypoints();
                            std::ostringstream s;
                            s << "CITIZEN " << i << endl;
                            CitizenState::Index index = c->getState()->getIndex();
                            s << "CURRENT STATE:";
                            switch (index) {
                                case CitizenState::Flocking:
                                    s << "FLOCKING" << endl;
                                    break;
                                case CitizenState::FollowNoma:
                                    s << "FOLLOW NOMA" << endl;
                                    break;
                                case CitizenState::Pathwalking:
                                    s << "PATHWALKING" << endl;
                                    break;
                                case CitizenState::Stand:
                                    s << "STAND" << endl;
                                    break;
                                case CitizenState::TalkToNoma:
                                    s << "TALK TO NOMA" << endl;
                                    break;
                                case CitizenState::WalkToPlace:
                                    s << "WALK TO PLACE" << endl;
                                    break;

                            }
                            s << "MOOD VALUE = " << c->getMoodValue() << endl;
                            s << "TRUST VALUE = " << c->getTrustValue() << endl;
                            s << "TALK VALUE = " << c->getTalkValue() << endl;
                            s << "ROUTE = ";
                            for (std::list<PNode *>::iterator i = list.begin(); // not listMyClass.begin()
                                    i != list.end(); // not listMyClass.end()
                                    i++) {
                                s << (*i)->getIndex() << "-";
                            }
                            s << endl;
                            std::string route(s.str());
                            connector->updatePathfindingRoutes(route);
                            connector->set3DTextContent(i, route);
                            cont++;
                        }

                    }
                }

                connector->setFollowCamera(0);

                break;
            case State::Badget:
                break;
            case State::Map:
                break;
            case State::Option:
                break;

        }

        if (em->isKeyDown(KEY_ESCAPE)) {
            connector->close();
        }
    }

}

void GraphicEngine::render(bool interpolation) {

    if (which == 0) {
        Environment::RGB color;
        if (Game::Instance()->getCurrentState()->getType() == State::Game)
            color = GameState::Instance()->getEnvironment()->getColor();
        else
            color = Environment::RGB();

        connector->beginScene(color.r, color.g, color.b);

        connector->draw3DElements();
        connector->drawGUIElements();

        if (depuration) {

            connector->drawWayroutes(GameState::Instance()->getCurrentWorld()->getWayPoints());
            //connector->printPathfindingRoutes();
            GameState::Instance()->getPhysicsEngine()->debugRender();

            std::ostringstream s1;
            s1 << "NOMA" << endl;
            s1 << "POSITION: " << GameState::Instance()->getNoma()->getPosition().X << ", " << GameState::Instance()->getNoma()->getPosition().Y << ", " << GameState::Instance()->getNoma()->getPosition().Z << endl;
            s1 << "-----------------" << endl;
            s1 << "PERSONALITY" << endl;
            s1 << "ACTIVITY: " << GameState::Instance()->getNoma()->getActivity() << endl;
            s1 << "CONFIDENCE: " << GameState::Instance()->getNoma()->getConfidence() << endl;
            s1 << "CONVERSATION: " << GameState::Instance()->getNoma()->getConversation() << endl;
            s1 << "TEMPERAMENT: " << GameState::Instance()->getNoma()->getTemperament() << endl;
            s1 << "-----------------" << endl;
            s1 << "ENVIRONMENT VALUE: " << GameState::Instance()->getEnvironment()->getEnvNumber() << endl;
            s1 << "COLOR: " << GameState::Instance()->getEnvironment()->getSColor() << endl;
            s1 << "MUSIC: " << GameState::Instance()->getEnvironment()->getMusic() << endl;
            s1 << "WEATHER: " << GameState::Instance()->getEnvironment()->getWeather() << endl;

            connector->draw2DText(s1.str(), Vector3f(10, 100, 0), Vector3f(200, 300, 0), GraphicConnector::Small);
        }

        //cout<<subtitle<<endl;
        //ADD TEXTS
        if (subtitle != L"") {
            std::string s = std::string(subtitle.begin(), subtitle.end());
            connector->draw2DText(s, Vector3f(100, screenHeight - 200, 0), Vector3f(screenWidth - 100, screenHeight - 100, 0), GraphicConnector::Large);
        }

        //--------
        connector->endScene();
    } else {
        if (Game::Instance()->getCurrentState()->getType() == State::Game) {
            Environment::RGB color = GameState::Instance()->getEnvironment()->getColor();
            TConnector->updateAmbientLightIntensity(color.r, color.g, color.b, 0.5);
        }
        TConnector->loopEvent();
    }
}

void GraphicEngine::addDebugInterface() {

    if (which == 0) {
        if (Game::Instance()->getCurrentState()->getType() == State::Game) {
            if (!depuration && !firstTimeDepuration && Game::Instance()->getDemoMode() != 4) {
                connector->addButton("Depuration Mode", Vector3f(10, 10, 0), Vector3f(300, 50, 0), 5);
                connector->addButton("E", Vector3f(10, 60, 0), Vector3f(30, 80, 0), 6);
            } else if (depuration && !firstTimeDepuration && Game::Instance()->getDemoMode() == 1) {

                for (int i = 0; i < Game::Instance()->getNumberOfEntities(); i++) {

                    MovingEntity * m = (MovingEntity *) GameState::Instance()->getGameEntityByIndex(i);

                    if (typeid (* m) == typeid (Noma)) {
                        connector->add3DTextToEntity("NOMA");
                        connector->addRadiusToEntity(i, 10);

                    } else {
                        Citizen * c = (Citizen *) m;
                        float propValue = c->getPropagationRadius();
                        float moodValue = c->getMoodValue();
                        float trustValue = c->getTrustValue();
                        connector->add3DTextToEntity("CITIZEN");
                        connector->addRadiusToEntity(i, 4, propValue, moodValue, trustValue);

                    }

                }
                PGraph *waypoints = GameState::Instance()->getCurrentWorld()->getWayPoints();
                connector->addWaypoints(waypoints, SteeringBehaviors::Instance()->getRadius());

                firstTimeDepuration = true;
            } else if (!depuration && firstTimeDepuration) {
                connector->setDebugInterfaceVisible(false);
            } else if (depuration && firstTimeDepuration) {
                connector->setDebugInterfaceVisible(true);
            }
        }
    }
}

void GraphicEngine::resumeScene() {

    if (which == 0)
        connector->resumeScene();

}

void GraphicEngine::printSubtitle(std::wstring s) {

    subtitle = s;
    empty = false;

    sub = new GUIText(Vector3f(screenWidth / 2, screenHeight - 200), GUIText::Center, 0, (wchar_t *)subtitle.c_str(), "Lekton-Regular.ttf", 16);
    sub->setDrawBBox(true);
    sub->setBBoxColor(new RGBA(0.0, 0.0, 0.0, 0.3));
    GameState::Instance()->addGUIElement(sub);
}

void GraphicEngine::emptySubtitle() {
    subtitle = L"";
    empty = true;
    GameState::Instance()->removeGUIElement(sub);
}