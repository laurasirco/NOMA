/* 
 * File:   PNode.cpp
 * Author: laurasirventcollado
 * 
 * Created on 30 de octubre de 2013, 12:30
 */

#include "../headers/PNode.h"
#include <vector>

PNode::PNode() {
}

PNode::PNode(const PNode& orig) {
}

PNode::~PNode() {
}


int PNode::Estimate(PNode* end) {
    Vector3f resta = end->getPosition() - position;
    float estimate = resta.magnitude();
    
    return estimate;
}
