/* 
 * File:   EventManager.h
 * Author: MAC
 *
 * Created on 15 de octubre de 2013, 17:39
 */

#ifndef EVENTMANAGER_H
#define	EVENTMANAGER_H

#include "../Irrlicht/include/irrlicht.h"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


class EventManager : public IEventReceiver {
public:
    EventManager();
    EventManager(const EventManager& orig);
    virtual ~EventManager();
    static EventManager * Instance();
    
    //For Irrlicht
    virtual bool OnEvent(const SEvent &event);
    virtual bool isKeyDown(EKEY_CODE keyCode) const;
    virtual bool isKeyUp(EKEY_CODE keyCode) const;

    struct SMouseState {
        position2di Position;
        bool leftButtonDown;

        SMouseState() : leftButtonDown(false) {
        }
    } mouseState;
    
    const SMouseState & getMouseState() const { return mouseState; }
    
    //For TAG
    static void keyPressed(unsigned char key, int x, int y);
    static void keyUp(unsigned char key, int x, int y);
    static void processMouse(int button, int state, int x, int y);
    static void passiveMouseMoved(int x, int y);
    static void mouseMoved(int x, int y);
    static int getMouseX() { return mouseX;}
    static int getMouseY() { return mouseY;}
    
    void resetAllKeys();
    

private:
    static EventManager * pinstance;
    static bool KeyDown[255];
    static int mouseX;
    static int mouseY;

};

#endif	/* EVENTMANAGER_H */

