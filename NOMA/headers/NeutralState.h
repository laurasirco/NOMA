/* 
 * File:   NeutralState.h
 * Author: MAC
 *
 * Created on 19 de noviembre de 2013, 17:35
 */

#ifndef NEUTRALSTATE_H
#define	NEUTRALSTATE_H
#include "EnvState.h"
#include "Environment.h"

class NeutralState : public EnvState {
public:
    NeutralState();
    NeutralState(const NeutralState& orig);
    virtual ~NeutralState();
    void update(Environment * environment, Noma * noma);
    void render();
private:

};

#endif	/* NEUTRALSTATE_H */

