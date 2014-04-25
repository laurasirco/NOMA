/* 
 * File:   PRoute.cpp
 * Author: MAC
 * 
 * Created on 1 de noviembre de 2013, 17:02
 */

#include "../headers/PRoute.h"
#include <list>
#include <vector>

PRoute::PRoute() {
}

PRoute::PRoute(const PRoute& orig) {
}

PRoute::~PRoute() {
}

list<PNode *> PRoute::calculateRoute(PGraph* g, PNode* s, PNode* e) {
    
    g->restartWeights();
    OpenList.clear();
    ClosedList.clear();
    
    graph = g; 
    start = s; 
    end = e;
    
    start->setG(0);
    start->setH(start->Estimate(end));
    //S = H + G
    start->setParent(NULL);
    OpenList.push_back(start);
    while (!OpenList.empty()) {
        PNode* n = getMinimum();
        OpenList.remove(n);
        if (n == end) {
            return getPath();
        }
        PNodesList neighbors = graph->getNeighbors(n);
        for(PNodesListIterator it = neighbors.begin(); it != neighbors.end(); ++it) {
            PNode *nn = *it;
            float newG = n->getG() + n->Estimate(nn);
            if (isInList(ClosedList, nn) && nn->getG() <= newG) {
                //Skip e
            }
            else {
                nn->setParent(n);
                nn->setG(newG);
                nn->setH(nn->Estimate(end));
                //e.f = e.g + e.h
                if (isInList(ClosedList, nn)){
                    ClosedList.remove(nn);
                }
                if (!isInList(OpenList, nn)) {
                    OpenList.push_back(nn);
                }
            }
        }
        ClosedList.push_back(n);

    }
    return getPath(); //Esta lista contendrá el nodo end y su parent será NULL
    //Esto se devuelve en caso de no haber hecho bien el pathfinding
}

bool PRoute::isInList(list<PNode*> List, PNode* node) {
    bool is = false;
    for(PNodesListIterator it = List.begin(); it != List.end() && is == false; ++it) {
        PNode *e = *it;
        if (e == node) {
            is = true;
        }
    }
    return is;
}

PNode* PRoute::getMinimum() {
    PNode *minimum = OpenList.front();
    for(PNodesListIterator it = OpenList.begin(); it != OpenList.end(); ++it) {
        PNode * e = *it;
        if (e->getF() < minimum->getF()) {
            minimum = e;
        }
    }
    
    return minimum;
}

list<PNode *> PRoute::getPath() {
    PNodesList path;
    PNode* actual = end;
    while (actual->getParent() != NULL) {
        path.push_back(actual);
        actual = actual->getParent();
    }
    path.push_back(actual);
    path.reverse();
    
    //cout<<"Route from "<<start->getIndex()<<" to "<<end->getIndex()<<": ";
    
    for(PNodesListIterator it = path.begin(); it != path.end(); ++it){
        PNode *n = *it;
        //cout<<n->getIndex()<<"->";
    }
    //cout<<endl;
    
    return path;
}

