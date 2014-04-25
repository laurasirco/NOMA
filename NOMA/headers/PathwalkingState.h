/* 
 * File:   PathwalkingState.h
 * Author: laurasirventcollado
 *
 * Created on 9 de enero de 2014, 11:23
 */

#ifndef PATHWALKINGSTATE_H
#define	PATHWALKINGSTATE_H
#include "CitizenState.h"
#include "Citizen.h"

class PathwalkingState : public CitizenState {
public:
    PathwalkingState();
    PathwalkingState(const PathwalkingState& orig);
    virtual ~PathwalkingState();
    void update(Citizen * me);
private:
    
};

#endif	/* PATHWALKINGSTATE_H */

