/* 
 * File:   TLODMesh.h
 * Author: iMac
 *
 * Created on 16 de abril de 2014, 10:44
 */

#ifndef TLODMESH_H
#define	TLODMESH_H
#include "TEntity.h"
#include "TResourceMesh.h"
#include "TResourceLODMesh.h"


class TLODMesh : public TEntity {
public:
    TLODMesh();
    TLODMesh(const TLODMesh& orig);
    virtual ~TLODMesh();
    bool load(char *filename, TResourceTexture* texture);
    
    void beginDraw() {LODMesh->setLOD(LOD); LODMesh->draw();}
    void endDraw() {}
    void setLOD(int l){ LOD = l;}
    TResourceLODMesh* getResource() {return LODMesh;}
    void setResource(TResourceLODMesh* l) {LODMesh = l;}
private:
    int LOD;
    TResourceLODMesh *LODMesh;
};

#endif	/* TLODMESH_H */

