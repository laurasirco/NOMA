/* 
 * File:   WalkToPlaceState.h
 * Author: laurasirventcollado
 *
 * Created on 10 de enero de 2014, 10:25
 */

#ifndef WALKTOPLACESTATE_H
#define	WALKTOPLACESTATE_H
#include "CitizenState.h"
#include "Citizen.h"

class WalkToPlaceState : public CitizenState {
public:
    WalkToPlaceState();
    WalkToPlaceState(const WalkToPlaceState& orig);
    virtual ~WalkToPlaceState();
    void update(Citizen * me);
private:
};

#endif	/* WALKTOPLACESTATE_H */

