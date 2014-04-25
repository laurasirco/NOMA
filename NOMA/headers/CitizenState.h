/* 
 * File:   CitizenState.h
 * Author: laurasirventcollado
 *
 * Created on 8 de enero de 2014, 11:19
 */

#ifndef CITIZENSTATE_H
#define	CITIZENSTATE_H
class Citizen;

class CitizenState {
public:
    
    enum Index{ Pathwalking, FollowNoma, TalkToNoma, WalkToPlace, Stand, Flocking };
    
    CitizenState();
    CitizenState(const CitizenState& orig);
    virtual ~CitizenState();
    virtual void update(Citizen * me) = 0;
    Index getIndex(){ return index; }
private:
protected:
    Index index;
};


#endif	/* CITIZENSTATE_H */

