/* 
 * File:   StandState.h
 * Author: laurasirventcollado
 *
 * Created on 10 de enero de 2014, 10:36
 */

#ifndef STANDSTATE_H
#define	STANDSTATE_H
#include "CitizenState.h"
#include "Citizen.h"

class StandState : public CitizenState{
public:
    StandState();
    StandState(const StandState& orig);
    virtual ~StandState();
    void update(Citizen * me);
private:

};

#endif	/* STANDSTATE_H */

