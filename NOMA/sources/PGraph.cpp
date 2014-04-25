/* 
 * File:   PGraph.cpp
 * Author: laurasirventcollado
 * 
 * Created on 30 de octubre de 2013, 12:46
 */

#include "../headers/PGraph.h"
#include <list>

PGraph::PGraph() {
    nodes.clear();
    edges.clear();
}

PGraph::PGraph(const PGraph& orig) {
}

PGraph::~PGraph() {
}

int PGraph::addPNode(PNode * node){
    
    nodes.push_back(node);
    PEdgeList l;
    edges.push_back(l);
    node->setIndex(nodes.size()-1);
    return nodes.size()-1;
    
}

void PGraph::addPEdge(PEdge * edge){
    
    edges[edge->getFromNode()].push_back(edge);
    edges[edge->getToNode()].push_back(edge);
}

void PGraph::showGraph(){
    
    for(int i = 0; i < nodes.size(); i++){
        cout<<nodes[i]->getIndex()<<endl;
        
        for (PEdgeListIterator it = edges[i].begin(); it != edges[i].end(); ++it){
            PEdge * e = *it;
            cout<<" "<<e->getFromNode()<<","<<e->getToNode()<<endl;
        }
        
    }
}

void PGraph::restartWeights(){
    
    for(int i = 0; i < nodes.size(); i++){
        nodes[i]->setG(0);
        nodes[i]->setH(0);
    }
}

int PGraph::getPNodeIndex(Vector3f pos){
    
    for(int i = 0; i < nodes.size(); i++){
        if(nodes[i]->getPosition().X == pos.X && nodes[i]->getPosition().Y == pos.Y && nodes[i]->getPosition().Z == pos.Z){
            return nodes[i]->getIndex();
        }
    }
    return -1;
}

list<PNode *> PGraph::getNeighbors(PNode* observer) {
    int observerIndex = observer->getIndex();
    PEdgeList edgesNeighbors = edges[observerIndex];
    list<PNode *> neighbors;
    for(PEdgeListIterator it = edgesNeighbors.begin(); it != edgesNeighbors.end(); ++it) {
        PEdge * e = *it;
        if (nodes[e->getFromNode()] != observer) {
            neighbors.push_back(nodes[e->getFromNode()]);
        }
        else {
            neighbors.push_back(nodes[e->getToNode()]);
        }    
    }
        
    return neighbors;
}

int PGraph::getNearestPNode(Vector3f position){
    
    Vector3f distance = position - nodes[0]->getPosition();
    float magnitude = distance.magnitude();
    int idx = 0;
    
    for(int i = 0; i < nodes.size(); i++){
        distance = position - nodes[i]->getPosition();
        if(distance.magnitude() < magnitude){
            magnitude = distance.magnitude();
            idx = i;
        }
    }
    return idx;
}