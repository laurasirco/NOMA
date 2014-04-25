/* 
 * File:   NeutralState.cpp
 * Author: MAC
 * 
 * Created on 19 de noviembre de 2013, 17:35
 */

#include "../headers/NeutralState.h"

NeutralState::NeutralState() {
}

NeutralState::NeutralState(const NeutralState& orig) {
}

NeutralState::~NeutralState() {
}

void NeutralState::update(Environment * environment, Noma * noma){
    

    environment->setColor("white", Environment::RGB(255,255,255));
    environment->setMusic("neutral");
    environment->setWeather("neutral");
}

void NeutralState::render(){
    
}

