/* 
 * File:   Parser.cpp
 * Author: MAC
 * 
 * Created on 6 de noviembre de 2013, 10:29
 */

#include "../headers/Parser.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <unistd.h>
#include <string.h>
#include <string>
#include <list>
#include "../headers/BaseGameEntity.h"
#include "../SimpleJSON/JSON.h"
#include "../headers/ScriptLine.h"
#include "../headers/BaseGameEntity.h"
#include "../headers/Game.h"

#define DESC_LENGTH 50
using namespace std;


Parser::Parser() {
}

Parser::Parser(const Parser& orig) {
}

Parser::~Parser() {
}

void Parser::ParseWorldMeshesData(std::string fileName, World* me){
    
    std::string buffer, fragment; 
    char *path=new char[fileName.size()+1];
    path[fileName.size()]=0;
    memcpy(path,fileName.c_str(),fileName.size());
    
    WorldMeshData data;
    
    ifstream fe;
    fe.open(path);

    if(!fe) { cout<<"Error opening "<<path<<endl; }
    else{
        while(getline(fe, buffer)) {
            if(buffer.find("node id=") != std::string::npos) {
                std::string fragment = buffer.substr(16,buffer.length()-16);
                int found = fragment.find("_", 0);
                if(found > -1)
                    fragment = fragment.substr(0,found);
                else{
                    found = fragment.find('\"',0);
                    fragment = fragment.substr(0,found);
                }
                
                //PARSED MESH NAME
                data.meshName = fragment+".obj";
                data.textureName = fragment+".png";
            }
            if(buffer.find("matrix") != std::string::npos) {
                std::string fragment = buffer.substr(buffer.find(">",0)+1,buffer.length()-buffer.find(">",0)+1);
                fragment = fragment.substr(0,fragment.length()-9);
                
                int spacePos, prevSpacePos;
                std::string num;
                for(int i = 0; i < 16; i++){
                    float n; 
                    if(i == 0){
                        spacePos = fragment.find(" ");
                        num = fragment.substr(0,spacePos);
                        n = atof(num.c_str());
                    } 
                    else{
                        prevSpacePos = spacePos;
                        spacePos = fragment.find(" ",prevSpacePos+1);
                        num = fragment.substr(prevSpacePos+1,spacePos-(prevSpacePos+1));
                        n = atof(num.c_str());
                    }
                    
                    //PARSED MATRIX POSITION
                    data.transformation[i] = n;
                    
                }
                
                //ALL PARSED
                //data.transformation.identity();
                me->addWorldMeshData(data);
                /*cout<<"ADDED DATA: "<<endl;
                cout<<data.meshName<<endl;
                for(int i = 0; i < 16; i++)
                    cout<<data.transformation[i]<<", ";
                cout<<endl;*/
            }
        }
    }
}


PGraph * Parser::ParseStage(std::string fileName) {
   
    long size;
    char *buf;
    char *ptr;

    std::string buffer, fragment; 
    fileName = ""+fileName+".xml";
    
    char *path=new char[fileName.size()+1];
    path[fileName.size()]=0;
    memcpy(path,fileName.c_str(),fileName.size());
    
    ifstream fe;
    fe.open(path);
    
    //cout<<path<<endl;
    if(!fe) { cout<<"error al abrir"<<endl; }
    PGraph* level = new PGraph(); //El grafo a devolver
    PGraph* graphAux = new PGraph(); //El grafo del momento
    //cout<<"Parsing waypoints: "<<path<<endl;      
    
    while(getline(fe, buffer)) {
        
        float x = 0, y = 0, z = 0;
        int from = 0, to = 0;
        
        if(buffer.find("GEO_POINT ") != std::string::npos) {
            fragment = buffer.substr(buffer.find("x="), buffer.length());             
            fragment = fragment.substr(fragment.find("=")+2, fragment.length());
            x = atoi(fragment.substr(0, fragment.find('"')).c_str());
            
            fragment = buffer.substr(buffer.find("y="), buffer.length());             
            fragment = fragment.substr(fragment.find("=")+2, fragment.length());
            z = atoi(fragment.substr(0, fragment.find('"')).c_str()); 
            
            fragment = buffer.substr(buffer.find("z="), buffer.length());             
            fragment = fragment.substr(fragment.find("=")+2, fragment.length());
            y = atoi(fragment.substr(0, fragment.find('"')).c_str());

            if(Game::Instance()->getWhichGraphicConnector() == 0){
                graphAux->addPNode(new PNode(0,Vector3f(-x,y,-z)));
            }
            else{
                graphAux->addPNode(new PNode(0,Vector3f(x,y,-z)));
            }
        }
        
        if(buffer.find("GEO_EDGE ") != std::string::npos) {
            fragment = buffer.substr(buffer.find("e1="), buffer.length());             
            fragment = fragment.substr(fragment.find("=")+2, fragment.length());
            from = atoi(fragment.substr(0, fragment.find('"')).c_str());
            
            fragment = buffer.substr(buffer.find("e2="), buffer.length());             
            fragment = fragment.substr(fragment.find("=")+2, fragment.length());
            to = atoi(fragment.substr(0, fragment.find('"')).c_str());   
            
            graphAux->addPEdge(new PEdge(from-1,to-1));
        }
        
        if(buffer.find("/noi:BASIS_LINE3D") != std::string::npos) {
            //Comprobar repeticiones de graphAux en level y añadir si no están
            
            vector<PNode *> nodes = graphAux->getNodes();
            for(int i = 0; i < nodes.size(); i++) {
                if (!isInVector(level->getNodes(), nodes[i])) {
                    level->addPNode(nodes[i]);
                }
            }
            
            vector<std::list<PEdge *> > edges = graphAux->getEdges();
            for(int i = 0; i < edges.size(); i++){
                for(std::list<PEdge*>::iterator it = edges[i].begin(); it != edges[i].end(); ++it){
                    PEdge *e = *it;
                    
                    Vector3f fromPos = graphAux->getPNode(e->getFromNode())->getPosition();
                    int from = level->getPNodeIndex(fromPos);
                    Vector3f toPos = graphAux->getPNode(e->getToNode())->getPosition();
                    int to = level->getPNodeIndex(toPos);
                    //cout<<e->getFromNode()<<", "<<from<<endl;
                    PEdge *toAdd = new PEdge(from, to);
                    if(!isInList(level->getEdges(), toAdd)){
                        level->addPEdge(toAdd);
                    }
                }
                
            }
            graphAux = new PGraph();
            
        }
                
    }
    
    /*cout<<"Parsed waypoints"<<endl;
    for(int i= 0; i<level->getNumberOfPNodes(); i++){
        PNode * n = level->getPNode(i);
        n->getPosition().print();
        cout<<endl;
    }
    cout<<"Edges number: "<< level->getEdges().size()<<endl;*/
    return level;
}


bool Parser::isInVector(vector<PNode*> nodes, PNode* e) {
    bool is = false;
    for(int i = 0; i < nodes.size(); i++) {
        if (nodes[i]->getPosition().X == e->getPosition().X && nodes[i]->getPosition().Y == e->getPosition().Y && nodes[i]->getPosition().Z == e->getPosition().Z) {
            is = true;
        }
    }
    return is;
}

bool Parser::isInList(vector< std::list<PEdge*> > List, PEdge* edge) {
    bool isFrom = false, isTo = false;
    
    for(std::list<PEdge *>::iterator it = List[edge->getFromNode()].begin(); it != List[edge->getFromNode()].end() && isFrom == false; ++it) {
        PEdge *e = *it;
        if (edge->getFromNode() == e->getFromNode() && edge->getToNode() == e->getToNode()) {
            isFrom = true;
        }
    }
    for(std::list<PEdge *>::iterator it = List[edge->getToNode()].begin(); it != List[edge->getToNode()].end() && isTo == false; ++it) {
        PEdge *e = *it;
        if (edge->getFromNode() == e->getFromNode() && edge->getToNode() == e->getToNode()) {
            isTo = true;
        }
    }
    return isFrom && isTo;
}

void Parser::ParseWorld(std::string worldName, World * me){
    
    wstring name = L"", data = L"";
    
    //Get file and parse it
    get_file(worldName, name, data);
    JSONValue *v = JSON::Parse(data.c_str());
    
    //Get contents
    JSONObject root = v->AsObject();
    
    //World name
    wstring cName = root[L"name"]->AsString();
    std::string sName(cName.begin(), cName.end());
    me->setWorldName(sName);
    
    //Map name
    wstring cMapName = root[L"mapName"]->AsString();
    std::string sMapName(cMapName.begin(), cMapName.end());
    me->setMapName(sMapName);
    
    //Map name
    wstring cFolder = root[L"folder"]->AsString();
    std::string sFolder(cFolder.begin(), cFolder.end());
    me->setFolder(sFolder);
    
    //Num of Citizens
    int numCitizen = root[L"numCitizen"]->AsNumber();
    me->setNumCitizens(numCitizen);
    
    //Personality values
    JSONArray moodValues = root[L"moodValues"]->AsArray();
    int minMood = moodValues[0]->AsNumber();
    int maxMood = moodValues[1]->AsNumber();
    int initialMood = moodValues[2]->AsNumber();
    me->setMoodValues(minMood, maxMood, initialMood);
    
    JSONArray trustValues = root[L"trustValues"]->AsArray();
    int minTrust = trustValues[0]->AsNumber();
    int maxTrust = trustValues[1]->AsNumber();
    int initialTrust = trustValues[2]->AsNumber();
    me->setTrustValues(minTrust, maxTrust, initialTrust);
    
    JSONArray talkValues = root[L"talkValues"]->AsArray();
    int minTalk = talkValues[0]->AsNumber();
    int maxTalk = talkValues[1]->AsNumber();
    int initialTalk = talkValues[2]->AsNumber();
    me->setTalkValues(minTalk, maxTalk, initialTalk);
    
    //Reachable Planets
    JSONArray reachableWorlds = root[L"reachableWorlds"]->AsArray();
    for(int i = 0; i < reachableWorlds.size(); i++){
        int world = reachableWorlds[i]->AsNumber();
        me->addReachableWorld(world);
    }
    
    //Citizen Data
    JSONArray citizenData = root[L"citizenData"]->AsArray();
    for(int i = 0; i < citizenData.size(); i++){
        JSONObject d = citizenData[i]->AsObject();
        wstring m = d[L"meshName"]->AsString();
        std::string meshName(m.begin(), m.end());
        wstring t = d[L"textureName"]->AsString();
        std::string textureName(t.begin(), t.end());
        float relativeNum = d[L"relativeNum"]->AsNumber();
        CitizenData data;
        data.meshName = meshName;
        data.textureName = textureName;
        data.relativeNum = relativeNum;
        me->addCitizenData(data);
    }
    
    //Script Lines
    JSONArray scriptLines = root[L"script"]->AsArray();
    for(int i = 0; i < scriptLines.size(); i++){
        JSONObject line = scriptLines[i]->AsObject();
        ScriptLine::Type type = (ScriptLine::Type) line[L"type"]->AsNumber();
        int x = line[L"x"]->AsNumber();
        int y = line[L"y"]->AsNumber();
        int z = line[L"z"]->AsNumber();
        Vector3f point(x,y,z);
        wstring cContent = line[L"content"]->AsString();
        wstring cAudio = line[L"audioFile"]->AsString();
        std::string audio(cAudio.begin(), cAudio.end());
        ScriptLine * s = new ScriptLine(type, point, cContent, audio);
        if(type == ScriptLine::Citizen) me->addScriptLineCitizen(s);
        else if(type == ScriptLine::Narrator) me->addScriptLineNarrator(s);
        else if(type == ScriptLine::Irrelevant) me->addScriptLineIrrelevant(s);
        else if(type == ScriptLine::Place) me->addScriptLinePlace(s);
        
        std::string content(cContent.begin(), cContent.end());
    }
    
    //Parse world meshes data
    ParseWorldMeshesData(me->getMapName()+".dae", me);
   
}

bool Parser::get_file(std::string filename, wstring &description, wstring &data)
{
	wifstream in(filename.c_str());
	if (in.is_open() == false)
		return false;

	getline(in, description);
	if (description.length() > DESC_LENGTH)
		description.resize(DESC_LENGTH);
	
	wstring line;
	data = L"";
	while (getline(in, line))
	{
		data += line;
		if (!in.eof()) data += L"\n";
	}
	return true;
}
