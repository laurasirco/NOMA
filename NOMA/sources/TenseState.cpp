/* 
 * File:   TenseState.cpp
 * Author: MAC
 * 
 * Created on 19 de noviembre de 2013, 17:36
 */

#include "../headers/TenseState.h"

TenseState::TenseState() {
}

TenseState::TenseState(const TenseState& orig) {
}

TenseState::~TenseState() {
}

void TenseState::update(Environment * environment, Noma * noma) {

    environment->setColor("red", Environment::RGB(255,0,0));
    environment->setMusic("tense");
    environment->setWeather("tense");
}

void TenseState::render() {

}

