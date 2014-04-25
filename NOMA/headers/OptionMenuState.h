/* 
 * File:   OptionMenuState.h
 * Author: MAC
 *
 * Created on 15 de octubre de 2013, 17:31
 */

#ifndef OPTIONMENUSTATE_H
#define	OPTIONMENUSTATE_H
#include "State.h"
#include "GUIBackground.h"
#include "GUIText.h"
#include "GUIButton.h"
#include "GUISlider.h"
#include <iostream>
#include <vector>

class OptionMenuState : public State{
public:
    OptionMenuState();
    OptionMenuState(const OptionMenuState& orig);
    virtual ~OptionMenuState();
    static OptionMenuState * Instance();
    void eventManager();
    void update();
    void render(bool interpolation = true);
    void pause();
    void resume();
    void deleteState();
    
    void increaseResolution();
    void decreaseResolution();
    void increaseGraphics();
    void decreaseGraphics();
    
    int getGraphicsQuality(){ return graphicsCounter; }
    
private:
    static OptionMenuState * pinstance;
    
    GUISlider * fxSlider;
    GUISlider * musicSlider;
    GUISlider * voicesSlider;
    
    GUIText * fxNumber;
    GUIText * musicNumber;
    GUIText * voicesNumber;
    
    GUIText * resolutionValue;
    GUIText * graphicsValue;
    
    std::vector<const wchar_t *> resolutionsVector;
    std::vector<const wchar_t *> graphicsVector;
    int resolutionsCounter;
    int graphicsCounter;
};

#endif	/* OPTIONMENUSTATE_H */

