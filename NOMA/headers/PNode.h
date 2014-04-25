/* 
 * File:   PNode.h
 * Author: laurasirventcollado
 *
 * Created on 30 de octubre de 2013, 12:30
 */

#ifndef PNODE_H
#define	PNODE_H

#include "BaseGameEntity.h"

class PNode {
public:
    PNode();
    PNode(int idx, Vector3f p) { index = idx; position = p; }
    PNode(const PNode& orig);
    virtual ~PNode();
    
    void setIndex(int i){ index = i; }
    int getIndex(){ return index; }
    Vector3f getPosition(){ return position; }
    float getF() { return g+h; }
    float getG() { return g; }
    void setG(int newG){ g = newG; }
    void setH(int newH){ h = newH; }
    void setParent(PNode* newParent) { parent = newParent; }
    int Estimate(PNode* end);
    PNode* getParent() { return parent; }
    
private:
    Vector3f position;
    int index;
    float g; //Coste desde el principio
    float h; //Coste estimado
    float f; //Suma de costes
    PNode* parent;
    
    
};

#endif	/* PNODE_H */

