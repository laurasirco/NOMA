/* 
 * File:   Environment.cpp
 * Author: laurasirventcollado
 * 
 * Created on 18 de noviembre de 2013, 11:34
 */

#include "../headers/Environment.h"
#include "../headers/CalmState.h"
#include "../headers/NeutralState.h"
#include "../headers/TenseState.h"
#include "../headers/Game.h"
#include "../headers/GameState.h"
#include "../headers/Noma.h"
#include "../headers/AudioEngine.h"
#include <iostream>
#include <ctime>
#include <typeinfo>

using namespace std;

Environment::Environment() {

    time_t now = time(0);
    tm *ltm = localtime(&now);
    hour = ltm->tm_hour;
    envNumber = 50.0f;
    if (hour < 12 && hour > 6) {
        envNumber += 20;
    } else if (hour < 20 && hour > 12) {
        //envNumber = envNumber;
    } else if (hour < 6 && hour > 0) {
        envNumber -= 20;
    } else {
        envNumber -= 20;
    }
    currentState = new NeutralState();
    //update();
}

Environment::Environment(const Environment& orig) {
}

Environment::~Environment() {
    delete(currentState);
    currentState = NULL;
    noma = NULL;
}

void Environment::update() {

    if (noma == NULL) {
        GameState *gState = (GameState*) Game::Instance()->getCurrentState();
        noma = gState->getNoma();
    }

    //Truncate to 0-100 if needed
    if (envNumber < 0) envNumber = 0;
    if (envNumber > 100) envNumber = 100;


    //Select State
    if (antEnvNumber > 32 && envNumber <= 32) {
        changeState(new CalmState());
        cout << "pasamos a calmado" << endl;
        
    } else if ((antEnvNumber > 65 && envNumber <= 65) || (antEnvNumber < 32 && envNumber >= 32)) {
        changeState(new NeutralState());
        cout << "pasamos a neutro" << endl;
        AudioEngine::Instance()->play2DRandomSound("Audio/Ambient/neutralAmbient",3);
    } else if (antEnvNumber < 65 && envNumber >= 65) {
        changeState(new TenseState());
        cout << "pasamos a tenso" << endl;
        AudioEngine::Instance()->play2DSound("Audio/Ambient/tenseAmbient1.ogg");
    }

    antEnvNumber = envNumber;

    currentState->update(this, noma);


    if (envNumber <= 50) {
        color.r = envNumber / 50.0;
        color.g = envNumber / 50.0;
        color.b = 1.0;
    }

    if (envNumber > 50) {
        color.r = 1.0;
        color.g = 1.0 - ((envNumber / 50.0) - 1.0);
        color.b = 1.0 - ((envNumber / 50.0) - 1.0);
    }

    //cout<<"EnvNumber: "<<envNumber<<" Color: "<<color.r<<", "<<color.g<<", "<<color.b<<endl;

    /*if ((noma->getActivity() > 80 && noma->getTemperament() > 50) || (noma->getConfidence() < 30 && noma->getConversation() <30)) {
        changeState(new TenseState());
    }
    else if (((noma->getActivity() < 40 && noma->getTemperament() <50) || (noma->getConfidence() > 60)) && typeid (currentState) == typeid (NeutralState *)) {
        changeState(new CalmState());
    }
    else {
        changeState(new NeutralState());
    }*/


}

void Environment::changeState(EnvState* newState) {

    //Delete current State
    /*if(currentState == NULL){
        currentState = newState;
    }
    else{
        delete(currentState);
        currentState = NULL;
        currentState = newState;
    }*/
    currentState = newState;

    //Point to the new state

}

