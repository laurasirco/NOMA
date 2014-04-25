/* 
 * File:   MainMenuState.h
 * Author: MAC
 *
 * Created on 15 de octubre de 2013, 17:32
 */

#ifndef MAINMENUSTATE_H
#define	MAINMENUSTATE_H
#include "State.h"
#include "GUIButton.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct MenuItem{
    
    int x1; int y1;
    int x2; int y2;
    wchar_t * title;
    wchar_t * tooltip;
};

class MainMenuState : public State{
public:
    MainMenuState();
    MainMenuState(const MainMenuState& orig);
    virtual ~MainMenuState();
    static MainMenuState * Instance();
    void eventManager();
    void update();
    void render(bool interpolation = true);
    void pause();
    void resume();
    void deleteState();
    
    void showSavedGames();
    GUIButton * getDebugButton(){ return debugButton; }
private:
    static MainMenuState * pinstance;
    vector<MenuItem> menuItems;
    vector<GUIButton *> demoButtons;
    bool isSavedGamesShowing;
    
    GUIButton * debugButton;
};

#endif	/* MAINMENUSTATE_H */

