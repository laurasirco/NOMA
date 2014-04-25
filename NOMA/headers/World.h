/* 
 * File:   World.h
 * Author: MAC
 *
 * Created on 15 de octubre de 2013, 17:27
 */

#ifndef WORLD_H
#define	WORLD_H
#include "PGraph.h"
#include "ScriptLine.h"
#include "Matrices.h"
#include "BaseGameEntity.h"
#include <vector>
#include <iostream>

struct CitizenData{
    std::string meshName;
    std::string textureName;
    float relativeNum;
};

struct WorldMeshData{
    std::string meshName;
    std::string textureName;
    Matrix4 transformation;
};

class World {
public:
    World(std::string fileName);
    World(const World& orig);
    virtual ~World();
    
    void loadGraphicEntities();
    
    PGraph * getWayPoints(){ return wayPoints; }
    void setWayPoints(PGraph * w){ wayPoints = w; }
    
    void setWorldName(std::string n){ worldName = n; }
    void setMapName(std::string n){ mapName = n; }
    void setFolder(std::string f){ folder = f; }
    void setNumCitizens(int num){ numCitizens = num; }
    void addCitizenData(CitizenData data){ citizenData.push_back(data); }
    void addWorldMeshData(WorldMeshData data){ worldMeshesData.push_back(data); }
    void addScriptLineNarrator(ScriptLine * s){ scriptNarrator.push_back(s); }
    void addScriptLineCitizen(ScriptLine * s){ scriptCitizen.push_back(s); }
    void addScriptLineIrrelevant(ScriptLine * s){ scriptIrrelevant.push_back(s); }
    void addScriptLinePlace(ScriptLine * s){ scriptPlace.push_back(s); }
    void addReachableWorld(int i){ reachableWorlds.push_back(i); }
    
    bool hasCitizenLines(){
        
        if(scriptCitizen.size() > 0) return true;
        if(scriptPlace.size() > 0) return true;
        if(scriptIrrelevant.size() > 0) return true;
        
        return false;
        
    }
    
    void addMonolith(Vector3f position);
    Vector3f getMonolithPosition(){ return monolith->getPosition(); }
    
    int getNumCitizens(){ return numCitizens; }
    ScriptLine *getScriptLineCitizen();
    ScriptLine *getScriptLineNarrator();
    std::string getWorldName(){ return worldName; }
    std::string getMapName(){ return mapName; }
    std::string getFolder(){ return folder; }
    std::vector<CitizenData> getCitizenData(){ return citizenData; }
    std::vector<WorldMeshData> getWorldMeshesData(){ return worldMeshesData; }
    std::vector<int> getReachableWorlds(){ return reachableWorlds; }
    
    void setMoodValues(int min, int max, int initial){ moodValues.push_back(min); moodValues.push_back(max); moodValues.push_back(initial); }
    void setTrustValues(int min, int max, int initial){ trustValues.push_back(min); trustValues.push_back(max); trustValues.push_back(initial); }
    void setTalkValues(int min, int max, int initial){ talkValues.push_back(min); talkValues.push_back(max); talkValues.push_back(initial); }
    
    std::vector<int> getMoodValues(){ return moodValues; }
    std::vector<int> getTrustValues(){ return trustValues; }
    std::vector<int> getTalkValues(){ return talkValues; }
    
    
private:
    PGraph * wayPoints;
    std::string worldName;
    std::string mapName;
    std::string folder;
    int numCitizens;
    std::vector<CitizenData> citizenData;
    std::vector<WorldMeshData> worldMeshesData;
    std::vector<ScriptLine *> scriptNarrator;
    std::vector<ScriptLine *> scriptCitizen;
    std::vector<ScriptLine *> scriptIrrelevant;
    std::vector<ScriptLine *> scriptPlace;
    std::vector<int> reachableWorlds;
    
    BaseGameEntity * monolith;
    
    std::vector<int> moodValues;
    std::vector<int> trustValues;
    std::vector<int> talkValues;
};

#endif	/* WORLD_H */

