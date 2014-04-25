/* 
 * File:   FlockingState.h
 * Author: laurasirventcollado
 *
 * Created on 9 de enero de 2014, 11:55
 */

#ifndef FLOCKINGSTATE_H
#define	FLOCKINGSTATE_H
#include "CitizenState.h"
#include "Citizen.h"

class FlockingState : public CitizenState {
public:
    FlockingState();
    FlockingState(const FlockingState& orig);
    virtual ~FlockingState();
    void update(Citizen * me);
private:

};

#endif	/* FLOCKINGSTATE_H */

