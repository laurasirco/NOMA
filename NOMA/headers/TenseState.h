/* 
 * File:   TenseState.h
 * Author: MAC
 *
 * Created on 19 de noviembre de 2013, 17:36
 */

#ifndef TENSESTATE_H
#define	TENSESTATE_H
#include "EnvState.h"
#include "Environment.h"

class TenseState : public EnvState {
public:
    TenseState();
    TenseState(const TenseState& orig);
    virtual ~TenseState();
    void update(Environment * environment, Noma * noma);
    void render();
private:

};

#endif	/* TENSESTATE_H */

