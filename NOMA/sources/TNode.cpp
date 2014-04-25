/* 
 * File:   TNode.cpp
 * Author: laurasirventcollado
 * 
 * Created on 10 de febrero de 2014, 11:06
 */

#include "../headers/TNode.h"
#include "../headers/TLODMesh.h"
#include "../headers/GameState.h"
#include "../headers/TTransformation.h"

TNode::TNode() {
    active = false;
    parent = NULL;
}

TNode::TNode(const TNode& orig) {
}

TNode::~TNode() {
    
    if(entity != NULL){
        delete(entity);
        entity = NULL;
    }
    parent = NULL;
    
}

void TNode::reset(){
    childs.clear();
}

int TNode::removeChild(TNode* child){
    
    int i=0; bool found = false;
    while(!found && i < childs.size()){
        if(childs[i] == child)
            found = true;
        else
            i++;
    }
    if(i < childs.size()){
        childs.erase(childs.begin()+i);
        delete(child);
    }
    child = NULL;
    
    return i;
}

void TNode::draw() {
    if (typeid (* entity) == typeid (TLODMesh)) {
        TTransformation * transf = (TTransformation *) parent->getEntity();      
        Vector3 nomaDist = Vector3(GameState::Instance()->getNoma()->getPosition().X - transf->getPosition().x, GameState::Instance()->getNoma()->getPosition().Y - transf->getPosition().y, GameState::Instance()->getNoma()->getPosition().Z - transf->getPosition().z);
        float dist = nomaDist.length();
        if(dist < 200){           
            TLODMesh * LOD = (TLODMesh *) entity;
            LOD->setLOD(0);
        } else  if (dist < 400){
            TLODMesh * LOD = (TLODMesh *) entity;
            LOD->setLOD(1);
        } else {
            TLODMesh * LOD = (TLODMesh *) entity;
            LOD->setLOD(2);
        }        
    }
    entity->beginDraw();
    for (int i = 0; i < childs.size(); i++) {
        childs[i]->draw();
    }
    entity->endDraw();
}
