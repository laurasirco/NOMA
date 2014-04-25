/* 
 * File:   TNode.h
 * Author: laurasirventcollado
 *
 * Created on 10 de febrero de 2014, 11:06
 */

#ifndef TNODE_H
#define	TNODE_H

#include <iostream>
#include <vector>
#include "TEntity.h"
using namespace std;

class TNode {
public:
    TNode();
    TNode(const TNode& orig);
    virtual ~TNode();
    
    bool setEntity(TEntity * e){ entity = e; return true; }
    TEntity * getEntity(){ return entity; }
    
    int addChild(TNode * child){ childs.push_back(child); return childs.size(); }
    int removeChild(TNode * child);
    
    void addParent(TNode * p) {parent = p; }
    TNode * getParent(){ return parent; }
    void setActive(bool a) {active = a; }
    int getNumberOfChilds () { return childs.size(); }
    TNode* getChild(int i) {return childs[i]; }
    void draw();
    
    void reset();
private:
    std::vector<TNode *> childs;
    TNode * parent;
    TEntity * entity;
    bool active;
};

#endif	/* TNODE_H */

