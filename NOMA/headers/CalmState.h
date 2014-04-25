/* 
 * File:   CalmState.h
 * Author: MAC
 *
 * Created on 19 de noviembre de 2013, 17:33
 */

#ifndef CALMSTATE_H
#define	CALMSTATE_H
#include "EnvState.h"
#include "Environment.h"

class CalmState : public EnvState {
public:
    CalmState();
    CalmState(const CalmState& orig);
    virtual ~CalmState();
    void update(Environment * environment, Noma * noma);
    void render();
private:

};

#endif	/* CALMSTATE_H */

