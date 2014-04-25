/* 
 * File:   Citizen.h
 * Author: MAC
 *
 * Created on 15 de octubre de 2013, 17:26
 */

#ifndef CITIZEN_H
#define	CITIZEN_H
#include "Character.h"
#include "Path.h"
#include "CitizenState.h"
#include "Noma.h"
#include "ScriptLine.h"

class Citizen : public Character{
public:
    Citizen();
    Citizen(const Citizen& orig);
    virtual ~Citizen();
    void update();
    void setFrom(int f){ from = f; }
    void setTo(int t){ to = t; }
    void avoidPenetrationWithNeighbors(std::vector<BaseGameEntity *> neighborhood, float radius, float divide, float overlapNoma);
    int getTo(){ return to; }
    int getFrom(){ return from; }
    Path * getPath(){ return path; }
    void resetPath(){ path = new Path(); from = to = 0; }
    
    void checkFSM();
    void updatePersonality(float updateMood, float updateTrust, float updateTalk);
    void changeState(CitizenState * newState);
    bool isNomaInRadius(float rad, Noma * noma);
    void propagateChangesToNeighbors(float updateMood, float updateTrust, float updateTalk);
    bool isAnyNeighborInteracting();
    
    void addMoodValue(float m){ moodValue += m; if(moodValue > MAX_MOOD) moodValue = MAX_MOOD; if(moodValue < MIN_MOOD) moodValue = MIN_MOOD; }
    void addTrustValue(float t){ trustValue += t; if(trustValue > MAX_TRUST) trustValue = MAX_TRUST; if(trustValue < MIN_TRUST) trustValue = MIN_TRUST;}
    void addTalkValue(float t){ talkValue += t; if(talkValue > MAX_TALK) talkValue = MAX_TALK; if(talkValue < MIN_TALK) talkValue = MIN_TALK;}
    
    float getMoodValue(){ return moodValue; }
    float getTrustValue(){ return trustValue; }
    float getTalkValue(){ return talkValue; }
    float getPropagationRadius() { return propagationRadius; }
    bool getInteracting(){ return interacting; }
    
    CitizenState * getState(){ return state; }
    
    ScriptLine * getScriptLine(){ return line; }
    void setScriptLine(ScriptLine *l){ line = l; }
    
    void setPropagated(bool p){ propagated = p; }
    
    TNode * getGraphicNode(){ return graphicNode; }
    
    //********* ENTREGABLE 8 **********//
    
    void setMoodNode(TNode * n){ moodNode = n; }
    void setTrustNode(TNode * n){ trustNode = n; }
    void setPropagationNode(TNode * n){ propagationNode = n; }
    
    //********************************//
    
private:
    
    int MAX_MOOD;
    int MAX_TRUST;
    int MAX_TALK;
    int MIN_MOOD;
    int MIN_TRUST;
    int MIN_TALK;
    
    Path *path;
    
    int from, to;
    float moodValue;
    float trustValue;
    float talkValue;
    float propagationRadius;
    bool talk;
    bool interacting;
    bool propagated;
    bool decrement;
    bool propagating;
    
    float totalDecrementValue;
    float decrementCounter;
    
    CitizenState * state;
    
    ScriptLine * line;
    
    
    //********* ENTREGABLE 8 **********//
        
    TNode * moodNode;
    TNode * trustNode;
    TNode * propagationNode;
            
    //********************************//

};

#endif	/* CITIZEN_H */

