/* 
 * File:   TResourceManager.h
 * Author: iMac
 *
 * Created on 17 de febrero de 2014, 22:19
 */

#ifndef TRESOURCEMANAGER_H
#define	TRESOURCEMANAGER_H
#include "../headers/TResourceMesh.h"
#include "../headers/TResourceFont.h"
#include "../headers/TResourceAnimatedMeshContainer.h"
#include "../headers/TResourceLODMesh.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstring>


using namespace std;

class TResourceManager {
public:
    TResourceManager();
    TResourceManager(const TResourceManager& orig);
    virtual ~TResourceManager();
    static TResourceManager* Instance();
    TResourceMesh *getResourceMesh (std::string name);
    TResourceTexture *getResourceTexture (std::string name);
    TResourceFont *getResourceFont (std::string name, int size);
    TResourceLODMesh *getResourceLOD (std::string name);
    TResourceAnimatedMeshContainer * getResourceAnimatedMesh(std::string name);
    void deleteResource(TResource * r);
private:
    std::vector <TResource *> resources;
    static TResourceManager* pinstance;
};

#endif	/* TRESOURCEMANAGER_H */

