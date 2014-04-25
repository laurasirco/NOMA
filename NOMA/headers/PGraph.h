/* 
 * File:   PGraph.h
 * Author: laurasirventcollado
 *
 * Created on 30 de octubre de 2013, 12:46
 */

#ifndef PGRAPH_H
#define	PGRAPH_H
#include "PNode.h"
#include "PEdge.h"
#include <iostream>
#include <vector>
#include <list>

using namespace std;

class PGraph {
public:
    
    typedef std::vector<PNode *> PNodeVector;
    typedef std::list<PEdge *> PEdgeList;
    typedef std::list<PEdge *>::iterator PEdgeListIterator;
    typedef std::vector <PEdgeList> PEdgeListVector;
    
    PGraph(bool d){ directed = d; nextPNodeIndex = 0; }
    PGraph();
    PGraph(const PGraph& orig);
    virtual ~PGraph();
    
    PNode * getPNode(int idx){return nodes[idx];};
    int getNearestPNode(Vector3f position);
    PEdgeList getPEdgeList(int idx){ return edges[idx]; }
    int getPNodeIndex(Vector3f pos);
    
    int getNextFreePNodeIndex();
    
    int addPNode(PNode * node);
    void removePNode(int node);
    void addPEdge(PEdge * edge);
    void removePEdge(int from, int to);
    
    bool isDirected(){ return directed; }
    bool isEmpty();
    
    void showGraph();
    std::list<PNode *> getNeighbors(PNode* observer);
    void restartWeights();
    std::vector<PNode *> getNodes(){ return nodes; };
    int getNumberOfPNodes(){ return nodes.size(); }
    std::vector<PEdgeList> getEdges() { return edges; }
    
private:
    PNodeVector nodes;
    PEdgeListVector edges;
    bool directed;
    int nextPNodeIndex;
};

#endif	/* PGRAPH_H */

