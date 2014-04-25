/* 
 * File:   RegisterState.cpp
 * Author: laurasirventcollado
 * 
 * Created on 18 de abril de 2014, 12:21
 */

#include "../headers/RegisterState.h"

RegisterState::RegisterState() {
}

RegisterState::RegisterState(const RegisterState& orig) {
}

RegisterState::~RegisterState() {
}

RegisterState * RegisterState::pinstance = 0;

RegisterState * RegisterState::Instance(){
    if(pinstance == 0){
        pinstance = new RegisterState;
    }
    return pinstance;
}

void RegisterState::update() {

}

void RegisterState::render(bool interpolation) {

}

void RegisterState::deleteState() {

}

void RegisterState::pause() {

}

void RegisterState::resume() {

}

void RegisterState::eventManager() {

}
