/* 
 * File:   CalmState.cpp
 * Author: MAC
 * 
 * Created on 19 de noviembre de 2013, 17:33
 */

#include "../headers/CalmState.h"

CalmState::CalmState() {
}

CalmState::CalmState(const CalmState& orig) {
}

CalmState::~CalmState() {
}

void CalmState::update(Environment * environment, Noma * noma) {
    
    environment->setColor("green", Environment::RGB(0,255,0));
    environment->setMusic("calm");
    environment->setWeather("calm");
}

void CalmState::render() {
}



