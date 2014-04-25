/* 
 * File:   RegisterState.h
 * Author: laurasirventcollado
 *
 * Created on 18 de abril de 2014, 12:21
 */

#ifndef REGISTERSTATE_H
#define	REGISTERSTATE_H
#include "State.h"
#include "GUIBackground.h"
#include "GUIText.h"
#include "GUIButton.h"
#include "GUISlider.h"
#include <iostream>
#include <vector>

class RegisterState : public State {
public:
    RegisterState();
    RegisterState(const RegisterState& orig);
    virtual ~RegisterState();
    static RegisterState * Instance();
    void eventManager();
    void update();
    void render(bool interpolation = true);
    void pause();
    void resume();
    void deleteState();
private:
    static RegisterState * pinstance;
};

#endif	/* REGISTERSTATE_H */

