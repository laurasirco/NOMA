/* 
 * File:   LoginState.h
 * Author: laurasirventcollado
 *
 * Created on 18 de abril de 2014, 12:19
 */

#ifndef LOGINSTATE_H
#define	LOGINSTATE_H
#include "State.h"
#include "GUIBackground.h"
#include "GUIText.h"
#include "GUIButton.h"
#include "GUISlider.h"
#include <iostream>
#include <vector>


class LoginState : public State {
public:
    LoginState();
    LoginState(const LoginState& orig);
    virtual ~LoginState();
    static LoginState * Instance();
    void eventManager();
    void update();
    void render(bool interpolation = true);
    void pause();
    void resume();
    void deleteState();
private:
    static LoginState * pinstance;
    
    GUIText * usernameText;
    GUIText * passwordText;
};

#endif	/* LOGINSTATE_H */

