/* 
 * File:   World.cpp
 * Author: MAC
 * 
 * Created on 15 de octubre de 2013, 17:27
 */

#include "../headers/World.h"
#include "../headers/Parser.h"
#include "../headers/GraphicEngine.h"
#include <stdlib.h>
#include <time.h>

World::World(std::string fileName) {

    Parser *p = new Parser();

    p->ParseWorld(fileName, this);

    wayPoints = p->ParseStage(mapName);

    //GraphicEngine::Instance()->addWaypoints(wayPoints);

    monolith = NULL;
}

World::World(const World& orig) {
}

World::~World() {
    if (monolith)
        delete(monolith);
    monolith = NULL;
    delete(wayPoints);
    wayPoints = NULL;
    citizenData.clear();
    worldMeshesData.clear();
    scriptNarrator.clear();
    scriptCitizen.clear();
    scriptIrrelevant.clear();
    scriptPlace.clear();
}

void World::loadGraphicEntities() {
    GraphicEngine::Instance()->loadWorldMap(this);
}

void World::addMonolith(Vector3f position) {

    monolith = new BaseGameEntity();
    monolith->setPosition(position.X, position.Y, position.Z);

}

ScriptLine* World::getScriptLineCitizen() {
    bool found = false;
    int i = 0;

    while (!found && i < scriptCitizen.size()) {
        if (!scriptCitizen[i]->isRead()) {
            found = true;
            return scriptCitizen[i];
        }
        i++;
    }
    i = 0;
    while (!found && i < scriptPlace.size()) {
        if (!scriptPlace[i]->isRead()) {
            found = true;
            return scriptPlace[i];
        }
        i++;
    }
    if (scriptIrrelevant.size() > 0) {
        srand(time(NULL));
        int v1 = rand() % scriptIrrelevant.size();
        return scriptIrrelevant[v1];
    } else
        return NULL;
}

ScriptLine* World::getScriptLineNarrator() {
    bool found = false;
    int i = 0;
    
    while (!found && i < scriptNarrator.size()) {
        if (!scriptNarrator[i]->isRead()) {
            found = true;
            return scriptNarrator[i];
        }
        i++;
    }
    return NULL;
    
}
