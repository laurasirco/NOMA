/* 
 * File:   TResourceLODMesh.h
 * Author: MAC
 *
 * Created on 16 de abril de 2014, 17:41
 */

#ifndef TRESOURCELODMESH_H
#define	TRESOURCELODMESH_H
#include "TResource.h"
#include "TResourceTexture.h"
#include "TResourceMesh.h"

class TResourceLODMesh : public TResource {
public:
    TResourceLODMesh();
    TResourceLODMesh(const TResourceLODMesh& orig);
    virtual ~TResourceLODMesh();
    bool load(char* filename);
    void setLOD(int l) { LOD = l; }
    void setTexture(TResourceTexture *t) {texture = t;}
    void draw() {
        if(vectorLODMesh.size() > 0){
            vectorLODMesh[LOD]->setTexture(texture);    
            vectorLODMesh[LOD]->draw(); 
        }
    }
private:
    std::vector<TResourceMesh *> vectorLODMesh;
    TResourceTexture * texture;
    int LOD;
};

#endif	/* TRESOURCELODMESH_H */

