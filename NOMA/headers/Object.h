/* 
 * File:   Object.h
 * Author: MAC
 *
 * Created on 15 de octubre de 2013, 17:23
 */

#ifndef OBJECT_H
#define	OBJECT_H

#include "MovingEntity.h"

class Object : public MovingEntity {
public:
    Object();
    Object(const Object& orig);
    virtual ~Object();
private:

};

#endif	/* OBJECT_H */

