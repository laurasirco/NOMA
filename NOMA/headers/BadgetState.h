/* 
 * File:   BadgetState.h
 * Author: MAC
 *
 * Created on 15 de octubre de 2013, 17:33
 */

#ifndef BADGETSTATE_H
#define	BADGETSTATE_H
#include "State.h"

class BadgetState : public State{
public:
    BadgetState();
    BadgetState(const BadgetState& orig);
    virtual ~BadgetState();
private:

};

#endif	/* BADGETSTATE_H */

