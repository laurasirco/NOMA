/* 
 * File:   BlankState.h
 * Author: laurasirventcollado
 *
 * Created on 14 de marzo de 2014, 18:02
 */

#ifndef BLANKSTATE_H
#define	BLANKSTATE_H
#include "State.h"
#include "GUIElement.h"
#include <iostream>

class BlankState : public State {
public:
    BlankState();
    BlankState(const BlankState& orig);
    virtual ~BlankState();
    static BlankState * Instance();
    void eventManager();
    void update();
    void render(bool interpolation = true);
    void pause();
    void resume();
    void deleteState();
    
    void setColor(RGBA * c){ color = c; }
    void setNewWorld(std::string world){ newWorld = world; }
    
private:

    static BlankState * pinstance;
    RGBA * color;
    
    std::string newWorld;
    bool changed;
    
};

#endif	/* BLANKSTATE_H */

