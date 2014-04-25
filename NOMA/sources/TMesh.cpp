/* 
 * File:   TMesh.cpp
 * Author: laurasirventcollado
 * 
 * Created on 10 de febrero de 2014, 18:52
 */

#include "../headers/TMesh.h"
#include "../headers/TResourceManager.h"
#include <iostream>
using namespace std;

TMesh::TMesh() {
    color = new RGBA(1.0,1.0,1.0,1.0);
}

TMesh::TMesh(const TMesh& orig) {
}

TMesh::~TMesh() {
    
    if(mesh != NULL){
        TResourceManager::Instance()->deleteResource(mesh);
        mesh = NULL;
    }
}

void TMesh::endDraw() {
    
}