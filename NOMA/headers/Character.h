/* 
 * File:   Character.h
 * Author: MAC
 *
 * Created on 15 de octubre de 2013, 17:22
 */

#ifndef CHARACTER_H
#define	CHARACTER_H
#include "../Bullet/src/btBulletDynamicsCommon.h"
#include "../Bullet/src/BulletDynamics/Character/btKinematicCharacterController.h"
#include "MovingEntity.h"

class Character : public MovingEntity {
public:
    Character();
    Character(const Character& orig);
    virtual ~Character();
    void setPhysicsPosition(Vector3f pos);
private:
protected:
    btKinematicCharacterController *m_character;
    btPairCachingGhostObject* m_ghostObject;
    
};

#endif	/* CHARACTER_H */

