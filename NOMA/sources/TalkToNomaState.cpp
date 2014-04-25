/* 
 * File:   TalkToNomaState.cpp
 * Author: laurasirventcollado
 * 
 * Created on 10 de enero de 2014, 10:24
 */

#include "../headers/TalkToNomaState.h"
#include "../headers/GameState.h"
#include "../headers/ScriptLine.h"
#include "../headers/GraphicEngine.h"
#include "../headers/WalkToPlaceState.h"
#include <iostream>
using namespace std;

TalkToNomaState::TalkToNomaState() {
    index = TalkToNoma;
}

TalkToNomaState::TalkToNomaState(const TalkToNomaState& orig) {
}

TalkToNomaState::~TalkToNomaState() {
}

void TalkToNomaState::update(Citizen* me) {

    
    if (GraphicEngine::Instance()->isSubtitleSpaceEmpty()) {
        ScriptLine * s = me->getScriptLine();
        
        if (s->getType() == ScriptLine::Place && !s->hasArrived()) {
            GraphicEngine::Instance()->printSubtitle(L"Sigueme");
            me->resetPath();
            me->changeState(new WalkToPlaceState());
        }
        
        else if((s->getType() == ScriptLine::Place && s->hasArrived()) || (s->getType() == ScriptLine::Citizen) || (s->getType() == ScriptLine::Irrelevant)){
            GraphicEngine::Instance()->printSubtitle(s->getContent());
            s->setRead(true);
        }
    }

    Vector3f nomaDirection = GameState::Instance()->getNoma()->getPosition() - me->getPosition();
    //ANGULAR
    me->setRotation(atan2(nomaDirection.X, nomaDirection.Z));
    me->setOrientation(me->getRotation());

    me->setVelocity(Vector3f(0, 0, 0));

}

