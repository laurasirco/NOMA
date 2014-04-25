/* 
 * File:   TResourceManager.cpp
 * Author: iMac
 * 
 * Created on 17 de febrero de 2014, 22:19
 */

#include "../headers/TResourceManager.h"
#include <vector>
#include <algorithm>

TResourceManager::TResourceManager() {

}

TResourceManager::TResourceManager(const TResourceManager& orig) {
}

TResourceManager::~TResourceManager() {
}

TResourceManager* TResourceManager::pinstance = 0;

TResourceManager* TResourceManager::Instance() {

    if (pinstance == 0) {
        pinstance = new TResourceManager;
    }
    return pinstance;
}

void TResourceManager::deleteResource(TResource* r){
    
    int i=0; bool found = false;
    while(!found && i < resources.size()){
        if(resources[i] == r)
            found = true;
        else
            i++;
    }
    if(i < resources.size()){
        resources.erase(resources.begin()+i);
        delete(r);
    }
    r = NULL;
}

TResourceMesh *TResourceManager::getResourceMesh(std::string name) {
    TResourceMesh *rec = NULL;
    int i = 0;
    bool foundResource = false;
    while (i < resources.size() && !foundResource) {
        if (resources[i]->getName() == name) {
            foundResource = true;
            rec = (TResourceMesh*) resources[i];
        }
        i++;
    }
    if (rec == NULL) {
        rec = new TResourceMesh();
        rec->load((char*) name.c_str());
        rec->setName(name);
        resources.push_back(rec);
    }
    return rec;
}

TResourceAnimatedMeshContainer * TResourceManager::getResourceAnimatedMesh(std::string name) {

    TResourceAnimatedMeshContainer *rec = NULL;
    int i = 0;
    bool foundResource = false;
    while (i < resources.size() && !foundResource) {
        if (resources[i]->getName() == name) {
            foundResource = true;
            rec = (TResourceAnimatedMeshContainer*) resources[i];
        }
        i++;
    }
    if (rec == NULL) {
        rec = new TResourceAnimatedMeshContainer();
        rec->load((char*) name.c_str());
        cout<<"Al acabar "<<rec->getAnimation(TResourceAnimatedMeshContainer::Stop)<<endl;
        rec->setName(name);
        cout<<"Al acabar "<<rec->getAnimation(TResourceAnimatedMeshContainer::Stop)<<endl;
        resources.push_back(rec);
    }
    return rec;
}

TResourceTexture *TResourceManager::getResourceTexture(std::string name) {
    TResourceTexture *rec = NULL;
    int i = 0;
    bool foundResource = false;
    while (i < resources.size() && !foundResource) {
        if (resources[i]->getName() == name) {
            foundResource = true;
            rec = (TResourceTexture*) resources[i];
        }
        i++;
    }
    if (rec == NULL) {
        rec = new TResourceTexture();
        rec->loadTexture((char*) name.c_str());
        rec->setName(name);
        resources.push_back(rec);
    }
    return rec;
}

TResourceFont * TResourceManager::getResourceFont(std::string name, int size) {

    TResourceFont *rec = NULL;
    int i = 0;
    bool foundResource = false;
    while (i < resources.size() && !foundResource) {
        if (resources[i]->getName() == name) {
            TResourceFont *f = (TResourceFont*) resources[i];
            if (size == f->getSize()) {
                foundResource = true;
                rec = f;
            }
        }
        i++;
    }
    if (rec == NULL) {
        rec = new TResourceFont();
        rec->load((char*) name.c_str(), size);
        rec->setName(name);
        resources.push_back(rec);
    }
    return rec;
}

TResourceLODMesh * TResourceManager::getResourceLOD(std::string name) {
    
    TResourceLODMesh *rec = NULL;
    int i = 0;
    bool foundResource = false;
    while (i < resources.size() && !foundResource) {
        if (resources[i]->getName() == name) {
            foundResource = true;
            rec = (TResourceLODMesh*) resources[i];
        }
        i++;
    }
    if (rec == NULL) {
        rec = new TResourceLODMesh();
        
        rec->load((char*) name.c_str());
        rec->setName(name);
        resources.push_back(rec);
    }
    return rec;
}