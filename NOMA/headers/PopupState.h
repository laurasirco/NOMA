/* 
 * File:   PopupState.h
 * Author: laurasirventcollado
 *
 * Created on 19 de marzo de 2014, 13:32
 */

#ifndef POPUPSTATE_H
#define	POPUPSTATE_H
#include "State.h"
#include "GUIBackground.h"
#include "GUIText.h"
#include "GUIButton.h"
#include "GUISlider.h"
#include <iostream>
#include <vector>

class PopupState : public State {
public:
    PopupState();
    PopupState(const PopupState& orig);
    virtual ~PopupState();
    static PopupState * Instance();
    void eventManager();
    void update();
    void render(bool interpolation = true);
    void pause();
    void resume();
    void deleteState();
    void increaseDemo();
    void decreaseDemo();
    int getSelectedDemo(){ return counter; }
    void resetCounter(){ counter = 0; }
private:
    static PopupState * pinstance;
    
    int counter;
    std::vector<const wchar_t *> demoTitles;
    std::vector<const wchar_t *> demoExplanations;
    GUIText * currentTitle;
    GUIText * currentExplanation;
    
    bool escapePressed;
    
};

#endif	/* POPUPSTATE_H */

