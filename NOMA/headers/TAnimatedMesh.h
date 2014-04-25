/* 
 * File:   TAnimatedMesh.h
 * Author: MAC
 *
 * Created on 12 de marzo de 2014, 16:15
 */

#ifndef TANIMATEDMESH_H
#define	TANIMATEDMESH_H
#include "TEntity.h"
#include "TResourceAnimatedMeshContainer.h"
#include <iostream>
using namespace std;

class TAnimatedMesh : public TEntity{
public:
    TAnimatedMesh();
    TAnimatedMesh(const TAnimatedMesh& orig);
    virtual ~TAnimatedMesh();
    
    void setAnimatedMeshContainer(TResourceAnimatedMeshContainer *m) { animations = m; }
    TResourceAnimatedMeshContainer *getResourceAnimatedMeshContainer() { return animations; }
    
    void beginDraw();
    void endDraw(){ }
    
    void setCycle(TResourceAnimatedMeshContainer::Cycle c){ cycle = c; }
    void setFrame(float f){ frame = f; }
    float getFrame(){ return frame; }
    
private:
    TResourceAnimatedMeshContainer * animations;
    float frame;
    TResourceAnimatedMeshContainer::Cycle cycle;
    
};

#endif	/* TANIMATEDMESH_H */

