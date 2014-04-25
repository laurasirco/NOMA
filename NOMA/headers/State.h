/* 
 * File:   State.h
 * Author: MAC
 *
 * Created on 15 de octubre de 2013, 17:28
 */

#ifndef STATE_H
#define	STATE_H
#include "GUIElement.h"
#include <iostream>
#include <vector>
#include <algorithm>

class State {
public:

    enum Type {
        MainMenu, Game, Map, Option, Badget, Blank, Popup, Login, Register
    };

    State();
    State(const State& orig);
    virtual ~State();
    void init();
    virtual void pause() = 0;
    virtual void resume() = 0;
    void cleanup();
    virtual void deleteState() = 0;
    virtual void eventManager() = 0;
    virtual void update() = 0;
    virtual void render(bool interpolation = true) = 0;

    Type getType() {
        return type;
    }

    void addGUIElement(GUIElement * element) {
        GUIElements.push_back(element);
    }

    void removeGUIElement(GUIElement * element) {
        for (std::vector<GUIElement *>::iterator it = GUIElements.begin(); it != GUIElements.end(); it++) {
            if (*it == element) {
                GUIElements.erase(it);
                break;
            }
        }
    }

    std::vector<GUIElement *> getGUIElements() {
        return GUIElements;
    }

private:
    State * currentState;
protected:
    //int type;
    Type type;
    std::vector<GUIElement *> GUIElements;
};

#endif	/* STATE_H */

