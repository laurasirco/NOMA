/* 
 * File:   BaseGameEntity.cpp
 * Author: laurasirventcollado
 * 
 * Created on 25 de octubre de 2013, 10:33
 */

#include "../headers/BaseGameEntity.h"
#include "../headers/Game.h"

BaseGameEntity::BaseGameEntity() {
    
    position.X = 0; position.Y = 0; position.Z = 0;
    orientation = 0;
    graphicNode = NULL;
    frame = 0;
}


BaseGameEntity::~BaseGameEntity() {
}

std::vector<BaseGameEntity *> BaseGameEntity::getNeighborhood(EntitiesVector entities, float radius){
    
    EntitiesVector neighborhood;
    EntitiesVectorIterator nb = neighborhood.begin();
    for(EntitiesVectorIterator it = entities.begin(); it != entities.end(); ++it){
        
        BaseGameEntity *n = *it;
        if(n->getPosition().X <= position.X+radius && n->getPosition().X >= position.X-radius){
            if(n->getPosition().Y <= position.Y+radius && n->getPosition().Y >= position.Y-radius){
                if(n->getPosition().Z <= position.Z+radius && n->getPosition().Z >= position.Z-radius){
                    if(n != this){
                        neighborhood.insert(nb, n);
                        nb = neighborhood.end();
                    }
                }
            }
        }
        
    }
    return neighborhood;
}

