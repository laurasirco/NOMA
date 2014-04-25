/* 
 * File:   EnvState.h
 * Author: laurasirventcollado
 *
 * Created on 18 de noviembre de 2013, 12:31
 */

#ifndef ENVSTATE_H
#define	ENVSTATE_H
#include "Noma.h"
class Environment;

class EnvState {
public:
    EnvState();
    EnvState(const EnvState& orig);
    virtual ~EnvState();
    virtual void update(Environment * environment, Noma * noma) = 0;
    virtual void render() = 0;
private:
};

#endif	/* ENVSTATE_H */

