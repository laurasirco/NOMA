/* 
 * File:   Path.cpp
 * Author: Laura Sirvent Collado
 * 
 * Created on 5 de noviembre de 2013, 18:41
 */

#include "../headers/Path.h"

Path::Path() {
    current = 0; 
    done = false;
    to = -1;
    from = -1;
}

Path::Path(std::list<PNode*> w){    
    Path();
    wayPoints = w;
    it = wayPoints.begin();
}

Path::Path(const Path& orig) {
}

Path::~Path() {
}

bool Path::nextWayPoint(){
    PNode *n = *it;   
    if(n->getIndex() != to){
        ++it;
        return true; 
    }
    else{
        return false;
    }
}

PNode * Path::currentWayPoint(){
    
    PNode *n = *it;
    return n;
}

bool Path::finished(){
    
    if(it != wayPoints.end())
        return false;
    else
        return true;
}

void Path::printPath(){
    
    for(std::list<PNode*>::iterator i = wayPoints.begin(); i != wayPoints.end(); ++i){
        PNode *n = *i;
        cout<<n->getIndex()<<"-";
    }
    cout<<endl;
}

