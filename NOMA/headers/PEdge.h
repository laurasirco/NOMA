/* 
 * File:   PEdge.h
 * Author: laurasirventcollado
 *
 * Created on 30 de octubre de 2013, 12:36
 */

#ifndef PEDGE_H
#define	PEDGE_H

#include "PNode.h"

class PEdge {
public:
    PEdge();
    PEdge(int f, int t, double c): fromNode(f),toNode(t),cost(c) {}
    PEdge(int f, int t): fromNode(f),toNode(t),cost(1.0) {  }
    PEdge(const PEdge& orig);
    virtual ~PEdge();
    
    void setFromNode(int f){ fromNode = f; }
    void setToNode(int t){ toNode = t; }
    void setCost(double c){ cost = c; }
    
    int getFromNode(){ return fromNode; }
    int getToNode(){ return toNode; }
    
private:
    int fromNode;
    int toNode;
    double cost;
};

#endif	/* PEDGE_H */

