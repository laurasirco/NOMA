/* 
 * File:   Citizen.cpp
 * Author: MAC
 * 
 * Created on 15 de octubre de 2013, 17:26
 */

#include "../headers/BaseGameEntity.h"
#include "../headers/Citizen.h"
#include "../headers/SteeringBehaviors.h"
#include "../headers/FlockingBehaviors.h"
#include "../headers/GameState.h"
#include "../headers/Game.h"
#include "../headers/PRoute.h"
#include "../headers/PathwalkingState.h"
#include "../headers/FlockingState.h"
#include "../headers/FollowNomaState.h"
#include "../headers/TalkToNomaState.h"
#include "../headers/StandState.h"
#include "../headers/WalkToPlaceState.h"
#include "../headers/GameState.h"
#include "../headers/TTransformation.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <time.h>

using namespace std;
#define RAD2DEG 180/3.14159;

Citizen::Citizen() {

    //GAME VARIABLES INITIALIZATION

    ID = Game::Instance()->addEntity();


    maxSpeed = 10;
    maxForce = 20;
    if (Game::Instance()->getDemoMode() == 3) {
        maxSpeed = 30;
        maxForce = 30;
    }

    mass = 2;
    path = new Path();
    rotation = 0;
    from = to = 0;
    srand(time(NULL));
    state = new PathwalkingState();
    talk = false;
    interacting = false;
    line = NULL;

    type = TCitizen;

    decrement = false;
    propagated = false;
    propagating = false;

    World * world = GameState::Instance()->getCurrentWorld();
    std::vector<int> values = world->getMoodValues();

    MIN_MOOD = values[0];
    MAX_MOOD = values[1];
    moodValue = values[2];

    values = world->getTrustValues();

    MIN_TRUST = values[0];
    MAX_TRUST = values[1];
    trustValue = values[2];

    values = world->getTalkValues();

    MIN_TALK = values[0];
    MAX_TALK = values[1];
    talkValue = values[2];


    propagationRadius = 100;

    if (Game::Instance()->getDemoMode() == 0 || Game::Instance()->getDemoMode() == 1) {
        propagationRadius = 35;
    }
}

Citizen::Citizen(const Citizen& orig) {
}

Citizen::~Citizen() {

    delete(state);
    state = NULL;
    delete(path);
    path = NULL;
    delete(line);
    line = NULL;
}

void Citizen::update() {

    frame = ((TAnimatedMesh*) graphicNode->getEntity())->getFrame();

    Vector3f prevPosition = position;
    checkFSM();

    state->update(this);

    position.X = position.X + velocity.X * FPS;
    position.Y = position.Y + velocity.Y * FPS;
    position.Z = position.Z + velocity.Z * FPS;

    if (Game::Instance()->getWhichGraphicConnector() != 0) {
        TTransformation * transformation = (TTransformation *) graphicNode->getParent()->getEntity();
        transformation->absoluteRotateY((orientation * (180)) / 3.1415);
        transformation->translate(position.X - prevPosition.X, position.Y - prevPosition.Y, position.Z - prevPosition.Z);

        //********* ENTREGABLE 8 **********//
        if (Game::Instance()->getDemoMode() == 0 || Game::Instance()->getDemoMode() == 2) {

            TTransformation * moodTrans = (TTransformation *) moodNode->getParent()->getEntity();
            moodTrans->identity();
            moodTrans->scale(moodValue, 1, moodValue);
            moodTrans->translate(0, -0.2, 0);

            TTransformation * trustTrans = (TTransformation *) trustNode->getParent()->getEntity();
            trustTrans->identity();
            trustTrans->scale(trustValue, 1, trustValue);
            trustTrans->translate(0, 0, 0);

            if (Game::Instance()->getDebugMode()) {
                TMesh * mood = (TMesh*) moodNode->getEntity();
                TMesh * trust = (TMesh*) trustNode->getEntity();
                mood->setColor(new RGBA(1.0, 0.4, 1.0, 0.5));
                trust->setColor(new RGBA(1.0, 0.6, 0.0, 0.5));

            } else if (!Game::Instance()->getDebugMode()) {
                TMesh * mood = (TMesh*) moodNode->getEntity();
                TMesh * trust = (TMesh*) trustNode->getEntity();
                mood->setColor(new RGBA(0, 0, 0, 0));
                trust->setColor(new RGBA(0, 0, 0, 0));
            }


        }
        if (Game::Instance()->getDemoMode() == 1 || Game::Instance()->getDemoMode() == 2) {

            //cout<<"propagated: "<<propagated<<endl;
            TTransformation * propTrans = (TTransformation *) propagationNode->getParent()->getEntity();
            propTrans->identity();
            propTrans->scale(propagationRadius, 1, propagationRadius);
            propTrans->translate(0, -0.2, 0);

            if (!Game::Instance()->getDebugMode()) {
                TMesh * prop = (TMesh*) propagationNode->getEntity();
                prop->setColor(new RGBA(0.0, 0.0, 0.0, 0.0));

            } else if (Game::Instance()->getDebugMode()) {
                if (propagating) {
                    TMesh * prop = (TMesh*) propagationNode->getEntity();
                    prop->setColor(new RGBA(0.0, 0.2, 0.4, 0.6));
                } else {
                    TMesh * prop = (TMesh*) propagationNode->getEntity();
                    prop->setColor(new RGBA(0.0, 0.2, 0.4, 0));
                }
            }

        }

        //********************************//
    }

    //cout << "mood: " << moodValue << ", trust: " << trustValue << ", talk: " << talkValue << endl;
    propagated = false;
    propagating = false;

    if (isNomaInRadius(propagationRadius, GameState::Instance()->getNoma())) {
        GameState::Instance()->getEnvironment()->setEnvNumber(GameState::Instance()->getEnvironment()->getEnvNumber() - 0.05);
    }

    TAnimatedMesh * animatedMesh = (TAnimatedMesh *) graphicNode->getEntity();
    animatedMesh->setCycle(TResourceAnimatedMeshContainer::Walk);
    frame += 0.5;
    animatedMesh->setFrame(frame);

}

void Citizen::checkFSM() {

    float updateMood = 0;
    float updateTrust = 0;
    float updateTalk = 0;

    float threshold = 12.0;
    float range = 20.0;

    if (Game::Instance()->getDemoMode() == 0 || Game::Instance()->getDemoMode() == 1) {
        threshold = 6.0;
        range = 10.0;
    }

    //The increment and decrement values depends on the distance between Noma and the citizen
    //Distance depends directly on increment and inversely on decrement

    Noma * noma = ((GameState *) Game::Instance()->getCurrentState())->getNoma();
    Vector3f distance = this->getPosition() - noma->getPosition();
    float value = distance.magnitude() / (moodValue + range); //Value between [0,1] 


    float incrementValue = (1 - value) * 10;
    float decrementValue = value * 5;

    float angle = (atan2(distance.X, distance.Z));
    angle *= RAD2DEG;
    float nomaAngle = noma->getRotation();

    if ((state->getIndex() == CitizenState::Pathwalking)) {

        if (decrement == true && decrementCounter > 0) { //There were a bad action
            updateMood = -totalDecrementValue / 100;
            updateTrust = -totalDecrementValue / 100;
            updateTalk = -totalDecrementValue / 100;

            decrementCounter--;

            if (moodValue <= MIN_MOOD && trustValue <= MIN_TRUST && talkValue <= MIN_TALK) {
                decrement = false;
            }
            if (decrementCounter == 0) {
                decrement = false;
            }
        }


        if ((isNomaInRadius(moodValue + range, noma)) && !noma->isInteracting() && !talk && GameState::Instance()->getCurrentWorld()->hasCitizenLines()) { //Increment because Noma is near you

            decrement = false;
            updateTrust = incrementValue / 10;
            updateMood = incrementValue / 10;

            if (trustValue >= threshold && !talk && !isAnyNeighborInteracting()) { //Follow Noma because Im enough confident and Noma is free
                interacting = true;
                resetPath();
                changeState(new FollowNomaState());
            }
        }

    } else if ((state->getIndex() == CitizenState::FollowNoma)) {

        if ((isNomaInRadius(trustValue, noma) && !noma->isInteracting()) && talkValue >= threshold && !noma->isWalking()) { //Noma is near and Im enough confident to talk, get the scriptline and talk
            line = GameState::Instance()->getCurrentWorld()->getScriptLineCitizen();
            if (line != NULL) {
                noma->setInteracting(true);
                changeState(new TalkToNomaState());
            }
        }

        if (!isNomaInRadius(trustValue, noma) && isNomaInRadius(moodValue + (5 * range), noma)) { //Both are standing, Citizen should now move to Noma

            FollowNomaState * follow = (FollowNomaState *) state;

            if (!noma->isWalking()) {
                if (moodValue <= MIN_MOOD) updateMood = incrementValue / 10;
                if (talkValue <= MIN_TALK) updateTalk = incrementValue / 10;
                if (trustValue <= MIN_TRUST) updateTrust = incrementValue / 10;

                if (Game::Instance()->getDemoMode() != 1)
                    follow->setStraightFollowNoma(true);
            }

            if (follow->getStraightFollowNoma() && noma->isWalking())
                follow->setStraightFollowNoma(false);
        }

        if (isNomaInRadius(moodValue + (5 * range), noma) && !isNomaInRadius(moodValue, noma) && noma->isWalking()) { //Noma is walking

            if (abs(angle - nomaAngle) > 90) { //Noma is fleeing of me
                updateMood = -decrementValue / 20;
                updateTrust = -decrementValue / 20;
                updateTalk = -decrementValue / 20;
            } else { //Noma is facing me
                updateMood = incrementValue / 10;
                updateTrust = incrementValue / 10;
                updateTalk = incrementValue / 10;
            }
        }

        if (!isNomaInRadius(moodValue + (5 * range), noma)) { //Noma has gone far
            decrement = true;
            totalDecrementValue = decrementValue;
            decrementCounter = 100;
            interacting = false;
            noma->setInteracting(false);
            line = NULL;
            resetPath();
            //decrement = true;
            changeState(new PathwalkingState());
        }


        if (isNomaInRadius(moodValue, noma))
            updateTalk = incrementValue;

    } else if ((state->getIndex() == CitizenState::TalkToNoma)) {

        if (!isNomaInRadius(trustValue + 5, noma)) { //Noma doesnt want to talk to me, negative reaction
            decrement = true;
            totalDecrementValue = incrementValue; //Take the positive value
            cout << "totalDecrement: " << totalDecrementValue << endl;
            decrementCounter = 400;
            talk = true;
            noma->setInteracting(false);
            line = NULL;
            interacting = false;
            changeState(new PathwalkingState());
        }
        if (!noma->isInteracting() && isNomaInRadius(trustValue, noma)) { //Noma has finished talking to me, positive reaction
            updateTrust = incrementValue;
            updateTalk = incrementValue;
            updateMood = incrementValue;
            talk = true;
            interacting = false;
            line = NULL;
            changeState(new PathwalkingState());
        }

    } else if ((state->getIndex() == CitizenState::WalkToPlace)) { //Im taking Noma to somewhere important

        if (!isNomaInRadius(moodValue + range, noma)) { //I must wait until Noma is near me again
            decrement = true;
            totalDecrementValue = decrementValue * 2;
            decrementCounter = 400;

            changeState(new StandState());
        }

        if (!noma->isInteracting() && state->getIndex() == CitizenState::WalkToPlace) { //Positive reaction
            if (line->isRead()) {
                updateMood = incrementValue;
                updateTrust = incrementValue;
                updateTalk = incrementValue;
                talk = true;
                interacting = false;
                line = NULL;
                changeState(new PathwalkingState());
            }
        }


    } else if ((state->getIndex() == CitizenState::Stand)) { //I wait until Noma is near me

        if (decrement == true && decrementCounter > 0) {
            updateMood = -totalDecrementValue / 100;
            updateTrust = -totalDecrementValue / 100;
            decrementCounter--;

            if (decrementCounter == 0) {
                decrement = false;
            }
        }

        if (isNomaInRadius(moodValue + 10, noma)) {
            decrement = false;
            noma->setInteracting(true);
            changeState(new WalkToPlaceState());
        }

    } else if ((state->getIndex() == CitizenState::Flocking)) { //Flocking state


    }

    //cout<<"Updates: "<<updateMood<<","<<updateTrust<<","<<updateTalk<<endl;
    updatePersonality(updateMood, updateTrust, updateTalk);

}

void Citizen::updatePersonality(float updateMood, float updateTrust, float updateTalk) {

    float value = 0.05;

    moodValue += updateMood * value;
    trustValue += updateTrust * value;
    talkValue += updateTalk * value;


    if (moodValue > MAX_MOOD) moodValue = MAX_MOOD;
    if (trustValue > MAX_TRUST) trustValue = MAX_TRUST;
    if (talkValue > MAX_TALK) talkValue = MAX_TALK;

    if (moodValue < MIN_MOOD) moodValue = MIN_MOOD;
    if (trustValue < MIN_TRUST) trustValue = MIN_TRUST;
    if (talkValue < MIN_TALK) talkValue = MIN_TALK;

    //********* ENTREGABLE 8 **********//
    if ((Game::Instance()->getDemoMode() == 0 || Game::Instance()->getDemoMode() == 1) && !propagated) {

        TMesh * mesh = (TMesh *) graphicNode->getEntity();
        RGBA *color = new RGBA(1.0, 1.0, 1.0, 0.0);

        if (updateTalk < 0 || updateTrust < 0 || updateMood < 0) {
            color->r = 1.0;
            color->g = 0.0;
            color->b = 0.0;
            color->a = 1.0;
        }
        if (updateTalk > 0 || updateTrust > 0 || updateMood > 0) {
            color->r = 0.0;
            color->g = 1.0;
            color->b = 0.0;
            color->a = 1.0;
        }

        //cout << "My color: "<< color->r << "," << color->g << "," << color->b << "," << color->a << endl;
        mesh->setColor(color);

    }
    //********************************//

    if (updateTalk != 0 || updateTrust != 0 || updateMood != 0) //Propagate only if changes
        propagateChangesToNeighbors(updateMood, updateTrust, updateTalk);
}

void Citizen::propagateChangesToNeighbors(float updateMood, float updateTrust, float updateTalk) {

    std::vector<BaseGameEntity *> neighborhood = this->getNeighborhood(GameState::Instance()->getEntities(), propagationRadius);
    propagating = true;

    for (int i = 0; i < neighborhood.size(); i++) {

        if (typeid (* neighborhood[i]) == typeid (Citizen)) {

            Vector3f distance = this->getPosition() - neighborhood[i]->getPosition();
            float numericDist = distance.magnitude();
            Citizen * n = (Citizen *) neighborhood[i];
            float value = 0.01;

            n->addMoodValue(updateMood * value * (numericDist / propagationRadius));
            n->addTrustValue(updateTrust * value * (numericDist / propagationRadius));
            n->addTalkValue(updateTalk * value * (numericDist / propagationRadius));


            //********* ENTREGABLE 8 **********//
            if (Game::Instance()->getDemoMode() == 0 || Game::Instance()->getDemoMode() == 1) {

                TMesh * mesh = (TMesh *) n->getGraphicNode()->getEntity();
                RGBA *color = new RGBA(1.0, 1.0, 1.0, 0.0);

                if (updateTalk < 0 || updateTrust < 0 || updateMood < 0) {
                    color->r = 1.0 * (1 - (numericDist / propagationRadius));
                    color->g = 0.0;
                    color->b = 0.0;
                    color->a = 1.0;
                }
                if (updateTalk > 0 || updateTrust > 0 || updateMood > 0) {
                    color->r = 0.0;
                    color->g = 1.0 * (1 - (numericDist / propagationRadius));
                    color->b = 0.0;
                    color->a = 1.0;
                }
                //cout<<"neighbor update color: "<<color->r<<", "<<color->g<<", "<<color->b<<", "<<color->a<<endl;

                mesh->setColor(color);
            }
            //********************************//

            n->setPropagated(true);
        }
    }
}

bool Citizen::isNomaInRadius(float rad, Noma * noma) {

    bool is = false;

    Vector3f distance = this->getPosition() - noma->getPosition();
    float numericDist = distance.magnitude();
    if (numericDist < rad) is = true;

    return is;
}

void Citizen::changeState(CitizenState* newState) {
    state = newState;
}

void Citizen::avoidPenetrationWithNeighbors(std::vector<BaseGameEntity*> neighborhood, float radius, float divide, float overlapNoma) {

    Vector3f prev = velocity;

    for (int i = 0; i < neighborhood.size(); i++) {
        Vector3f toNeighbor = this->getPosition() - neighborhood[i]->getPosition();
        float dist = toNeighbor.magnitude();

        float overlap = 2 * radius - dist;
        if (overlap >= 0)
            velocity = velocity + ((toNeighbor / dist) * overlap) / divide;
    }

    Vector3f toNoma = this->getPosition() - GameState::Instance()->getNoma()->getPosition();
    float dist = toNoma.magnitude();

    float overlap = overlapNoma - dist;
    if (overlap >= 0)
        velocity = velocity + ((toNoma / dist) * overlap) / divide;

    velocity.Y = prev.Y;
}

bool Citizen::isAnyNeighborInteracting() {

    bool anyone = false;
    int i = 0;
    std::vector<BaseGameEntity *> entities = GameState::Instance()->getEntities();
    while (!anyone && i < entities.size()) {
        if (typeid (* entities[i]) == typeid (Citizen)) {
            Citizen *c = (Citizen *) entities[i];
            anyone = c->getInteracting();
        }
        i++;
    }

    return anyone;

}