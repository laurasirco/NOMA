/* 
 * File:   TMesh.h
 * Author: laurasirventcollado
 *
 * Created on 10 de febrero de 2014, 18:52
 */

#ifndef TMESH_H
#define	TMESH_H

#include "TEntity.h"
#include "TResourceMesh.h"

#include "GUIElement.h" //RGBA struct

class TMesh : public TEntity{
public:
    TMesh();
    TMesh(const TMesh& orig);
    virtual ~TMesh();
    void setMesh(TResourceMesh *m) { mesh = m; }
    TResourceMesh *getResourceMesh() { return mesh; }
    
    void beginDraw() { mesh->setColor(color); mesh->draw();}
    void endDraw();
    
    void setColor(RGBA * c){ color = c; }
    RGBA * getColor(){ return color; }
    
private:
    TResourceMesh *mesh;
    RGBA * color;
};

#endif	/* TMESH_H */

