/* 
 * File:   Path.h
 * Author: Laura Sirvent Collado
 *
 * Created on 5 de noviembre de 2013, 18:41
 */

#ifndef PATH_H
#define	PATH_H
#include "PNode.h"
#include <iostream>
#include <list>

class Path {
public:
    Path();
    Path(const Path& orig);
    Path(std::list<PNode *> w);
    virtual ~Path();
    bool isPathDone(){ return done; }
    void setDone(bool d){ done = d; }
    void setTo(int t){ to = t; }
    void setFrom(int f){ from = f; }
    int getTo(){ return to; }
    int getFrom(){ return from; }
    void setWaypoints(std::list<PNode *> w){ wayPoints = w; it = wayPoints.begin(); }
    void resetIterator(){ it = wayPoints.begin(); }
    bool nextWayPoint();
    bool finished();
    PNode * currentWayPoint();
    std::list<PNode *> getWaypoints(){ return wayPoints; }
    void printPath();
    
private:
    std::list<PNode *> wayPoints;
    std::list<PNode *>::iterator it;
    int current;
    bool done;
    int from, to;
};

#endif	/* PATH_H */

