/* 
 * File:   TResourceAnimatedMeshContainer.h
 * Author: laurasirventcollado
 *
 * Created on 15 de marzo de 2014, 20:39
 */

#ifndef TRESOURCEANIMATEDMESHCONTAINER_H
#define	TRESOURCEANIMATEDMESHCONTAINER_H
#include "TResource.h"
#include "TResourceAnimatedMesh.h"
#include <iostream>
#include <vector>
#include <map>

class TResourceAnimatedMeshContainer : public TResource {
public:
    
    enum Cycle{ Stand, Talk, Walk, RunNeutral, RunTired, Jump, Start, Stop, Wave };
    
    TResourceAnimatedMeshContainer();
    TResourceAnimatedMeshContainer(const TResourceAnimatedMeshContainer& orig);
    virtual ~TResourceAnimatedMeshContainer();
    bool load(char *filename);
    void setCurrentAnimationCycle(Cycle c){ currentCycle = c; }
    void setFrame(float f){ frame = f; }
    float getFrame(){ return frame; }
    TResourceAnimatedMesh * getAnimation(Cycle c){ return animations.find(Stop)->second; }
    
    void draw();
    
    
private:
    std::map<Cycle, TResourceAnimatedMesh *> animations;
    Cycle currentCycle;
    float frame;
};

#endif	/* TRESOURCEANIMATEDMESHCONTAINER_H */

