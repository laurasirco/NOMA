/* 
 * File:   TalkToNomaState.h
 * Author: laurasirventcollado
 *
 * Created on 10 de enero de 2014, 10:24
 */

#ifndef TALKTONOMASTATE_H
#define	TALKTONOMASTATE_H
#include "CitizenState.h"
#include "Citizen.h"

class TalkToNomaState : public CitizenState {
public:
    TalkToNomaState();
    TalkToNomaState(const TalkToNomaState& orig);
    virtual ~TalkToNomaState();
    void update(Citizen * me);
private:

};

#endif	/* TALKTONOMASTATE_H */

