/* 
 * File:   PRoute.h
 * Author: MAC
 *
 * Created on 1 de noviembre de 2013, 17:02
 */

#ifndef PROUTE_H
#define	PROUTE_H
#include "PNode.h"
#include "PGraph.h"
#include <list>
#include <vector>

class PRoute {
public:
    PRoute();
    PRoute(const PRoute& orig);
    virtual ~PRoute();
    
    typedef std::list<PNode *> PNodesList; 
    typedef std::list<PNode *>::iterator PNodesListIterator; 

    std::list<PNode *> calculateRoute (PGraph* g, PNode* s, PNode* e);
    
    PNode* getMinimum ();
    std::list<PNode *> getPath();
    bool isInList (std::list<PNode *> List, PNode* node);
    
private:
    PGraph* graph; //Grafo de nodos y aristas
    PNode* start; //Nodo de inicio
    PNode* end; //Nodo de destino
    PNodesList OpenList; //Nodos a explorar
    PNodesList ClosedList; //Nodos explorados
};

#endif	/* PROUTE_H */

