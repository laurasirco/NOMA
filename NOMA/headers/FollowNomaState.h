/* 
 * File:   FollowNomaState.h
 * Author: laurasirventcollado
 *
 * Created on 9 de enero de 2014, 12:16
 */

#ifndef FOLLOWNOMASTATE_H
#define	FOLLOWNOMASTATE_H
#include "CitizenState.h"
#include "Citizen.h"

class FollowNomaState : public CitizenState {
public:
    FollowNomaState();
    FollowNomaState(const FollowNomaState& orig);
    virtual ~FollowNomaState();
    void update(Citizen * me);
    void setStraightFollowNoma(bool f){ straightFollowNoma = f; }
    bool getStraightFollowNoma(){ return straightFollowNoma; }
private:
    bool straightFollowNoma;
};

#endif	/* FOLLOWNOMASTATE_H */

