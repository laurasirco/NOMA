/* 
 * File:   MapState.h
 * Author: MAC
 *
 * Created on 15 de octubre de 2013, 17:34
 */

#ifndef MAPSTATE_H
#define	MAPSTATE_H
#include "State.h"
#include "GUIButton.h"
#include "GUIOrbit.h"
#include "GUIBackground.h"
#include "GUIText.h"

class MapState : public State{
public:
    MapState();
    MapState(const MapState& orig);
    static MapState * Instance();
    virtual ~MapState();
    void eventManager();
    void update();
    void render(bool interpolation = true);
    void pause();
    void resume();
    void deleteState();
    void setTravellingAllowed(bool t);
private:
    static MapState * pinstance;
    bool enterKey;
    int angle;
    std::vector<GUIButton *> planets;
    std::vector<GUIOrbit *> orbits;
    GUIText * infoText;
    Vector3f center;
};

#endif	/* MAPSTATE_H */

